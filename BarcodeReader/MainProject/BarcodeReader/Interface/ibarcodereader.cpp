#include "ibarcodereader.h"

IBarcodeReader::IBarcodeReader(const int &id, QObject *parent) : QObject(parent)
{
    this->m_nID = id;
    p_Client = new TcpClient();
}

IBarcodeReader::~IBarcodeReader()
{
    if(p_Client != nullptr)
    {
        p_Client = nullptr;
        delete p_Client;
    }
}

bool IBarcodeReader::Connect(const QString &strIP, const uint16_t &nPort)
{
    this->m_strIP = strIP;
    this->m_nPort = nPort;
    return p_Client->Connect(strIP, nPort);
}
