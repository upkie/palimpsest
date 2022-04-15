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

#pragma once

#include <string>

namespace palimpsest {

class PalimpsestError : public std::runtime_error {
 public:
  /*! Create a new error.
   *
   * \param[in] message Error message.
   */
  PalimpsestError(const std::string& message, const std::string& file,
                  unsigned line)
      : std::runtime_error(message) {
    std::ostringstream out;
    out << "[" << file << ":" << line << "] " << message;
    message_ = out.str();
  }

  PalimpsestError(const PalimpsestError& other,
                  const std::string& extra_message)
      : std::runtime_error(other.message_ + extra_message),
        message_(other.message_ + extra_message) {}

  ~PalimpsestError() throw() {}

  //! Error message
  const char* what() const throw() { return message_.c_str(); }

 private:
  //! Complete error message
  std::string message_;
};

}  // namespace palimpsest
