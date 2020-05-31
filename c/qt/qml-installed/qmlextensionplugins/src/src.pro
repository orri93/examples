TEMPLATE = app
TARGET = extensionpluginsapps

QT += quick

SOURCES += \
    main.cpp

target.path = $$OUT_PWD/../install
qml.files = plugins.qml
qml.path += $$OUT_PWD/../install

INSTALLS += target qml

