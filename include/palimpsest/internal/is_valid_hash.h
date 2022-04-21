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
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 *     Configuration and DataStore classes of mc_rtc
 *     Copyright 2015-2020 CNRS-UM LIRMM, CNRS-AIST JRL
 *     License: BSD-2-Clause
 */

#pragma once

#include <memory>

namespace palimpsest::internal {

/*! Check if hash code matches that of the template type parameter.
 *
 * \param hash Hash code to check.
 */
template <typename T>
bool is_valid_hash(std::size_t hash) {
  return (hash == typeid(T).hash_code());
}

/*! Check if hash code matches that of the template type parameter.
 *
 * \param hash Hash code to check.
 */
template <typename T, typename U, typename... Args>
bool is_valid_hash(std::size_t hash) {
  return is_valid_hash<T>(hash) || is_valid_hash<U, Args...>(hash);
}

}  // namespace palimpsest::internal
