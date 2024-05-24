// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 Stéphane Caron

#pragma once

#include <string>

#include "palimpsest/exceptions/PalimpsestError.h"

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
