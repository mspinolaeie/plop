#include "PlopQtRuntime.h"

#include <QMutex>
#include <QMutexLocker>
#include <QStringList>

namespace {

QMutex g_runtimeMutex;
QString g_lastError;
QStringList g_warnings;
QString g_debugLog;

QString fromLocal(const char *text)
{
	return text == NULL ? QString() : QString::fromLocal8Bit(text);
}

}

namespace plopqt {

AbortException::AbortException(QString message)
	: message_(message)
{
}

const QString &AbortException::message() const
{
	return message_;
}

void clearRuntimeMessages()
{
	QMutexLocker locker(&g_runtimeMutex);
	g_lastError.clear();
	g_warnings.clear();
	g_debugLog.clear();
}

QString lastErrorMessage()
{
	QMutexLocker locker(&g_runtimeMutex);
	return g_lastError;
}

QString warningsText()
{
	QMutexLocker locker(&g_runtimeMutex);
	return g_warnings.join("\n");
}

QString debugLog()
{
	QMutexLocker locker(&g_runtimeMutex);
	return g_debugLog;
}

}

void prompt_exit(void)
{
	QString message;
	{
		QMutexLocker locker(&g_runtimeMutex);
		message = g_lastError;
		if (message.isEmpty()) {
			message = QStringLiteral("Plop aborted the current operation.");
		}
	}

	throw plopqt::AbortException(message);
}

void err_msg(const char *msg)
{
	QMutexLocker locker(&g_runtimeMutex);
	g_lastError = fromLocal(msg).trimmed();
	if (!g_lastError.isEmpty()) {
		g_debugLog += g_lastError + QLatin1Char('\n');
	}
}

void warn_msg(const char *msg)
{
	const QString warning = fromLocal(msg).trimmed();
	QMutexLocker locker(&g_runtimeMutex);
	if (!warning.isEmpty()) {
		g_warnings.push_back(warning);
		g_debugLog += warning + QLatin1Char('\n');
	}
}
