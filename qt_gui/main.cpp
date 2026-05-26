#include <QApplication>

#include "MainWindow.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setApplicationName(QStringLiteral("plop_gui_qt"));
	QCoreApplication::setOrganizationName(QStringLiteral("plop"));

	MainWindow window;
	window.show();

	if (argc > 1) {
		window.openControlFile(QString::fromLocal8Bit(argv[1]));
	}

	return app.exec();
}
