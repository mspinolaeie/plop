#include "PlopCoreFacade.h"

#include "PlopQtRuntime.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QPainter>
#include <QProcess>
#include <QProcessEnvironment>
#include <QTemporaryFile>
#include <QTextStream>

#include <cmath>
#include <cstring>

#include "global.h"
#include "grid_gen.h"
#include "plate_global.h"
#include "plop_debug.h"
#include "plop_parms.h"
#include "plop_parser.h"
#include "plot.h"

void init_plop(void);
void alloc_globals(void);
void read_info(char *s);
void read_info_chars(void);
void write_info_chars(int phys, int write_opts);
void init_default_basis(void);
void run_plate(void);
void evaluate_parts(void);

namespace plopqt {

namespace {

QString normalizeText(QString text)
{
	text.replace("\r\n", "\n");
	text.replace('\r', '\n');
	return text;
}

QString renderNumberList(const double *values, int count)
{
	QStringList items;
	for (int i = 0; i < count; ++i) {
		items << QString::number(values[i], 'g', 10);
	}
	return items.join(", ");
}

QString renderIntList(const int *values, int count)
{
	QStringList items;
	for (int i = 0; i < count; ++i) {
		items << QString::number(values[i]);
	}
	return items.join(", ");
}

QString lineForPart(int partIndex)
{
	QString line = QStringLiteral("Part %1: ").arg(partIndex + 1);
	line += QStringLiteral("type=%1 quantity=%2")
		.arg(part_type[partIndex] == part_type_triangle ? QStringLiteral("triangle") : QStringLiteral("bar"))
		.arg(part_quantity[partIndex]);
	return line;
}

}

PlopCoreFacade::PlopCoreFacade()
	: initialized_(false)
{
}

void PlopCoreFacade::ensureInitialized() const
{
	if (initialized_) {
		return;
	}

	init_plop();
	init_graphics();
	alloc_globals();
	alloc_plate_globals();
	output_file = stdout;
	debug_file = stdout;
	initialized_ = true;
}

void PlopCoreFacade::resetForInput() const
{
	init_plop();
	output_file = stdout;
	debug_file = stdout;
}

bool PlopCoreFacade::applyControlTextLocked(const QString &text, QString *errorMessage) const
{
	QString normalized = normalizeText(text);
	QByteArray data = normalized.toLocal8Bit();
	if (data.size() >= max_plop_file_len) {
		if (errorMessage != NULL) {
			*errorMessage = QStringLiteral("The control file is too large for the legacy Plop parser.");
		}
		return false;
	}

	resetForInput();
	plopqt::clearRuntimeMessages();
	std::memcpy(plop_text_file_buff, data.constData(), static_cast<size_t>(data.size()));
	plop_text_file_buff[data.size()] = '\0';
	plop_text_file_len = data.size();
	plop_comment_len = 0;
	currentText_ = normalized;

	try {
		read_info_chars();
	}
	catch (const AbortException &abort) {
		if (errorMessage != NULL) {
			*errorMessage = abort.message();
		}
		return false;
	}

	if (errorMessage != NULL) {
		errorMessage->clear();
	}
	return true;
}

QString PlopCoreFacade::loadControlFile(const QString &filePath, QString *errorMessage)
{
	QMutexLocker locker(&mutex_);
	ensureInitialized();

	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		if (errorMessage != NULL) {
			*errorMessage = QStringLiteral("Unable to open %1").arg(QDir::toNativeSeparators(filePath));
		}
		return QString();
	}

	QString text = QString::fromLocal8Bit(file.readAll());
	if (!applyControlTextLocked(text, errorMessage)) {
		return QString();
	}

	return currentText_;
}

