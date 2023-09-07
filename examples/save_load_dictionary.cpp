/*
 * Copyright 2022 Stéphane Caron
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy
 * of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#include <palimpsest/Dictionary.h>

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>

using palimpsest::Dictionary;

int main() {
  Dictionary things;
  things("foo") = "socket";
  things("bar") = 56u;
  things.write("things.mpack");

  Dictionary things_reloaded;
  things_reloaded.read("things.mpack");
  std::cout << things_reloaded << std::endl;

  return EXIT_SUCCESS;
}
