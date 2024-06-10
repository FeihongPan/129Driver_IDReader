#ifndef IBARCODEREADER_H
#define IBARCODEREADER_H

#include "Communication/TCP/tcpclient.h"

#include <QObject>

class IBarcodeReader : public QObject
{
    Q_OBJECT
public:
    explicit IBarcodeReader(const int &id, QObject *parent = nullptr);

    ~IBarcodeReader();

    inline const int &GetID() const;

    inline void SetTimeout(const int &timeout);

    bool Connect(const QString &strIP, const uint16_t &nPort);

    virtual bool Read(QString &code) = 0;

    virtual bool ReadwithPos(QString &code, QPointF &pos) = 0;

protected:
    TcpClient *p_Client = nullptr;

    QString m_strIP;
    QString m_strSN;

    uint16_t m_nPort;
    int m_nID;
    int m_nTimeout = 10000;
};

inline const int &IBarcodeReader::GetID() const
{
    return this->m_nID;
}

inline void IBarcodeReader::SetTimeout(const int &timeout)
{
    this->m_nTimeout = timeout;
}

#endif // IBARCODEREADER_H
