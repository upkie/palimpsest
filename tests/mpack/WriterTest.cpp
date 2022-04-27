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

#include <gtest/gtest.h>

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <memory>
#include <vector>

#include "palimpsest/mpack/Writer.h"

namespace palimpsest::mpack {

class WriterTest : public ::testing::Test {
 protected:
  void SetUp() override { writer_ = std::make_unique<mpack::Writer>(buffer_); }

 protected:
  //! Internal byte buffer
  std::vector<char> buffer_;

  //! Writer
  std::unique_ptr<mpack::Writer> writer_;
};

TEST_F(WriterTest, MessagePackExample) {
  writer_->start_map(2);
  writer_->write("compact");
  writer_->write(true);
  writer_->write("schema");
  writer_->write(0u);
  writer_->finish_map();
  size_t size = writer_->finish();
  ASSERT_GT(buffer_.size(), size);
}

TEST_F(WriterTest, EigenTypes) {
  Eigen::Matrix3d morpheus;
  morpheus << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;

  Eigen::VectorXd cypher(4);
  cypher(0) = 4.0;
  cypher(1) = 3.0;
  cypher(2) = 2.0;
  cypher(3) = 1.0;

  writer_->start_map(2);
  writer_->write("Vector2d");
  writer_->write(Eigen::Vector2d{1.0, 2.0});
  writer_->write("Vector3d");
  writer_->write(Eigen::Vector3d{1.0, 2.0, 3.0});
  writer_->write("Matrix3d");
  writer_->write(morpheus);
  writer_->write("VectorXd");
  writer_->write(cypher);
  writer_->write("Quaterniond");
  writer_->write(Eigen::Quaterniond::Identity());
  writer_->finish_map();
  size_t size = writer_->finish();
  ASSERT_GT(buffer_.size(), size);
}

}  // namespace palimpsest::mpack
