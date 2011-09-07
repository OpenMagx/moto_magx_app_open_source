TEMPLATE	= app
CONFIG		= qt warn_on release
HEADERS		= EZX_TypeDefs.h \
		  NAPI/NAPILink.h \
		  NAPI/NAPIManager.h \
		  citySelectDlg.h \
		  forecastData.h \
		  header/ZDataSessionManager.h \
		  header/napi.h \
		  structureparser.h \
		  weather.h \
		  weatherData.h
SOURCES		= NAPI/NAPILink.cpp \
		  NAPI/NAPIManager.cpp \
		  citySelectDlg.cpp \
		  main.cpp \
		  structureparser.cpp \
		  weather.cpp
INTERFACES	= 
