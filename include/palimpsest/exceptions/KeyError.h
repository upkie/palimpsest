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

#include "palimpsest/exceptions/PalimpsestError.h"

namespace palimpsest::exceptions {

//! Requested dictionary key is not found.
class KeyError : public PalimpsestError {
 public:
  /*! Create a key error.
   *
   * @param[in] key Key that was not found.
   * @param[in] file Source file of the instruction that threw the error.
   * @param[in] line Line of code in that file where the throw originates from.
   * @param[in] message Error message.
   */
  KeyError(const std::string& key, const std::string& file, unsigned line,
           const std::string& message)
      : PalimpsestError(
            file, line,
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

}  // namespace palimpsest::exceptions
