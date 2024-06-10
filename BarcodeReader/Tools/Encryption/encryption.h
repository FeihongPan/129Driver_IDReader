#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "Tools_global.h"

#include <QString>

class TOOLS_EXPORT Encryption
{
public:
    static QString DecodedText(const QString &data, const QString &key);
};

#endif // ENCRYPTION_H
