QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Amino.cpp \
    Atom.cpp \
    Chain.cpp \
    Graph.cpp \
    Model.cpp \
    PDB.cpp \
    Parser.cpp \
    To_Graph.cpp \
    customdialog.cpp \
    customlistmodel.cpp \
    form.cpp \
    form2.cpp \
    main.cpp \
    mainwindow.cpp \
    result.cpp \
    switch.cpp

HEADERS += \
    Amino.h \
    Atom.h \
    Chain.h \
    Graph.h \
    Model.h \
    PDB.h \
    Parser.h \
    To_Graph.h \
    customdialog.h \
    customlistmodel.h \
    form.h \
    form2.h \
    mainwindow.h \
    result.h \
    style.h \
    switch.h

FORMS += \
    form.ui \
    form2.ui \
    mainwindow.ui \
    result.ui

TRANSLATIONS += \
    Matching_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    blue-background.jpg \
    pf-misctexture01-beer-000_5.jpg

RESOURCES += \
    Resource.qrc
