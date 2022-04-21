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

add_library(third_party_mpack
    mpack/src/mpack/mpack-common.c
    mpack/src/mpack/mpack-common.h
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
)
