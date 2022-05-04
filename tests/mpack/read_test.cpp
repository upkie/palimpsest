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

#include "palimpsest/mpack/read.h"

#include <gtest/gtest.h>
#include <mpack.h>

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <fstream>
#include <string>

namespace palimpsest::mpack {

class ReadTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Example from https://msgpack.org/
    static const char msgpack_example[] =
        "\x82\xA7"
        "compact\xC3\xA6"
        "schema\x00\xC1";

    mpack_tree_init(&example_tree_, msgpack_example,
                    sizeof(msgpack_example) - 1);
    mpack_tree_parse(&example_tree_);
    auto error = mpack_tree_error(&example_tree_);
    if (error != mpack_ok) {
      FAIL() << "Tree is in error state " << static_cast<int>(error) << " ("
             << mpack_error_to_string(error) << ")";
    }
    ASSERT_EQ(mpack_tree_error(&example_tree_), mpack_ok);
    ASSERT_EQ(mpack_tree_size(&example_tree_), sizeof(msgpack_example) - 2);
  }

  void TearDown() override {
    mpack_error_t error = mpack_tree_destroy(&example_tree_);
    if (error != mpack_ok) {
      FAIL() << "Tree is in error state " << static_cast<int>(error) << " ("
             << mpack_error_to_string(error) << ")";
    }
    ASSERT_EQ(error, mpack_ok);
  }

 protected:
  mpack_tree_t example_tree_;
};

TEST_F(ReadTest, ExampleIntegrity) {
  mpack_node_t map = mpack_tree_root(&example_tree_);
  ASSERT_EQ(mpack_node_bool(mpack_node_map_cstr(map, "compact")), true);
  ASSERT_EQ(mpack_node_u8(mpack_node_map_cstr(map, "schema")), 0);
}

TEST_F(ReadTest, ReadBool) {
  mpack_node_t map = mpack_tree_root(&example_tree_);
  auto bool_node = mpack_node_map_cstr(map, "compact");
  ASSERT_EQ(mpack_node_bool(bool_node), true);

  bool output = false;
  mpack::read(bool_node, output);
  ASSERT_EQ(output, true);
}

}  // namespace palimpsest::mpack
