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

/*! Allocator<T> is std::allocator<T> for usual types */
template <typename T, typename = void>
struct Allocator : public std::allocator<T> {};

/*! Allocator<T> is Eigen::aligned_allocator for EIGEN_MAKE_ALIGNED_OPERATOR_NEW
 * types */
template <typename T>
struct Allocator<T, typename T::eigen_aligned_operator_new_marker_type>
    : public Eigen::aligned_allocator<T> {};

}  // namespace palimpsest::internal
