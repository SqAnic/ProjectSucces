QT += core gui

QT += network #Для работы с сетью

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authform.cpp \
    main.cpp \
    mainwindow.cpp \
    SingletonClient.cpp \
    statistic.cpp \
    task.cpp

HEADERS += \
    authform.h \
    mainwindow.h \
    SingletonClient.h \
    statistic.h \
    task.h

FORMS += \
    authform.ui \
    mainwindow.ui \
    statistic.ui \
    task.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
