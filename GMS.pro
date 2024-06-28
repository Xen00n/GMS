QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    booking_page.cpp \
    cancel_page.cpp \
    loginpage.cpp \
    main.cpp \
    mainpage.cpp \
    mainwindow.cpp \
    view_page.cpp

HEADERS += \
    booking_page.h \
    cancel_page.h \
    loginpage.h \
    mainpage.h \
    mainwindow.h \
    view_page.h

FORMS += \
    booking_page.ui \
    cancel_page.ui \
    loginpage.ui \
    mainpage.ui \
    mainwindow.ui \
    view_page.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