bool PlopCoreFacade::saveControlFile(const QString &filePath, const QString &text, QString *errorMessage) const
{
	QFile file(filePath);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
		if (errorMessage != NULL) {
			*errorMessage = QStringLiteral("Unable to write %1").arg(QDir::toNativeSeparators(filePath));
		}
		return false;
	}

	QByteArray data = normalizeText(text).toLocal8Bit();
	if (file.write(data) != data.size()) {
		if (errorMessage != NULL) {
			*errorMessage = QStringLiteral("Unable to write the full control file to disk.");
		}
		return false;
	}

	if (errorMessage != NULL) {
		errorMessage->clear();
	}
	return true;
}

bool PlopCoreFacade::parseControlText(const QString &text, QString *errorMessage)
{
	QMutexLocker locker(&mutex_);
	ensureInitialized();
	return applyControlTextLocked(text, errorMessage);
}

RunResults PlopCoreFacade::snapshotResultsLocked() const
{
	RunResults results;
	results.visibleRms = plate_err_vis_rms;
	results.visiblePv = plate_err_vis_p_v;
	results.refocusFocalLength = plate_refocus_focal_length;
	results.z88VisibleRms = z88_plot_err_vis_rms;
	results.z88VisiblePv = z88_plot_err_vis_p_v;
	results.hasZ88Results = z88_plot_n_points > 0;
	results.hasGeneratedZ88Input = z88_input_files_valid != 0;
	results.warnings = plopqt::warningsText();
	results.debugLog = plopqt::debugLog();
	return results;
}

bool PlopCoreFacade::runControlText(const QString &text, const RunSettings &settings, RunResults *results, QString *errorMessage)
{
	QMutexLocker locker(&mutex_);
	ensureInitialized();
	if (!applyControlTextLocked(text, errorMessage)) {
		return false;
	}

	use_p_v_error = settings.usePeakValley ? 1 : 0;
	refocus_flag = settings.refocus ? 1 : 0;
	refocus_xyr_flag = settings.refocusXyr ? 1 : 0;
	grid_gen_using_basis = settings.useBasis ? 1 : 0;
	generate_z88_input_flag = settings.generateZ88Input ? 1 : 0;
	trace_opt = settings.traceOptimization ? 1 : 0;
	calculate_zernike_flag = settings.calculateZernike ? 1 : 0;
	zernike_order = settings.zernikeOrder;
	n_monte_tests = settings.monteTests;
	z88_plot_n_points = 0;
	z88_plot_n_triangles = 0;
	z88_input_files_valid = 0;

	FILE *stream = stdout;
	QTemporaryFile outputTemplate(QDir::temp().filePath(QStringLiteral("plop-run-XXXXXX.txt")));
	if (outputTemplate.open()) {
		const QString path = outputTemplate.fileName();
		outputTemplate.close();
		QByteArray nativePath = QDir::toNativeSeparators(path).toLocal8Bit();
		stream = fopen(nativePath.constData(), "w+");
	}
	output_file = stream != NULL ? stream : stdout;
	debug_file = stdout;

	try {
		init_default_basis();
		plate_init();
		run_plate();
	}
	catch (const AbortException &abort) {
		if (stream != NULL && stream != stdout) {
			fclose(stream);
		}
		output_file = stdout;
		debug_file = stdout;
		if (errorMessage != NULL) {
			*errorMessage = abort.message();
		}
		return false;
	}

	QString outputLog;
	if (stream != NULL && stream != stdout) {
		fflush(stream);
		fseek(stream, 0, SEEK_SET);
		QByteArray content;
		char buffer[1024];
		while (fgets(buffer, sizeof(buffer), stream) != NULL) {
			content.append(buffer);
		}
		outputLog = QString::fromLocal8Bit(content);
		fclose(stream);
	}
	output_file = stdout;
	debug_file = stdout;

	if (results != NULL) {
		*results = snapshotResultsLocked();
		results->outputLog = outputLog;
	}
	if (errorMessage != NULL) {
		errorMessage->clear();
	}
	return true;
}

