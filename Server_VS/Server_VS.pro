# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = Server_VS
DESTDIR = ../Win32/Debug
QT += core sql gui widgets websockets
CONFIG += debug
DEFINES += _UNICODE WIN64 QT_DLL QT_WEBSOCKETS_LIB QT_WIDGETS_LIB
INCLUDEPATH += ../../include \
    ./GeneratedFiles \
    . \
    ./GeneratedFiles/$(ConfigurationName)
LIBS += -L"../../lib" \
    -lws2_32 \
    -lactivemq-cpp \
    -llibapr-1 \
    -llibapriconv-1 \
    -llibaprutil-1 \
    -llibeay32 \
    -llibssh2 \
    -lssleay32 \
    -lzlib
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
HEADERS += ./SimpleProducer.h \
    ./param.h \
    ./server_vs.h \
    ./IOCP.h \
    ./PluginManager.h \
    ./PluginInstance.h \
    ./Dictionary.h \
    ./LogWrite.h \
    configwindow.h \
    ConfigWnd.h
SOURCES += ./Dictionary.cpp \
    ./IOCP.cpp \
    ./LogWrite.cpp \
    ./main.cpp \
    ./PluginInstance.cpp \
    ./PluginManager.cpp \
    ./server_vs.cpp \
    ./SimpleProducer.cpp \
    configwindow.cpp \
    ConfigWnd.cpp
FORMS += ./server_vs.ui \
    configwindow.ui \
    ConfigWnd.ui
RESOURCES += server_vs.qrc
