TEMPLATE = app
TARGET = extensionpluginsapps

QT += quick

SOURCES += \
    main.cpp

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH = $$PWD/../pidtoolkitplugin/Pid/Toolkit
#QML_IMPORT_PATH = $$PWD/../pidtoolkitplugin
QML_IMPORT_PATH = $$PWD/../plugins/imports

# Additional import path used to resolve QML modules just for Qt Quick Designer
#QML_DESIGNER_IMPORT_PATH = $$PWD/../pidtoolkitplugin/Pid/Toolkit
#QML_DESIGNER_IMPORT_PATH = $$PWD/../pidtoolkitplugin
QML_DESIGNER_IMPORT_PATH =

target.path = $$OUT_PWD/../install
qml.files = plugins.qml
qml.path += $$OUT_PWD/../install

INSTALLS += target qml

