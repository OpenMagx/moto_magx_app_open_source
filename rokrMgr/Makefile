#############################################################################
# Makefile for building RokrMgr
# Generated by tmake at 12:44, 2011/04/13
#     Project: RokrMgr
#    Template: app
#############################################################################

####### Compiler, tools and options

CC	=	arm-linux-gnueabi-gcc
CXX	=	arm-linux-gnueabi-g++
CFLAGS	=	-pipe -Wall -W -O3 -DNO_DEBUG
CXXFLAGS=	-pipe -DQWS -fno-exceptions -fno-rtti -Wall -W -O3 -DNO_DEBUG
INCPATH	=	-I$(QTDIR)/include
LINK	=	arm-linux-gnueabi-gcc
LFLAGS	=	-Wl,-rpath,$(QTDIR)/lib
LIBS	=	$(SUBLIBS) -L$(QTDIR)/lib -lm -lqte-mt -lezxappbase -lezxam
MOC	=	$(QTDIR)/bin/moc
UIC	=	$(QTDIR)/bin/uic

TAR	=	tar -cf
GZIP	=	gzip -9f

####### Files

HEADERS =	BaseDlg.h \
		ThemeSettingView.h \
		deathDlg.h \
		lng.h \
		mediaBrowser.h \
		myDef.h \
		rokrmgr.h \
		saveDlg.h \
		tool.h
SOURCES =	BaseDlg.cpp \
		ThemeSettingView.cpp \
		deathDlg.cpp \
		lng.cpp \
		main.cpp \
		medaiBrowser.cpp \
		rokrmgr.cpp \
		saveDlg.cpp \
		tool.cpp
OBJECTS =	BaseDlg.o \
		ThemeSettingView.o \
		deathDlg.o \
		lng.o \
		main.o \
		medaiBrowser.o \
		rokrmgr.o \
		saveDlg.o \
		tool.o
INTERFACES =	
UICDECLS =	
UICIMPLS =	
SRCMOC	=	moc_BaseDlg.cpp \
		moc_ThemeSettingView.cpp \
		moc_deathDlg.cpp \
		moc_mediaBrowser.cpp \
		moc_rokrmgr.cpp \
		moc_saveDlg.cpp
OBJMOC	=	moc_BaseDlg.o \
		moc_ThemeSettingView.o \
		moc_deathDlg.o \
		moc_mediaBrowser.o \
		moc_rokrmgr.o \
		moc_saveDlg.o
DIST	=	
TARGET	=	RokrMgr
INTERFACE_DECL_PATH = .

####### Implicit rules

.SUFFIXES: .cpp .cxx .cc .C .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules


all: $(TARGET)

$(TARGET): $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(LIBS)

moc: $(SRCMOC)

tmake: Makefile

Makefile: RokrMgr.pro
	tmake RokrMgr.pro -o Makefile

dist:
	$(TAR) RokrMgr.tar RokrMgr.pro $(SOURCES) $(HEADERS) $(INTERFACES) $(DIST)
	$(GZIP) RokrMgr.tar

clean:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS) $(TARGET)
	-rm -f *~ core

####### Sub-libraries


###### Combined headers


####### Compile

BaseDlg.o: BaseDlg.cpp \
		BaseDlg.h

ThemeSettingView.o: ThemeSettingView.cpp \
		ThemeSettingView.h \
		BaseDlg.h \
		mediaBrowser.h \
		lng.h

deathDlg.o: deathDlg.cpp \
		deathDlg.h \
		tool.h

lng.o: lng.cpp \
		lng.h

main.o: main.cpp \
		rokrmgr.h \
		lng.h

medaiBrowser.o: medaiBrowser.cpp \
		mediaBrowser.h \
		lng.h \
		myDef.h

rokrmgr.o: rokrmgr.cpp \
		rokrmgr.h \
		tool.h \
		deathDlg.h \
		myDef.h \
		lng.h \
		ThemeSettingView.h \
		BaseDlg.h \
		saveDlg.h

saveDlg.o: saveDlg.cpp \
		saveDlg.h \
		lng.h \
		myDef.h

tool.o: tool.cpp \
		tool.h

moc_BaseDlg.o: moc_BaseDlg.cpp \
		BaseDlg.h

moc_ThemeSettingView.o: moc_ThemeSettingView.cpp \
		ThemeSettingView.h \
		BaseDlg.h

moc_deathDlg.o: moc_deathDlg.cpp \
		deathDlg.h

moc_mediaBrowser.o: moc_mediaBrowser.cpp \
		mediaBrowser.h

moc_rokrmgr.o: moc_rokrmgr.cpp \
		rokrmgr.h

moc_saveDlg.o: moc_saveDlg.cpp \
		saveDlg.h \
		lng.h

moc_BaseDlg.cpp: BaseDlg.h
	$(MOC) BaseDlg.h -o moc_BaseDlg.cpp

moc_ThemeSettingView.cpp: ThemeSettingView.h
	$(MOC) ThemeSettingView.h -o moc_ThemeSettingView.cpp

moc_deathDlg.cpp: deathDlg.h
	$(MOC) deathDlg.h -o moc_deathDlg.cpp

moc_mediaBrowser.cpp: mediaBrowser.h
	$(MOC) mediaBrowser.h -o moc_mediaBrowser.cpp

moc_rokrmgr.cpp: rokrmgr.h
	$(MOC) rokrmgr.h -o moc_rokrmgr.cpp

moc_saveDlg.cpp: saveDlg.h
	$(MOC) saveDlg.h -o moc_saveDlg.cpp

