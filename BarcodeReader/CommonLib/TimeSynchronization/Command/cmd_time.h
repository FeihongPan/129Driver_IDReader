#ifndef CMD_TIME_H
#define CMD_TIME_H

#include <QObject>

class CMD_Time : public QObject
{
    Q_OBJECT

public:
    enum Command
    {
        CMD_TimeBenchmark,
        CMD_SetTime,
    };
    Q_ENUM(Command)
};

#endif // CMD_TIME_H
