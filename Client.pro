QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#INSTALLS += openssl
#LIBS += -LC:\Users\DANIL\Documents\secrurityTCP\ -llibcrypto-1_1-x64
#LIBS += -LC:\Users\DANIL\Documents\secrurityTCP\ -llibcrypto-3-x64
#LIBS += -LC:\Users\DANIL\Documents\secrurityTCP\ -llibssl-1_1-x64
#LIBS += -LC:\Users\DANIL\Documents\secrurityTCP\ -llibssl-3-x64


CONFIG(release, debug|release): openssl.path = $$OUT_PWD/release
else:CONFIG(debug, debug|release): openssl.path = $$OUT_PWD/debug
openssl.files += $$PWD/../openssl/*.dll

include(/android_openssl/openssl.pri)



SOURCES += \
    chess_engine.cpp \
    clientglobal.cpp \
    form_game.cpp \
    form_group.cpp \
    form_groups.cpp \
    form_logReg.cpp \
    form_pass.cpp \
    form_settings.cpp \
    form_user.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    moveitem.cpp \
    network_object.cpp \
    userdata.cpp

HEADERS += \
    chess_engine.h \
    clientglobal.h \
    form_game.h \
    form_group.h \
    form_groups.h \
    form_logReg.h \
    form_pass.h \
    form_settings.h \
    form_user.h \
    mainmenu.h \
    mainwindow.h \
    moveitem.h \
    network_object.h \
    userdata.h

FORMS += \
    form_game.ui \
    form_group.ui \
    form_groups.ui \
    form_logReg.ui \
    form_pass.ui \
    form_settings.ui \
    form_user.ui \
    mainmenu.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
   res/res.qrc
