#ifndef BRINFO_H
#define BRINFO_H

#include "BasicValue/point.h"
#include "Serializer/QSerializer"

class S_BRInfo : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_FIELD(int, brID)
    QS_FIELD(QString, code)
    QS_OBJECT(S_Point2D, pos)

public:
    S_BRInfo();
};

#endif // BRINFO_H
