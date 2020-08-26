QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
    dependencies/MqttDaemon/src \
    dependencies/SimpleIni/include \
    dependencies/ServiceSkeleton/src \
    dependencies/SimpleLog/src \
    dependencies/SimpleFolder/src \
    dependencies/FragFramework/src

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MqttNotification.cpp \
    dependencies/FragFramework/src/StringTools.cpp \
    dependencies/MqttDaemon/src/MqttBase.cpp \
    dependencies/MqttDaemon/src/MqttClient.cpp \
    dependencies/MqttDaemon/src/MqttDaemon.cpp \
    dependencies/ServiceSkeleton/src/Service.cpp \
    dependencies/SimpleFolder/src/SimpleFolders.cpp \
    dependencies/SimpleIni/src/SimpleIni.cpp \
    dependencies/SimpleLog/src/SimpleLog.cpp \
    main.cpp

HEADERS += \
    MqttNotification.h \
    dependencies/FragFramework/src/StringTools.h \
    dependencies/MqttDaemon/src/MqttBase.h \
    dependencies/MqttDaemon/src/MqttClient.h \
    dependencies/MqttDaemon/src/MqttDaemon.h \
    dependencies/ServiceSkeleton/src/Service.h \
    dependencies/SimpleFolder/src/SimpleFolders.h \
    dependencies/SimpleIni/include/SimpleIni.h \
    dependencies/SimpleLog/src/SimpleLog.h \
    dependencies/SimpleLog/src/SimpleLog.inl

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

LIBS += \
    -lpaho-mqtt3a \
    -lpaho-mqttpp3

DISTFILES += \
    README.md