bool PlopCoreFacade::runZ88(RunResults *results, QString *errorMessage)
{
	QMutexLocker locker(&mutex_);
	ensureInitialized();
	if (!z88_input_files_valid) {
		if (errorMessage != NULL) {
			*errorMessage = QStringLiteral("No generated Z88 input is available. Run Plop with Z88 input generation enabled first.");
		}
		return false;
	}

	const QString appDir = QCoreApplication::applicationDirPath();
	const QString exe1 = QDir(appDir).filePath(QStringLiteral("z88i1plop.exe"));
	const QString exe2 = QDir(appDir).filePath(QStringLiteral("z88i2plop.exe"));
	if (!QFile::exists(exe1) || !QFile::exists(exe2)) {
		if (errorMessage != NULL) {
			*errorMessage = QStringLiteral("The Z88 executables were not found next to the application binary.");
		}
		return false;
	}

	QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
	env.insert(QStringLiteral("PLOPDIR"), QDir::toNativeSeparators(appDir));

	auto runProcess = [&](const QString &exePath) -> bool {
		QProcess process;
		process.setWorkingDirectory(appDir);
		process.setProcessEnvironment(env);
		process.start(exePath);
		if (!process.waitForStarted()) {
			if (errorMessage != NULL) {
				*errorMessage = QStringLiteral("Unable to start %1").arg(QDir::toNativeSeparators(exePath));
			}
			return false;
		}
		process.waitForFinished(-1);
		if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
			if (errorMessage != NULL) {
				*errorMessage = QStringLiteral("%1 failed:\n%2")
					.arg(QFileInfo(exePath).fileName(), QString::fromLocal8Bit(process.readAllStandardError()));
			}
			return false;
		}
		return true;
	};

	if (!runProcess(exe1) || !runProcess(exe2)) {
		return false;
	}

	load_z88_deflection_data(n_mesh_depth);
	if (results != NULL) {
		*results = snapshotResultsLocked();
	}
	if (errorMessage != NULL) {
		errorMessage->clear();
	}
	return true;
}

QPointF PlopCoreFacade::scalePoint(double x, double y, double scale, int size)
{
	const double centeredX = x * scale + size / 2.0;
	const double centeredY = y * scale + size / 2.0;
	return QPointF(centeredX, size - 1.0 - centeredY);
}

QImage PlopCoreFacade::renderRasterPlotLocked(PlotKind kind, int size) const
{
	const int boundedSize = qMin(size, graph_xy_max);
	pic_size = boundedSize;
	double zMin = 0.0;
	double zMax = 0.0;
	double errRms = 0.0;
	double errPv = 0.0;
	const plop_cmap *map = &color_cmap;

	switch (kind) {
	case PlotKind::Color:
		calculate_plop_plot(0, &zMin, &zMax, &errRms, &errPv);
		map = &color_cmap;
		break;
	case PlotKind::Contour:
		calculate_plop_plot(1, &zMin, &zMax, &errRms, &errPv);
		map = &contour_cmap;
		break;
	case PlotKind::Z88Color:
		calculate_z88_plot(0, &zMin, &zMax, &errRms, &errPv);
		map = &color_cmap;
		break;
	default:
		return QImage();
	}

	QImage image(boundedSize, boundedSize, QImage::Format_RGB32);
	for (int y = 0; y < boundedSize; ++y) {
		for (int x = 0; x < boundedSize; ++x) {
			const unsigned char index = picture[y][x];
			image.setPixelColor(x, y, QColor(map->color_r[index], map->color_g[index], map->color_b[index]));
		}
	}
	return image;
}

