#ifndef MULTILOGGER_H
#define MULTILOGGER_H

#include "logger.h"

namespace NS_Log
{
    class MultiLogger : public Logger
    {
    public:
        explicit MultiLogger(const QString &folderPath, qint64 timeSinceEpoch);
    };
}

#endif // MULTILOGGER_H
