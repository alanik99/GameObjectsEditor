QT       += core gui widgets
CONFIG   += c++11

SOURCES += *.cpp
HEADERS += *.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
