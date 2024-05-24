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

/*! Allocator<T> is std::allocator<T> for usual types */
template <typename T, typename = void>
struct Allocator : public std::allocator<T> {};

/*! Allocator<T> is Eigen::aligned_allocator for EIGEN_MAKE_ALIGNED_OPERATOR_NEW
 * types */
template <typename T>
struct Allocator<T, typename T::eigen_aligned_operator_new_marker_type>
    : public Eigen::aligned_allocator<T> {};

}  // namespace palimpsest::internal
