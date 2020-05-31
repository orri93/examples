TEMPLATE = lib
CONFIG += plugin
QT += qml
QT += quick


DESTDIR = imports/TimeExample
TARGET  = qmlqtimeexampleplugin

SOURCES += plugin.cpp 

pluginfiles.files += \
    imports/TimeExample/qmldir \
    imports/TimeExample/center.png \
    imports/TimeExample/clock.png \
    imports/TimeExample/Clock.qml \
    imports/TimeExample/hour.png \
    imports/TimeExample/minute.png


target.path = $$OUT_PWD/../install/TimeExample/


qml.files = plugins.qml
qml.path += $$OUT_PWD/../install/TimeExample/
pluginfiles.path += $$OUT_PWD/../install/TimeExample/

INSTALLS += target qml pluginfiles

RESOURCES += \
    imports/TimeExample/qmlqtimeexampleplugin.qrc