QImage PlopCoreFacade::renderGeometryPlotLocked(PlotKind kind, int size) const
{
	QImage image(size, size, QImage::Format_ARGB32_Premultiplied);
	image.fill(Qt::white);

	if (diameter <= 0.0) {
		return image;
	}

	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(QPen(Qt::black, 1.0));

	const double scale = (size * 0.95) / diameter;
	auto toPoint = [&](int pointIndex) {
		double x = 0.0;
		double y = 0.0;
		polar_to_euc(point_radius[pointIndex], point_angle[pointIndex], &x, &y);
		return scalePoint(x, y, scale, size);
	};

	if (kind == PlotKind::Mesh) {
		for (int i = 0; i < n_triangles; ++i) {
			for (int j = 0; j < tri_pts; ++j) {
				painter.drawLine(toPoint(triangle_points[i][j]), toPoint(triangle_points[i][(j + 1) % tri_pts]));
			}
		}
	}
	else if (kind == PlotKind::Quads && n_quads > 0) {
		for (int i = 0; i < n_quads; ++i) {
			for (int j = 0; j < quad_pts; ++j) {
				painter.drawLine(toPoint(quad_points[i][j]), toPoint(quad_points[i][(j + 1) % quad_pts]));
			}
		}
	}
	else {
		painter.drawEllipse(QRectF(size * 0.025, size * 0.025, size * 0.95, size * 0.95));
	}

	if (kind == PlotKind::Parts) {
		for (int i = 0; i < n_parts; ++i) {
			const int corners = part_type_num_corners[part_type[i]];
			for (int instance = 0; instance < part_quantity[i]; ++instance) {
				QPainterPath path;
				for (int corner = 0; corner < corners; ++corner) {
					double x = 0.0;
					double y = 0.0;
					polar_to_euc(part_corner_radius[i][corner],
						part_corner_angle[i][corner] + instance * static_cast<double>(degrees) / part_quantity[i],
						&x, &y);
					const QPointF point = scalePoint(x, y, scale, size);
					if (corner == 0) {
						path.moveTo(point);
					}
					else {
						path.lineTo(point);
					}
				}
				path.closeSubpath();
				painter.drawPath(path);
			}
		}
	}

	painter.setBrush(Qt::white);
	for (int i = 0; i < n_support_radii; ++i) {
		for (int j = 0; j < num_support[i]; ++j) {
			double x = 0.0;
			double y = 0.0;
			const double angle = support_angle[i] + j * static_cast<double>(degrees) / num_support[i];
			polar_to_euc(support_radii[i], angle, &x, &y);
			painter.drawEllipse(scalePoint(x, y, scale, size), size / 140.0, size / 140.0);
		}
	}

	if (kind == PlotKind::Quads && n_quads == 0) {
		painter.setPen(Qt::darkGray);
		painter.drawText(image.rect().adjusted(12, 12, -12, -12),
			Qt::AlignTop | Qt::AlignLeft | Qt::TextWordWrap,
			QStringLiteral("No quads are available. Enable Z88 input generation during a run to populate quadrilateral data."));
	}

	return image;
}

