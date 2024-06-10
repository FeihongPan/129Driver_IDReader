#Version ver1.0.0
QT -= gui
QT       += network xml

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = CommonLibd
} else {
    TARGET = CommonLib
}

DEFINES += QS_HAS_JSON
DEFINES += QS_HAS_XML

QMAKE_CXXFLAGS_EXCEPTIONS_ON = /EHa
QMAKE_CXXFLAGS_STL_ON = /EHa

include($$PWD/Communication/Communication.pri)
include($$PWD/Logger/Logger.pri)
include($$PWD/TimeSynchronization/TimeSynchronization.pri)
include($$PWD/BasicValue/BasicValue.pri)
include($$PWD/NetworkEquipmentMonitor/NetworkEquipmentMonitor.pri)
include($$PWD/AppConfig/AppConfig.pri)

include($$PWD/../ThirdParties/ThirdParties.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=

HEADERS +=

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Version

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Tools/release/ -lTools
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Tools/debug/ -lToolsd
else:unix:!macx: LIBS += -L$$OUT_PWD/../Tools/ -lTools

INCLUDEPATH += $$PWD/../Tools
DEPENDPATH += $$PWD/../Tools
