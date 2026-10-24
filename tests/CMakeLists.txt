#
# Copyright © 2018 Hasan Yavuz Özderya
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

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Test)

include_directories("../src")

add_executable(Test EXCLUDE_FROM_ALL
  test.cpp
  test_stream.cpp
  ../src/core/samplepack.cpp
  ../src/core/sink.cpp
  ../src/core/source.cpp
  ../src/buffers/indexbuffer.cpp
  ../src/buffers/linindexbuffer.cpp
  ../src/buffers/ringbuffer.cpp
  ../src/buffers/readonlybuffer.cpp
  ../src/core/stream.cpp
  ../src/core/streamchannel.cpp
  ../src/core/channelinfomodel.cpp
  )
add_test(NAME test1 COMMAND Test)
qt5_use_modules(Test Widgets)

qt5_wrap_ui(UI_FILES_T
  ../src/readers/binarystreamreadersettings.ui
  ../src/readers/asciireadersettings.ui
  ../src/readers/framedreadersettings.ui
  ../src/readers/demoreadersettings.ui
  ../src/widgets/numberformatbox.ui
  ../src/widgets/endiannessbox.ui
  )

# test for readers
add_executable(TestReaders EXCLUDE_FROM_ALL
  test_readers.cpp
  ../src/core/samplepack.cpp
  ../src/core/sink.cpp
  ../src/core/source.cpp
  ../src/readers/abstractreader.cpp
  ../src/readers/binarystreamreader.cpp
  ../src/readers/binarystreamreadersettings.cpp
  ../src/readers/asciireader.cpp
  ../src/readers/asciireadersettings.cpp
  ../src/readers/framedreader.cpp
  ../src/readers/framedreadersettings.cpp
  ../src/readers/demoreader.cpp
  ../src/readers/demoreadersettings.cpp
  ../src/command/commandedit.cpp
  ../src/widgets/endiannessbox.cpp
  ../src/widgets/numberformatbox.cpp
  ../src/widgets/numberformat.cpp
  ${UI_FILES_T}
  )
qt5_use_modules(TestReaders Widgets Test)
add_test(NAME test_readers COMMAND TestReaders)

# test for recroder
add_executable(TestRecorder EXCLUDE_FROM_ALL
  test_recorder.cpp
  ../src/core/samplepack.cpp
  ../src/core/sink.cpp
  ../src/core/source.cpp
  ../src/record/datarecorder.cpp
)
qt5_use_modules(TestRecorder Widgets Test)
add_test(NAME test_recorder COMMAND TestRecorder)

set(CMAKE_CTEST_COMMAND ctest -V)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
add_dependencies(check
  Test
  TestReaders
  TestRecorder
  )
