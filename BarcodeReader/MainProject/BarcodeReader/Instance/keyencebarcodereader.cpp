#include "keyencebarcodereader.h"

#include <QTimer>
#include <QDebug>
#include <QEventLoop>

KeyenceBarcodeReader::KeyenceBarcodeReader(const int &id, QObject *parent) : IBarcodeReader(id, parent)
{
    connect(p_Client, &TcpClient::sig_Recived, this, [ = ](QByteArray datas)
    {
        this->m_strSN = datas;
        emit on_DataRecived();
    });

    connect(this, &KeyenceBarcodeReader::on_CommandSend, this, [ = ](const QString & str_LON)
    {
        p_Client->Send(str_LON.toLatin1());
    });
}

bool KeyenceBarcodeReader::Read(QString &code)
{
    QString str_LON = "LON\r\n";
    emit on_CommandSend(str_LON);
    static QEventLoop loop;
    bool r = false;
    connect(this, &KeyenceBarcodeReader::on_DataRecived, &loop, [ & ]
    {
        r = true;
        loop.quit();
    });
    QTimer::singleShot(this->m_nTimeout, &loop, [&]
    {
        r = false;
        loop.quit();
    });
    loop.exec();
    code = this->m_strSN;
    qDebug() << "Recieved Sn: " << code;
    return r;
}

bool KeyenceBarcodeReader::ReadwithPos(QString &code, QPointF &pos)
{
    return true;
}
