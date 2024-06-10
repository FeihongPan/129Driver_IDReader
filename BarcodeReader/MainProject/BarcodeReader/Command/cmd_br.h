#ifndef CMD_BR_H
#define CMD_BR_H

#include <QObject>

class CMD_BR : public QObject
{
    Q_OBJECT
public:
    enum Command
    {
        CMD_Read,
        CMD_ReadwithPos,
    };
    Q_ENUM(Command)

    explicit CMD_BR(QObject *parent = nullptr);

signals:

};

#endif // CMD_BR_H
