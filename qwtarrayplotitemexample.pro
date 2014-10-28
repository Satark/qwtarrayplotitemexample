
#use real path to qwt folder (in my system i have QWTDIR enviroment variable defined)
QWT_ROOT = $$(QWTDIR)

TEMPLATE     = app

INCLUDEPATH += $${QWT_ROOT}/src
DEPENDPATH  += $${QWT_ROOT}/src

include($${QWT_ROOT}/qwtfunctions.pri)

QMAKE_RPATHDIR *= $${QWT_ROOT}/lib

LIBS      += -L$${QWT_ROOT}/lib

QT += widgets gui

TARGET = qwtarrayplotitemexample

win32 {
		#comment this line if you are using static qwt build
         DEFINES    += QT_DLL QWT_DLL
    }
	
qwtAddLibrary(qwt)
	
HEADERS = \
    mainwindow.h \ 
	qwtarrayplotitem.h

SOURCES = \
    mainwindow.cpp \
    main.cpp \
	qwtarrayplotitem.cpp
