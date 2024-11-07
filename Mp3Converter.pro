QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appsettingsdialog.cpp \
    appsettingsmanager.cpp \
    converterprocess.cpp \
    dropframe.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    appsettingsdialog.h \
    appsettingsmanager.h \
    converterprocess.h \
    dropframe.h \
    mainwindow.h

FORMS += \
    appsettingsdialog.ui \
    converterprocess.ui \
    dropframe.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Mp3Converter.qrc


TRANSLATIONS =  languages/audiocv_en.ts \
                languages/audiocv_de.ts \
                languages/audiocv_de.ts \
                languages/audiocv_en.ts \
                languages/audiocv_es.ts \
                languages/audiocv_fr.ts \
                languages/audiocv_fr.ts \
                languages/audiocv_es.ts \
                languages/audiocv_ja.ts \
                languages/audiocv_ja.ts \
                languages/audiocv_ko.ts \
                languages/audiocv_ko.ts \
                languages/audiocv_nl.ts \
                languages/audiocv_nl.ts \
                languages/audiocv_pt.ts \
                languages/audiocv_ru.ts \
                languages/audiocv_ru.ts \
                languages/audiocv_pt.ts \
                languages/audiocv_zh.ts \
                languages/audiocv_zh.ts

DISTFILES += \
    languages/audiocv_de.qm \
    languages/audiocv_en.qm \
    languages/audiocv_es.qm \
    languages/audiocv_fr.qm \
    languages/audiocv_ja.qm \
    languages/audiocv_ko.qm \
    languages/audiocv_nl.qm \
    languages/audiocv_pt.qm \
    languages/audiocv_ru.qm \
    languages/audiocv_zh.qm
