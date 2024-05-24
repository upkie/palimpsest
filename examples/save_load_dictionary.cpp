// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 Stéphane Caron

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
