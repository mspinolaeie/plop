#pragma once

#include <QImage>
#include <QMutex>
#include <QString>

namespace plopqt {

enum class PlotKind {
	Mesh,
	Supports,
	Color,
	Contour,
	Parts,
	Quads,
	Z88Color,
};

struct RunSettings {
	bool usePeakValley = false;
	bool refocus = true;
	bool refocusXyr = false;
	bool useBasis = true;
	bool generateZ88Input = false;
	bool traceOptimization = false;
	bool calculateZernike = false;
	int zernikeOrder = 12;
	int monteTests = 0;
};

struct RunResults {
	double visibleRms = 0.0;
	double visiblePv = 0.0;
	double refocusFocalLength = 0.0;
	double z88VisibleRms = 0.0;
	double z88VisiblePv = 0.0;
	bool hasZ88Results = false;
	bool hasGeneratedZ88Input = false;
	QString outputLog;
	QString warnings;
	QString debugLog;
};

struct SummaryData {
	QString mirror;
	QString supports;
	QString variables;
	QString parts;
	QString z88;
};

class PlopCoreFacade {
public:
	PlopCoreFacade();

	QString loadControlFile(const QString &filePath, QString *errorMessage);
	bool parseControlText(const QString &text, QString *errorMessage);
	bool saveControlFile(const QString &filePath, const QString &text, QString *errorMessage) const;
	bool runControlText(const QString &text, const RunSettings &settings, RunResults *results, QString *errorMessage);
	bool runZ88(RunResults *results, QString *errorMessage);

	QImage renderPlot(PlotKind kind, int size = 750) const;
	QImage renderPartDimension(int partIndex, bool inches) const;
	QString partDetails(int partIndex, bool inches) const;
	void rotatePart(int partIndex);

	SummaryData summaries() const;
	QString manualPath() const;
	QString autoCellDirectory() const;
	QString currentControlText() const;
	int partCount() const;
	bool hasGeneratedZ88Input() const;
	bool isInitialized() const;

private:
	void ensureInitialized() const;
	void resetForInput() const;
	bool applyControlTextLocked(const QString &text, QString *errorMessage) const;
	RunResults snapshotResultsLocked() const;
	SummaryData summariesLocked() const;
	QImage renderRasterPlotLocked(PlotKind kind, int size) const;
	QImage renderGeometryPlotLocked(PlotKind kind, int size) const;
	QImage renderPartDimensionLocked(int partIndex, bool inches, int size) const;
	QString partDetailsLocked(int partIndex, bool inches) const;

	static QPointF scalePoint(double x, double y, double scale, int size);

	mutable QMutex mutex_;
	mutable bool initialized_;
	mutable QString currentText_;
};

}
