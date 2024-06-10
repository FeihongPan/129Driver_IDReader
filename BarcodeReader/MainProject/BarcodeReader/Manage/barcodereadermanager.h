#ifndef BARCODEREADERMANAGER_H
#define BARCODEREADERMANAGER_H

#include "BarcodeReader/Interface/ibarcodereader.h"

#include "Communication/MQTT/imqttclient.h"

#include <QObject>

class BarcodeReaderManager : public IMqttClient
{
    Q_OBJECT

public:
    ~BarcodeReaderManager();

    static BarcodeReaderManager *getInstance();

    bool RegisterBarcodeReader(IBarcodeReader *pIBarcodeReader);

    bool Read(int id);

    bool ReadwithPos(int id);

private:
    explicit BarcodeReaderManager(QString name, QObject *parent = nullptr);
    BarcodeReaderManager(const BarcodeReaderManager &instance) = delete;
    BarcodeReaderManager &operator=(const BarcodeReaderManager &instance) = delete;

    virtual void decoding(const QString &task, bool result, const QByteArray &msg, const QByteArray &errMsg);

private:
    static BarcodeReaderManager *self;

    QMap<int, IBarcodeReader *> p_dic_BarcodeReader;
};

#endif // BARCODEREADERMANAGER_H
