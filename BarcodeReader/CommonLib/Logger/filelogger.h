#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "logger.h"

namespace NS_Log
{
    class FileLogger : public Logger
    {
    public:
        explicit FileLogger(const QString &folderPath, qint64 timeSinceEpoch);
    };
}

#endif // FILELOGGER_H
