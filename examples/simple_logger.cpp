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

#include <fstream>
#include <iostream>

const std::string output_file = "simple_logger.mpack";

using palimpsest::Dictionary;

//! Log dictionaries to file.
class SimpleLogger {
 public:
  /*! Open file to log to.
   *
   * \param[in] path Path to log file.
   */
  explicit SimpleLogger(const std::string &path) {
    file_.open(path, std::ofstream::binary);
    if (!file_) {
      throw std::runtime_error("Cannot open " + path + " for writing");
    }
  }

  //! Close log file.
  ~SimpleLogger() { file_.close(); }

  /*! Write a dictionary to the log.
   *
   * \param dict Dictionary to write.
   */
  void write(const Dictionary &dict) {
    size_t size = dict.serialize(serialization_buffer_);
    file_.write(serialization_buffer_.data(), static_cast<int>(size));
    file_.flush();
  }

 private:
  //! Output file stream.
  std::ofstream file_;

  //! Internal buffer used by \ref write(const Dictionary&).
  std::vector<char> serialization_buffer_;
};

int main() {
  Dictionary world;
  SimpleLogger logger(output_file);
  world("temperature") = 28.0;
  for (unsigned iter = 0; iter < 42; ++iter) {
    double &temperature = world("temperature");
    const double u = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    const double noise = (u - 0.5) / 0.5;  // between -1.0 and +1.0
    temperature += 0.1 * noise;
    logger.write(world);
  }
  std::cout << "All dictionaries written to " << output_file << std::endl;
  return EXIT_SUCCESS;
}
