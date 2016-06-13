#-------------------------------------------------
#
# Project created by QtCreator 2016-02-07T14:45:53
#
#-------------------------------------------------

QT       += core
QT       += network



QT += widgets


TARGET = DiLuz
TEMPLATE = app


SOURCES += main.cpp\
    receiveosc.cpp \
    worker.cpp \
    window.cpp

HEADERS  += receiveosc.h \
    oscpkt.hh \
    worker.h \
    window.h \
    qbouton.h \
    slideh.h \
    multipushbutton.h




DISTFILES += android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/QtActivity.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += ressource.qrc

