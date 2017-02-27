TEMPLATE = app
TARGET = camera

QT += multimedia multimediawidgets

HEADERS = \
    camera.h \
    imagesettings.h

SOURCES = \
    main.cpp \
    camera.cpp \
    imagesettings.cpp

FORMS += \
    camera.ui \
    imagesettings.ui

# nbtarget.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/camera
# INSTALLS += target

QT+=widgets
