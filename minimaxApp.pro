QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += moc  # Добавлено для явного указания на использование MOC

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    TreeNode.cpp \
    algo_minimax.cpp \
    inputParametr.cpp \
    main.cpp \
    mainApplication.cpp \
    mainwindow.cpp \
    startProgram.cpp \
    visualizer.cpp \
    windowProcessControler.cpp

HEADERS += \
    TreeNode.h \
    algo_minimax.h \
    inputParametr.h \
    mainApplication.h \
    mainwindow.h \
    startProgram.h \
    visualizer.h \
    windowProcessControler.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
