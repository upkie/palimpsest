// Copyright 2022 Stéphane Caron
// SPDX-License-Identifier: Apache-2.0

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