QImage PlopCoreFacade::renderPartDimensionLocked(int partIndex, bool inches, int size) const
{
	QImage image(size, size, QImage::Format_ARGB32_Premultiplied);
	image.fill(Qt::white);

	if (partIndex < 0 || partIndex >= n_parts) {
		return image;
	}

	const double unitScale = inches ? (1.0 / 25.4) : 1.0;
	const int corners = part_type_num_corners[part_type[partIndex]];
	double maxX = 0.0;
	double maxY = 0.0;
	double minX = 0.0;
	double minY = 0.0;
	for (int corner = 0; corner < corners; ++corner) {
		maxX = qMax(maxX, part_draw_x[partIndex][corner]);
		maxY = qMax(maxY, part_draw_y[partIndex][corner]);
		minX = qMin(minX, part_draw_x[partIndex][corner]);
		minY = qMin(minY, part_draw_y[partIndex][corner]);
	}

	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(QPen(Qt::black, 1.0));

	const double usableWidth = size - 120.0;
	const double usableHeight = size - 40.0;
	const double width = qMax(maxX - minX, 1.0e-10);
	const double height = qMax(maxY - minY, 1.0e-10);
	const double scale = qMin(usableWidth / width, usableHeight / height) * 0.9;
	const double originX = ((size - 120.0) - (maxX + minX) * scale) / 2.0;
	const double originY = ((size - 40.0) - (maxY + minY) * scale) / 2.0;

	auto localPoint = [&](double x, double y) {
		return QPointF(x * scale + originX, size - 1.0 - (y * scale + originY));
	};

	for (int corner = 0; corner < corners; ++corner) {
		const QPointF start = localPoint(part_draw_x[partIndex][corner], part_draw_y[partIndex][corner]);
		const QPointF end = localPoint(part_draw_x[partIndex][(corner + 1) % corners], part_draw_y[partIndex][(corner + 1) % corners]);
		painter.drawLine(start, end);
		painter.drawEllipse(start, size / 140.0, size / 140.0);
		painter.drawText(start + QPointF(8.0, -8.0),
			QStringLiteral("(%1) X=%2 Y=%3")
				.arg((corner + part_rotation[partIndex]) % corners + 1)
				.arg(part_draw_x[partIndex][corner] * unitScale, 0, 'f', 3)
				.arg(part_draw_y[partIndex][corner] * unitScale, 0, 'f', 3));
	}

	painter.setPen(QPen(Qt::red, 1.0));
	const QPointF cg = localPoint(part_draw_cg_x[partIndex], part_draw_cg_y[partIndex]);
	painter.drawLine(cg + QPointF(-8.0, 0.0), cg + QPointF(8.0, 0.0));
	painter.drawLine(cg + QPointF(0.0, -8.0), cg + QPointF(0.0, 8.0));
	painter.drawText(cg + QPointF(14.0, -12.0),
		QStringLiteral("X=%1 Y=%2")
			.arg(part_draw_cg_x[partIndex] * unitScale, 0, 'f', 3)
			.arg(part_draw_cg_y[partIndex] * unitScale, 0, 'f', 3));

	return image;
}

QImage PlopCoreFacade::renderPlot(PlotKind kind, int size) const
{
	QMutexLocker locker(&mutex_);
	ensureInitialized();

	switch (kind) {
	case PlotKind::Color:
	case PlotKind::Contour:
	case PlotKind::Z88Color:
		return renderRasterPlotLocked(kind, size);
	default:
		return renderGeometryPlotLocked(kind, size);
	}
}

QImage PlopCoreFacade::renderPartDimension(int partIndex, bool inches) const
{
	QMutexLocker locker(&mutex_);
	ensureInitialized();
	return renderPartDimensionLocked(partIndex, inches, 900);
}

QString PlopCoreFacade::partDetailsLocked(int partIndex, bool inches) const
{
	if (partIndex < 0 || partIndex >= n_parts) {
		return QStringLiteral("No part selected.");
	}

	const double unitScale = inches ? (1.0 / 25.4) : 1.0;
	QStringList lines;
	lines << lineForPart(partIndex);
	lines << QStringLiteral("CG radius: %1").arg(part_cg_radius[partIndex] * unitScale, 0, 'f', 3);
	lines << QStringLiteral("CG angle: %1").arg(std::fmod(part_cg_angle[partIndex], static_cast<double>(degrees)), 0, 'f', 3);
	lines << QStringLiteral("CG X: %1").arg(part_cg_x[partIndex] * unitScale, 0, 'f', 3);
	lines << QStringLiteral("CG Y: %1").arg(part_cg_y[partIndex] * unitScale, 0, 'f', 3);
	return lines.join("\n");
}

QString PlopCoreFacade::partDetails(int partIndex, bool inches) const
{
	QMutexLocker locker(&mutex_);
	ensureInitialized();
	return partDetailsLocked(partIndex, inches);
}

