CONFIG += qt debug

HEADERS += includes/globaldefs.h \
	includes/glwidget.h \ 
	includes/treedrawer.h \
	includes/window.h

SOURCES += src/treeimpl.cpp \
	src/main.cpp \
	src/window.cpp \
	src/glwidget.cpp \
	src/treedrawer.cpp
	
INCLUDEPATH += ./includes

QT += widgets