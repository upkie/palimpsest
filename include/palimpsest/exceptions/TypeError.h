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

#include "palimpsest/PalimpsestError.h"

namespace palimpsest::exceptions {

//! Requested type doesn't match the one already in the dictionary.
class TypeError : public PalimpsestError {
 public:
  /*! Create a type error.
   *
   * @param[in] file Source file of the instruction that threw the error.
   * @param[in] line Line of code in that file where the throw originates from.
   * @param[in] message Error message.
   */
  TypeError(const std::string& file, unsigned line, const std::string& message)
      : PalimpsestError(file, line, message) {}

  /*! Copy an existing error, adding to the error message.
   *
   * @param[in] other Existing error.
   * @param[in] extra_message Additional error message.
   */
  TypeError(const TypeError& other, const std::string& extra_message)
      : PalimpsestError(other, extra_message) {}

  //! Empty destructor
  ~TypeError() throw() {}
};

}  // namespace palimpsest::exceptions
