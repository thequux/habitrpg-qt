# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = HabitRPG

CONFIG += sailfishapp
CONFIG += c++11

SOURCES += src/HabitRPG.cpp \
    src/HrpgClient.cpp \
    src/HrpgAuth.cpp

PKGDATA = /usr/share/$$TARGET
pkgdata.path = $$PKGDATA
pkgdata.files += js
pkgdata.files += res

INSTALLS += pkgdata

OTHER_FILES += qml/HabitRPG.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    js/habitrpg.js \
    res/splash.png \
    rpm/HabitRPG.changes.in \
    rpm/HabitRPG.spec \
    rpm/HabitRPG.yaml \
    translations/*.ts \
    HabitRPG.desktop \
    qml/pages/SplashPage.qml

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/HabitRPG-de.ts

HEADERS += \
    src/HrpgClient.h \
    src/HrpgAuth.h

CONFIG(debug, debug|release) {
    DEFINES += HRPG_SERVER=habitrpg.thequux.com:3000
}
CONFIG(release, debug|release) {
    DEFINES += HRPG_SERVER=habitrpg.com
}
