# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = Server_VS
DESTDIR = ../Win32/Release
QT += core sql network gui widgets websockets
CONFIG += release
DEFINES += _UNICODE WIN64 QT_DLL QT_WEBSOCKETS_LIB QT_WIDGETS_LIB
INCLUDEPATH += ./../include \
    ./GeneratedFiles \
    . \
    ./GeneratedFiles/$(ConfigurationName)
LIBS += -L"./../lib" \
    -lws2_32 \
    -lactivemq-cpp \
    -llibapr-1 \
    -llibapriconv-1 \
    -llibaprutil-1 \
    -llibeay32 \
    -llibssh2 \
    -lssleay32 \
    -lzlib \
    -lIphlpapi
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(Server_VS.pri)
