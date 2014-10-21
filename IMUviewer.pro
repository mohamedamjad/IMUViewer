#-------------------------------------------------
#
# Project created by QtCreator 2014-10-17T09:05:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = IMUviewer
CONFIG   += console
CONFIG   -= app_bundle


#Prise en compte de l'ISO C++ 2011


TEMPLATE = app


SOURCES += main.cpp \
    traitementsignal.cpp \
    csv.cpp \
    quaternion.cpp \
    tests.cpp

HEADERS += \
    traitementsignal.h \
    csv.h \
    quaternion.h \
    tests.h





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/lib/release/ -lAquila
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/lib/debug/ -lAquila
else:unix: LIBS += -L$$PWD/lib/lib/ -lAquila

INCLUDEPATH += $$PWD/lib/include
DEPENDPATH += $$PWD/lib/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/lib/release/libAquila.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/lib/debug/libAquila.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/lib/release/Aquila.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/lib/debug/Aquila.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/lib/libAquila.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/lib/release/ -lUnitTest++
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/lib/debug/ -lUnitTest++
else:unix: LIBS += -L$$PWD/lib/lib/ -lUnitTest++

INCLUDEPATH += $$PWD/lib/include
DEPENDPATH += $$PWD/lib/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/lib/release/libUnitTest++.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/lib/debug/libUnitTest++.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/lib/release/UnitTest++.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/lib/debug/UnitTest++.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/lib/libUnitTest++.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/lib/release/ -lOoura_fft
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/lib/debug/ -lOoura_fft
else:unix: LIBS += -L$$PWD/lib/lib/ -lOoura_fft

INCLUDEPATH += $$PWD/lib/include
DEPENDPATH += $$PWD/lib/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/lib/release/libOoura_fft.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/lib/debug/libOoura_fft.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/lib/release/Ooura_fft.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/lib/debug/Ooura_fft.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/lib/libOoura_fft.a
