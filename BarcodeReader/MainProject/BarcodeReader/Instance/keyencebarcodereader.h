#ifndef KEYENCEBARCODEREADER_H
#define KEYENCEBARCODEREADER_H

#include "BarcodeReader/Interface/ibarcodereader.h"

#include <QObject>

class KeyenceBarcodeReader : public IBarcodeReader
{
    Q_OBJECT

public:
    explicit KeyenceBarcodeReader(const int &id, QObject *parent = nullptr);

    virtual bool Read(QString &code) override;

    virtual bool ReadwithPos(QString &code, QPointF &pos) override;

signals:
    void on_DataRecived();
    void on_CommandSend(const QString &str_LON);
};

#endif // KEYENCEBARCODEREADER_H
