# CMakeLists.txt -- Build system for palimpsest
#
# Copyright 2022 Stéphane Caron
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

add_library(mpack SHARED
    mpack/src/mpack/mpack-common.c
    mpack/src/mpack/mpack-common.h
    mpack/src/mpack/mpack-defaults.h
    mpack/src/mpack/mpack-expect.c
    mpack/src/mpack/mpack-expect.h
    mpack/src/mpack/mpack-node.c
    mpack/src/mpack/mpack-node.h
    mpack/src/mpack/mpack-platform.c
    mpack/src/mpack/mpack-platform.h
    mpack/src/mpack/mpack-reader.c
    mpack/src/mpack/mpack-reader.h
    mpack/src/mpack/mpack-writer.c
    mpack/src/mpack/mpack-writer.h
    mpack/src/mpack/mpack.h
)

target_sources(mpack PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/mpack/src/mpack/mpack-common.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mpack/src/mpack/mpack-defaults.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mpack/src/mpack/mpack-expect.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mpack/src/mpack/mpack-node.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mpack/src/mpack/mpack-platform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mpack/src/mpack/mpack-reader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mpack/src/mpack/mpack-writer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mpack/src/mpack/mpack.h
)

get_target_property(MPACK_PUBLIC_HEADERS mpack INTERFACE_SOURCES)
set_target_properties(mpack PROPERTIES PUBLIC_HEADER "${MPACK_PUBLIC_HEADERS}")

install(TARGETS mpack
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
