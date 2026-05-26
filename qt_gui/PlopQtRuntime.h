#pragma once

#include <QString>

namespace plopqt {

class AbortException {
public:
	explicit AbortException(QString message);

	const QString &message() const;

private:
	QString message_;
};

void clearRuntimeMessages();
QString lastErrorMessage();
QString warningsText();
QString debugLog();

}
