Release:DESTDIR = ../bin/release
Release:OBJECTS_DIR = ../bin/release/.obj
Release:MOC_DIR = ../bin/release/.moc
Release:RCC_DIR = ../bin/release/.rcc
Release:UI_DIR = ../bin/release/.ui

Debug:DESTDIR = ../bin/debug
Debug:OBJECTS_DIR = ../bin/debug/.obj
Debug:MOC_DIR = ../bin/debug/.moc
Debug:RCC_DIR = ../bin/debug/.rcc
Debug:UI_DIR = ../bin/debug/.ui

TEMPLATE = app
TARGET = AsciiBitmapEditor
DEPENDPATH += ../resources ../source ../build/GeneratedFiles
INCLUDEPATH += ../source

# Input
HEADERS += ../source/backgroundcolortool.h \
           ../source/backgroundcolortoolundoaction.h \
           ../source/bitmap.h \
           ../source/bitmapeditor.h \
           ../source/bitmapexporter.h \
           ../source/bitmapresizedialog.h \
           ../source/bitmapserializer.h \
           ../source/colortool.h \
           ../source/documentwrapper.h \
           ../source/drawingtool.h \
           ../source/drawingtoolundoaction.h \
           ../source/foregroundcolortool.h \
           ../source/foregroundcolortoolundoaction.h \
           ../source/mainwindow.h \
           ../source/tool.h \
           ../source/toolpalette.h \
           ../source/toolundoaction.h \
           ../source/version.h
           
           
FORMS += ../source/bitmapresizedialog.ui ../source/mainwindow.ui


SOURCES += ../source/backgroundcolortool.cpp \
           ../source/backgroundcolortoolundoaction.cpp \
           ../source/bitmap.cpp \
           ../source/bitmapeditor.cpp \
           ../source/bitmapexporter.cpp \
           ../source/bitmapresizedialog.cpp \
           ../source/bitmapserializer.cpp \
           ../source/colortool.cpp \
           ../source/documentwrapper.cpp \
           ../source/drawingtool.cpp \
           ../source/drawingtoolundoaction.cpp \
           ../source/foregroundcolortool.cpp \
           ../source/foregroundcolortoolundoaction.cpp \
           ../source/main.cpp \
           ../source/mainwindow.cpp \
           ../source/toolpalette.cpp
           
RESOURCES += ../resources/resources.qrc