void PlopCoreFacade::rotatePart(int partIndex)
{
	QMutexLocker locker(&mutex_);
	ensureInitialized();
	if (partIndex < 0 || partIndex >= n_parts) {
		return;
	}
	part_rotation[partIndex] = (part_rotation[partIndex] + 1) % part_type_num_corners[part_type[partIndex]];
	evaluate_parts();
}

SummaryData PlopCoreFacade::summariesLocked() const
{
	SummaryData data;

	data.mirror = QStringLiteral(
		"Diameter: %1\nThickness: %2\nFocal length: %3\nMesh rings: %4\nMesh depth: %5\nRefocus enabled: %6")
		.arg(diameter, 0, 'g', 10)
		.arg(thickness, 0, 'g', 10)
		.arg(focal_length, 0, 'g', 10)
		.arg(n_mesh_rings)
		.arg(n_mesh_depth)
		.arg(refocus_flag ? QStringLiteral("yes") : QStringLiteral("no"));

	data.supports = QStringLiteral(
		"Support rings: %1\nSupport radii: %2\nSupports per ring: %3\nSupport angles: %4")
		.arg(n_support_radii)
		.arg(renderNumberList(support_radii, n_support_radii))
		.arg(renderIntList(num_support, n_num_support_rings))
		.arg(renderNumberList(support_angle, n_support_angle));

	QStringList variableLines;
	variableLines << QStringLiteral("Variables: %1").arg(n_variables);
	for (int i = 0; i < n_variables; ++i) {
		variableLines << QStringLiteral("  %1 = %2").arg(var_table[i].name).arg(var_table[i].value, 0, 'g', 10);
	}
	variableLines << QStringLiteral("Optimize vars: %1").arg(n_optimize_vars);
	variableLines << QStringLiteral("Scan vars: %1").arg(n_scan_vars);
	variableLines << QStringLiteral("Scan sets: %1").arg(n_scan_set_vars);
	variableLines << QStringLiteral("Monte vars: %1").arg(n_monte_vars);
	data.variables = variableLines.join("\n");

	QStringList partsLines;
	partsLines << QStringLiteral("Parts: %1").arg(n_parts);
	for (int i = 0; i < n_parts; ++i) {
		partsLines << lineForPart(i);
	}
	data.parts = partsLines.join("\n");

	data.z88 = QStringLiteral(
		"Generate Z88 input: %1\nInput generated: %2\nStructure file: %3\nLoad file: %4\nDeflection file: %5")
		.arg(generate_z88_input_flag ? QStringLiteral("yes") : QStringLiteral("no"))
		.arg(z88_input_files_valid ? QStringLiteral("yes") : QStringLiteral("no"))
		.arg(QString::fromLocal8Bit(z88_struct_file_name))
		.arg(QString::fromLocal8Bit(z88_load_file_name))
		.arg(QString::fromLocal8Bit(z88_deflection_file_name));

	return data;
}

SummaryData PlopCoreFacade::summaries() const
{
	QMutexLocker locker(&mutex_);
	ensureInitialized();
	return summariesLocked();
}

QString PlopCoreFacade::manualPath() const
{
	return QDir(QCoreApplication::applicationDirPath()).filePath(QStringLiteral("GuiPlop Users Manual.pdf"));
}

QString PlopCoreFacade::autoCellDirectory() const
{
	return QDir(QCoreApplication::applicationDirPath()).filePath(QStringLiteral("autocell"));
}

QString PlopCoreFacade::currentControlText() const
{
	QMutexLocker locker(&mutex_);
	return currentText_;
}

int PlopCoreFacade::partCount() const
{
	QMutexLocker locker(&mutex_);
	ensureInitialized();
	return n_parts;
}

bool PlopCoreFacade::hasGeneratedZ88Input() const
{
	QMutexLocker locker(&mutex_);
	ensureInitialized();
	return z88_input_files_valid != 0;
}

bool PlopCoreFacade::isInitialized() const
{
	QMutexLocker locker(&mutex_);
	return initialized_;
}

}
