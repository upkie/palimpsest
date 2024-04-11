// Copyright 2022 Stéphane Caron
// SPDX-License-Identifier: Apache-2.0
/*
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 *     Configuration and DataStore classes of mc_rtc
 *     Copyright 2015-2020 CNRS-UM LIRMM, CNRS-AIST JRL
 *     SPDX-License-Identifier: BSD-2-Clause
 */

#include "palimpsest/json/write.h"

#include <gtest/gtest.h>

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <fstream>
#include <string>

namespace palimpsest::json {

TEST(JsonTest, WriteBasicTypes) {
  std::ofstream out;
  out.open("/dev/null", std::ofstream::out | std::ofstream::app);
  ASSERT_NO_THROW(write(out, true));
  ASSERT_NO_THROW(write(out, int8_t(-1)));
  ASSERT_NO_THROW(write(out, int16_t(-2)));
  ASSERT_NO_THROW(write(out, int32_t(-3)));
  ASSERT_NO_THROW(write(out, int64_t(-4)));
  ASSERT_NO_THROW(write(out, uint8_t(1)));
  ASSERT_NO_THROW(write(out, uint16_t(2)));
  ASSERT_NO_THROW(write(out, uint32_t(3)));
  ASSERT_NO_THROW(write(out, uint64_t(4)));
  ASSERT_NO_THROW(write(out, 12.0f));
  ASSERT_NO_THROW(write(out, 42.0));
  ASSERT_NO_THROW(write(out, "c_str"));
  ASSERT_NO_THROW(write(out, std::string("cpp_str")));
  out.close();
}

TEST(JsonTest, WriteEigenTypes) {
  Eigen::Matrix3d morpheus;
  morpheus << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;

  Eigen::VectorXd cypher(4);
  cypher(0) = 4.0;
  cypher(1) = 3.0;
  cypher(2) = 2.0;
  cypher(3) = 1.0;

  std::ofstream out;
  out.open("/dev/null", std::ofstream::out | std::ofstream::app);
  ASSERT_NO_THROW(write(out, Eigen::Vector2d{1.0, 2.0}));
  ASSERT_NO_THROW(write(out, Eigen::Vector3d{1.0, 2.0, 3.0}));
  ASSERT_NO_THROW(write(out, Eigen::Quaterniond{1.0, 2.0, 3.0, 4.0}));
  ASSERT_NO_THROW(write(out, morpheus));
  ASSERT_NO_THROW(write(out, cypher));
  out.close();
}
}  // namespace palimpsest::json
