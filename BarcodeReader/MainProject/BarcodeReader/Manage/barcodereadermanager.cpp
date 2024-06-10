#include "barcodereadermanager.h"
#include "BarcodeReader/Data/brinfo.h"
#include "BarcodeReader/Command/cmd_br.h"

#include "Converter/enumconverter.h"

BarcodeReaderManager *BarcodeReaderManager::self = nullptr;

BarcodeReaderManager::BarcodeReaderManager(QString name, QObject *parent) : IMqttClient(name, parent)
{

}

BarcodeReaderManager::~BarcodeReaderManager()
{

}

BarcodeReaderManager *BarcodeReaderManager::getInstance()
{
    if(nullptr == self)
    {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if(nullptr == self)
        {
            self = new BarcodeReaderManager("BarcodeReaderManager");
        }
    }
    return self;
}

bool BarcodeReaderManager::RegisterBarcodeReader(IBarcodeReader *pIBarcodeReader)
{
    if(pIBarcodeReader == nullptr)
    {
        return false;
    }

    if(p_dic_BarcodeReader.contains(pIBarcodeReader->GetID()))
    {
        return false;
    }

    p_dic_BarcodeReader.insert(pIBarcodeReader->GetID(), pIBarcodeReader);
    return true;
}

bool BarcodeReaderManager::Read(int id)
{
    S_BRInfo info;
    info.brID = id;
    bool res = p_dic_BarcodeReader[id]->Read(info.code);
    Publish(EnumConverter::ConvertToString(CMD_BR::CMD_Read), res, info.toRawJson());
    return res;
}

bool BarcodeReaderManager::ReadwithPos(int id)
{
    S_BRInfo info;
    info.brID = id;
    QPointF point;
    bool res = p_dic_BarcodeReader[id]->ReadwithPos(info.code, point);
    info.pos = point;
    Publish(EnumConverter::ConvertToString(CMD_BR::CMD_Read), res, info.toRawJson());
    return res;
}

void BarcodeReaderManager::decoding(const QString &task, bool result, const QByteArray &msg, const QByteArray &errMsg)
{
    S_BRInfo info;
    info.fromJson(msg);
    CMD_BR::Command cmd = EnumConverter::ConvertStringToEnum<CMD_BR::Command>(task);

    switch(cmd)
    {
        case CMD_BR::Command::CMD_Read:
            Read(info.brID);
            break;

        case CMD_BR::Command::CMD_ReadwithPos:
            ReadwithPos(info.brID);
            break;

        default:
            break;
    }
}
