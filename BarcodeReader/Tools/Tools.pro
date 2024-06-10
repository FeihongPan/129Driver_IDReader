QT -= gui
QT += xml

TEMPLATE = lib
DEFINES += TOOLS_LIBRARY

CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = Toolsd
} else {
    TARGET = Tools
}

DEFINES += QS_HAS_JSON
DEFINES += QS_HAS_XML

include($$PWD/Serializer/qserializer.pri)
include($$PWD/Encryption/Encryption.pri)
include($$PWD/DeviceRecognize/DeviceRecognize.pri)
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Converter/enumconverter.cpp \
    FileSystem/fileoperatormanager.cpp \
    FileSystem/filesystem.cpp \
    FileSystem/ifileoperator.cpp \
    Language/language.cpp

HEADERS += \
    Converter/enumconverter.h \
    FileSystem/fileoperatormanager.h \
    FileSystem/filesystem.h \
    FileSystem/ifileoperator.h \
    FileSystem/utils.h \
    Language/language.h \
    Tools_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

CONFIG(debug,debug|release){
    DLLDESTDIR = $$OUT_PWD/../MainProject/debug
} else {
    DLLDESTDIR = $$OUT_PWD/../MainProject/release
}

DISTFILES += \
    Version
