TEMPLATE	= lib
CONFIG		= qt warn_on release
HEADERS = IMPluginSwitcher.h \
    MarsDialog.h \
    U2Panel.h \
    MarsSkinLoader.h \
    PYDB.h
SOURCES += IMPluginSwitcher.cpp \
    MarsDialog.cpp \
    U2Panel.cpp \
    MarsSkinLoader.cpp \
    PYDB.cpp
MOC_DIR = .moc
OBJECTS_DIR = .obj
LIBS+= -lsqlite3
TARGET = ezxinput
