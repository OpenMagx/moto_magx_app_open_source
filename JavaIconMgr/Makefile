#############################################################################
# Makefile for building iv
# Generated by tmake at 23:04, 2011/03/12
#     Project: iv
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

HEADERS =	UtilsEnum.h \
		UtilsTaskBase.h \
		UtilsTools.h \
		ZIconView.h \
		ZTaskItem.h \
		appListBox.h \
		deathDlg.h \
		lng.h \
		megabox.h \
		myDef.h \
		source.h
SOURCES =	UtilsTaskBase.cpp \
		UtilsTools.cpp \
		ZTaskItem.cpp \
		appListBox.cpp \
		deathDlg.cpp \
		lng.cpp \
		main.cpp \
		megabox.cpp
OBJECTS =	UtilsTaskBase.o \
		UtilsTools.o \
		ZTaskItem.o \
		appListBox.o \
		deathDlg.o \
		lng.o \
		main.o \
		megabox.o
INTERFACES =	
UICDECLS =	
UICIMPLS =	
SRCMOC	=	moc_ZIconView.cpp \
		moc_appListBox.cpp \
		moc_deathDlg.cpp \
		moc_megabox.cpp
OBJMOC	=	moc_ZIconView.o \
		moc_appListBox.o \
		moc_deathDlg.o \
		moc_megabox.o
DIST	=	
TARGET	=	iv
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

Makefile: iv.pro
	tmake iv.pro -o Makefile

dist:
	$(TAR) iv.tar iv.pro $(SOURCES) $(HEADERS) $(INTERFACES) $(DIST)
	$(GZIP) iv.tar

clean:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS) $(TARGET)
	-rm -f *~ core

####### Sub-libraries


###### Combined headers


####### Compile

UtilsTaskBase.o: UtilsTaskBase.cpp \
		UtilsTaskBase.h \
		myDef.h \
		UtilsEnum.h \
		UtilsTools.h

UtilsTools.o: UtilsTools.cpp \
		UtilsTools.h \
		myDef.h

ZTaskItem.o: ZTaskItem.cpp \
		ZTaskItem.h \
		ZIconView.h \
		myDef.h \
		source.h \
		UtilsEnum.h \
		UtilsTools.h \
		UtilsTaskBase.h

appListBox.o: appListBox.cpp \
		appListBox.h \
		ZTaskItem.h \
		ZIconView.h \
		myDef.h \
		source.h \
		UtilsEnum.h \
		UtilsTools.h \
		UtilsTaskBase.h \
		lng.h

deathDlg.o: deathDlg.cpp \
		deathDlg.h \
		myDef.h

lng.o: lng.cpp \
		lng.h

main.o: main.cpp \
		megabox.h \
		appListBox.h \
		ZTaskItem.h \
		ZIconView.h \
		myDef.h \
		source.h \
		UtilsEnum.h \
		UtilsTools.h \
		UtilsTaskBase.h \
		lng.h

megabox.o: megabox.cpp \
		ZTaskItem.h \
		ZIconView.h \
		myDef.h \
		source.h \
		UtilsEnum.h \
		UtilsTools.h \
		UtilsTaskBase.h \
		megabox.h \
		appListBox.h \
		deathDlg.h \
		lng.h

moc_ZIconView.o: moc_ZIconView.cpp \
		ZIconView.h

moc_appListBox.o: moc_appListBox.cpp \
		appListBox.h \
		ZTaskItem.h \
		ZIconView.h \
		myDef.h \
		source.h \
		UtilsEnum.h \
		UtilsTools.h \
		UtilsTaskBase.h

moc_deathDlg.o: moc_deathDlg.cpp \
		deathDlg.h

moc_megabox.o: moc_megabox.cpp \
		megabox.h \
		appListBox.h \
		ZTaskItem.h \
		ZIconView.h \
		myDef.h \
		source.h \
		UtilsEnum.h \
		UtilsTools.h \
		UtilsTaskBase.h

moc_ZIconView.cpp: ZIconView.h
	$(MOC) ZIconView.h -o moc_ZIconView.cpp

moc_appListBox.cpp: appListBox.h
	$(MOC) appListBox.h -o moc_appListBox.cpp

moc_deathDlg.cpp: deathDlg.h
	$(MOC) deathDlg.h -o moc_deathDlg.cpp

moc_megabox.cpp: megabox.h
	$(MOC) megabox.h -o moc_megabox.cpp

