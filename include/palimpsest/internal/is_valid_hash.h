// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 Stéphane Caron
/*
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 *     Configuration and DataStore classes of mc_rtc
 *     Copyright 2015-2020 CNRS-UM LIRMM, CNRS-AIST JRL
 *     SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <memory>

namespace palimpsest::internal {

/*! Check if hash code matches that of the template type parameter.
 *
 * @param hash Hash code to check.
 */
template <typename T>
bool is_valid_hash(std::size_t hash) {
  return (hash == typeid(T).hash_code());
}

/*! Check if hash code matches that of the template type parameter.
 *
 * @param hash Hash code to check.
 */
template <typename T, typename U, typename... Args>
bool is_valid_hash(std::size_t hash) {
  return is_valid_hash<T>(hash) || is_valid_hash<U, Args...>(hash);
}

}  // namespace palimpsest::internal
