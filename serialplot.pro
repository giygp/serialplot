#
# Copyright © 2025 Hasan Yavuz Özderya
#
# This file is part of serialplot.
#
# serialplot is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# serialplot is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with serialplot.  If not, see <http://www.gnu.org/licenses/>.
#

#-------------------------------------------------
#
# Project created by QtCreator 2015-03-04T08:20:06
#
#-------------------------------------------------

QT       += core gui serialport network svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serialplot
TEMPLATE = app

# CONFIG += qwt
# LIBS += -lqwt # enable this line if qwt pri files aren't installed

# Qwt library built from source (qwt-6.3.0) with Qt 6.8.3 MinGW
INCLUDEPATH += $$PWD/qwt-6.3.0/src
LIBS        += -L$$PWD/build/lib -lqwt
DEFINES     += QWT_DLL

DEFINES += PROGRAM_NAME="\\\"serialplot\\\""

DEFINES += VERSION_MAJOR=10 VERSION_MINOR=0 VERSION_PATCH=0 VERSION_STRING=\\\"10.0.0\\\"

SOURCES += \
    src/main.cpp \
    src/app/mainwindow.cpp \
    src/core/channelinfomodel.cpp \
    src/core/samplecounter.cpp \
    src/core/samplepack.cpp \
    src/core/sink.cpp \
    src/core/source.cpp \
    src/core/stream.cpp \
    src/core/streamchannel.cpp \
    src/buffers/framebufferseries.cpp \
    src/buffers/indexbuffer.cpp \
    src/buffers/linindexbuffer.cpp \
    src/buffers/readonlybuffer.cpp \
    src/buffers/ringbuffer.cpp \
    src/readers/abstractreader.cpp \
    src/readers/asciireader.cpp \
    src/readers/asciireadersettings.cpp \
    src/readers/binarystreamreader.cpp \
    src/readers/binarystreamreadersettings.cpp \
    src/readers/dataformatpanel.cpp \
    src/readers/demoreader.cpp \
    src/readers/demoreadersettings.cpp \
    src/readers/framedreader.cpp \
    src/readers/framedreadersettings.cpp \
    src/plot/barplot.cpp \
    src/plot/barchart.cpp \
    src/plot/barscaledraw.cpp \
    src/plot/plot.cpp \
    src/plot/plotsnapshotoverlay.cpp \
    src/plot/plotcontrolpanel.cpp \
    src/plot/plotmanager.cpp \
    src/plot/plotmenu.cpp \
    src/plot/scalepicker.cpp \
    src/plot/scalezoomer.cpp \
    src/plot/scrollbar.cpp \
    src/plot/scrollzoomer.cpp \
    src/plot/zoomer.cpp \
    src/connect/bpslabel.cpp \
    src/connect/portcontrol.cpp \
    src/connect/portlist.cpp \
    src/connect/tcpcontrol.cpp \
    src/snapshot/snapshot.cpp \
    src/snapshot/snapshotmanager.cpp \
    src/snapshot/snapshotview.cpp \
    src/record/datarecorder.cpp \
    src/record/datatextview.cpp \
    src/record/recordpanel.cpp \
    src/command/commandedit.cpp \
    src/command/commandpanel.cpp \
    src/command/commandwidget.cpp \
    src/widgets/endiannessbox.cpp \
    src/widgets/hidabletabwidget.cpp \
    src/widgets/ledwidget.cpp \
    src/widgets/numberformat.cpp \
    src/widgets/numberformatbox.cpp \
    src/widgets/sneakylineedit.cpp \
    src/widgets/tooltipfilter.cpp \
    src/update/updatecheckdialog.cpp \
    src/update/updatechecker.cpp \
    src/update/versionnumber.cpp

HEADERS += \
    src/app/mainwindow.h \
    src/app/defines.h \
    src/app/setting_defines.h \
    src/app/version.h \
    src/core/channelinfomodel.h \
    src/core/samplecounter.h \
    src/core/samplepack.h \
    src/core/sink.h \
    src/core/source.h \
    src/core/stream.h \
    src/core/streamchannel.h \
    src/buffers/framebuffer.h \
    src/buffers/framebufferseries.h \
    src/buffers/indexbuffer.h \
    src/buffers/linindexbuffer.h \
    src/buffers/readonlybuffer.h \
    src/buffers/ringbuffer.h \
    src/readers/abstractreader.h \
    src/readers/asciireader.h \
    src/readers/asciireadersettings.h \
    src/readers/binarystreamreader.h \
    src/readers/binarystreamreadersettings.h \
    src/readers/dataformatpanel.h \
    src/readers/demoreader.h \
    src/readers/demoreadersettings.h \
    src/readers/framedreader.h \
    src/readers/framedreadersettings.h \
    src/plot/barplot.h \
    src/plot/barchart.h \
    src/plot/barscaledraw.h \
    src/plot/plot.h \
    src/plot/plotsnapshotoverlay.h \
    src/plot/plotcontrolpanel.h \
    src/plot/plotmanager.h \
    src/plot/plotmenu.h \
    src/plot/scalepicker.h \
    src/plot/scalezoomer.h \
    src/plot/scrollbar.h \
    src/plot/scrollzoomer.h \
    src/plot/zoomer.h \
    src/connect/bpslabel.h \
    src/connect/portcontrol.h \
    src/connect/portlist.h \
    src/connect/tcpcontrol.h \
    src/snapshot/snapshot.h \
    src/snapshot/snapshotmanager.h \
    src/snapshot/snapshotview.h \
    src/record/datarecorder.h \
    src/record/datatextview.h \
    src/record/recordpanel.h \
    src/command/commandedit.h \
    src/command/commandpanel.h \
    src/command/commandwidget.h \
    src/widgets/endiannessbox.h \
    src/widgets/hidabletabwidget.h \
    src/widgets/ledwidget.h \
    src/widgets/numberformat.h \
    src/widgets/numberformatbox.h \
    src/widgets/sneakylineedit.h \
    src/widgets/tooltipfilter.h \
    src/update/updatecheckdialog.h \
    src/update/updatechecker.h \
    src/update/versionnumber.h

FORMS += \
    src/app/mainwindow.ui \
    src/app/about_dialog.ui \
    src/readers/dataformatpanel.ui \
    src/readers/framedreadersettings.ui \
    src/readers/binarystreamreadersettings.ui \
    src/readers/asciireadersettings.ui \
    src/readers/demoreadersettings.ui \
    src/plot/plotcontrolpanel.ui \
    src/connect/portcontrol.ui \
    src/connect/tcpcontrol.ui \
    src/snapshot/snapshotview.ui \
    src/record/recordpanel.ui \
    src/record/datatextview.ui \
    src/command/commandpanel.ui \
    src/command/commandwidget.ui \
    src/widgets/numberformatbox.ui \
    src/widgets/endiannessbox.ui \
    src/update/updatecheckdialog.ui

INCLUDEPATH += qmake/ src/

CONFIG += c++11

RESOURCES += misc/icons.qrc

win32 {
    RESOURCES += misc/winicons.qrc
}
