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

//! Error with file and line references to the calling code.
class InternalError : public std::runtime_error {
 public:
  /*! Create a new error.
   *
   * \param[in] file Source file of the instruction that threw the error.
   * \param[in] line Line of code in that file where the throw originates from.
   * \param[in] message Error message.
   */
  InternalError(const std::string& file, unsigned line,
                const std::string& message)
      : std::runtime_error(message) {
    std::ostringstream out;
    out << "[" << file << ":" << line << "] " << message;
    message_ = out.str();
  }

  /*! Copy an existing error, adding to the error message.
   *
   * \param[in] other Existing error.
   * \param[in] extra_message Additional error message.
   */
  InternalError(const InternalError& other, const std::string& extra_message)
      : std::runtime_error(other.message_ + extra_message),
        message_(other.message_ + extra_message) {}

  //! Empty destructor
  ~InternalError() throw() {}

  //! Error message
  const char* what() const throw() { return message_.c_str(); }

 private:
  //! Complete error message
  std::string message_;
};

//! Requested type doesn't match the one already in the dictionary.
class TypeError : public InternalError {
 public:
  /*! Create a type error.
   *
   * \param[in] file Source file of the instruction that threw the error.
   * \param[in] line Line of code in that file where the throw originates from.
   * \param[in] message Error message.
   */
  TypeError(const std::string& file, unsigned line, const std::string& message)
      : InternalError(file, line, message) {}

  /*! Copy an existing error, adding to the error message.
   *
   * \param[in] other Existing error.
   * \param[in] extra_message Additional error message.
   */
  TypeError(const TypeError& other, const std::string& extra_message)
      : InternalError(other, extra_message) {}

  //! Empty destructor
  ~TypeError() throw() {}
};

//! Requested dictionary key is not found.
class KeyError : public InternalError {
 public:
  /*! Create a key error.
   *
   * \param[in] key Key that was not found.
   * \param[in] file Source file of the instruction that threw the error.
   * \param[in] line Line of code in that file where the throw originates from.
   * \param[in] message Error message.
   */
  KeyError(const std::string& key, const std::string& file, unsigned line,
           const std::string& message)
      : InternalError(file, line,
                      std::string("Key \"") + key + "\" not found. " + message),
        key_(key) {}

  //! Empty destructor
  ~KeyError() throw() {}

  //! Key that was not found
  const std::string& key() const throw() { return key_; }

 private:
  //! Key that was not found
  std::string key_;
};

}  // namespace palimpsest
