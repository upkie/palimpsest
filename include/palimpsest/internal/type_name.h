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

/*! Return a human-readable type name
 *
 * Only use for displaying messages as the name is not guaranteed to be the
 * same across compilers and invokation
 */
template <typename T>
const char *type_name() {
  return typeid(T).name();
}

}  // namespace palimpsest::internal
