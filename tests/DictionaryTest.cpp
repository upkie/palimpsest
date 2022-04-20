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
#include <string>
#include <vector>

#include "cppcodec/base64_rfc4648.hpp"
#include "palimpsest/Dictionary.h"
#include "palimpsest/MessagePackWriter.h"

using base64 = cppcodec::base64_rfc4648;
using palimpsest::MessagePackWriter;

// This is only used in EigenOverloadOperatorNew but we need to overload the
// Eigen::aligned_allocator for this type.
struct Overloaded {
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

// We cheat here since we know our code is going to use
// Eigen::aligned_allocator in such cases.
namespace Eigen {

template <>
struct aligned_allocator<Overloaded> : public std::allocator<Overloaded> {
  static bool used;
  Overloaded *allocate(size_t n, const void *hint = nullptr) {
    used = true;
    return std::allocator<Overloaded>::allocate(n, hint);
  }

  void deallocate(Overloaded *p, std::size_t n) {
    used = false;
    return std::allocator<Overloaded>::deallocate(p, n);
  }
};

bool aligned_allocator<Overloaded>::used = false;

}  // namespace Eigen

/*! Custom serializable type.
 *
 * A serializable type can be any type T for which a json::write<T>()
 * specialization is implemented.
 */
struct Serializable {
  int a;
  std::string b;
};

namespace palimpsest::json {

/*! Write custom serializable type as JSON.
 *
 * \param stream Output stream.
 * \param s Instance of the custom Serializable type defined above.
 */
template <>
void write(std::ostream &stream, const Serializable &s) {
  stream << "{\"a\": " << s.a << ", \"b\": \"" << s.b << "\"}";
}

}  // namespace palimpsest::json

namespace palimpsest {

class DictionaryTest : public ::testing::Test {
 protected:
  void SetUp() override {
    Eigen::VectorXd longer_vector(42);
    longer_vector.setOnes();

    // Insert one value for each type
    dict_.insert<bool>("sure", true);
    dict_.insert<int>("foo", 12);
    dict_.insert<int8_t>("int8_t", -8);
    dict_.insert<int16_t>("int16_t", -16);
    dict_.insert<int32_t>("int32_t", -32);
    dict_.insert<int64_t>("int64_t", -64);
    dict_.insert<uint8_t>("uint8_t", 8u);
    dict_.insert<uint16_t>("uint16_t", 16u);
    dict_.insert<uint32_t>("uint32_t", 32u);
    dict_.insert<uint64_t>("uint64_t", 64u);
    dict_.insert<float>("huns", 1.f / 9.f);
    dict_.insert<double>("blah", 12.12);
    dict_.insert<std::string>("bar", "de ligne");
    dict_.insert<Eigen::Vector2d>("tiny", 6., 4.);
    dict_.insert<Eigen::Vector3d>("position", 1., 2., 3.);
    dict_.insert<Eigen::Quaterniond>("orientation", 0., 1., 0., 0.);
    dict_.insert<Eigen::Matrix3d>("inertia", 12. * Eigen::Matrix3d::Identity());
    dict_.insert<Eigen::VectorXd>("longer_vector", longer_vector);
  }

  Dictionary dict_;
};

TEST(Dictionary, TestDictionary) {
  Dictionary dict;
  dict.insert<std::vector<double>>("data", 4, 42.0);
  auto &data = dict.get<std::vector<double>>("data");
  ASSERT_EQ(data.size(), 4);
  EXPECT_NEAR(data[0], 42, 1e-10);
  EXPECT_NEAR(data[1], 42, 1e-10);
  EXPECT_NEAR(data[2], 42, 1e-10);
  EXPECT_NEAR(data[3], 42, 1e-10);
  EXPECT_THROW(dict.get<double>("data"), TypeError);
  EXPECT_THROW(dict.get<std::vector<int>>("data"), TypeError);
  EXPECT_THROW(dict.get<std::vector<double>>("inexistent"), KeyError);

  data.resize(100);
  auto &data2 = dict.get<std::vector<double>>("data");
  ASSERT_TRUE(data2.size() == data.size());
  const auto &constData = dict.get<std::vector<double>>("data");
  ASSERT_TRUE(data2.size() == constData.size());

  struct CustomType {
    int answer;
    std::string name;
  };

  // Test insert
  dict.insert<CustomType>("key", CustomType{42, "Test"});
  ASSERT_EQ(dict.get<CustomType>("key").answer, 42);
  ASSERT_EQ(dict.get<CustomType>("key").name, "Test");

  // Remove object
  dict.remove("key");
  EXPECT_FALSE(dict.has("key"));
  EXPECT_TRUE(dict.has("data"));

  // Try to remove when it's not there
  dict.remove("key");
  EXPECT_FALSE(dict.has("key"));
  EXPECT_TRUE(dict.has("data"));

  // Test insertion with an inline initializer list
  dict.insert_initializer<CustomType>("key", 42, "Test");
  ASSERT_EQ(dict.get<CustomType>("key").answer, 42);
  ASSERT_EQ(dict.get<CustomType>("key").name, "Test");

  // Trying to re-create the object returns the existing one
  auto &previous_object =
      dict.insert_initializer<CustomType>("key", 51, "Test");
  ASSERT_EQ(previous_object.answer, 42);
  ASSERT_EQ(previous_object.name, "Test");
  ASSERT_EQ(dict.get<CustomType>("key").answer, 42);
  ASSERT_EQ(dict.get<CustomType>("key").name, "Test");

  // Recreate it with the same name and directly assign some value to it
  dict.remove("key");
  dict.insert_initializer<CustomType>("key", 42, "Test").name = "Test2";
  ASSERT_TRUE(dict.get<CustomType>("key").name == "Test2");

  // Check creating object of a different type with same name
  dict.remove("key");
  dict.insert_initializer<std::vector<double>>("key", 1., 2.);
  auto &v = dict.get<std::vector<double>>("key");
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);

  // Test getters
  dict.insert<double>("assign", 42);
  double value = 0;
  dict.get("assign", /* default_value = */ value);  // no effect
  ASSERT_DOUBLE_EQ(value, 0);
  ASSERT_EQ(dict.get("assign_inexistent", 12), 12);
  ASSERT_FALSE(dict.get("has_feature", false));
}

TEST(Dictionary, TestDictionaryInheritance) {
  Dictionary dict;

  struct A {
    explicit A(const std::string &name) : name_(name) {}
    virtual std::string hello() const { return "A::Hello " + name_; }
    void printHello() const { std::cout << hello() << std::endl; }
    std::string type() const { return "A"; }
    std::string name_;
  };

  struct B : public A {
    explicit B(const std::string &name) : A(name) {}
    std::string hello() const override { return "B::Hello " + name_; }
    std::string type() const { return "B"; }
  };

  // Creating an inherited object and checking virtual inheritance
  dict.insert<B, A>("b", "World");
  auto &a = dict.get<A>("b");
  // Checking member function
  ASSERT_EQ(a.type(), "A");
  // Checking virtual function
  ASSERT_EQ(a.hello(), "B::Hello World");
  auto &b = dict.get<B>("b");
  ASSERT_EQ(b.type(), "B");
  ASSERT_EQ(b.hello(), "B::Hello World");

  // Extra check on A alone
  dict.insert<A>("a", "Parent");
  auto &a_of_a = dict.get<A>("a");
  ASSERT_EQ(a_of_a.hello(), "A::Hello Parent");
}

TEST(Dictionary, TestRemove) {
  struct ToLiveAndDieInLA {
    explicit ToLiveAndDieInLA(const std::string &name) : name_(name) {
      spdlog::info("Object {} constructed", name_);
    }
    ~ToLiveAndDieInLA() { spdlog::info("Object {} destructed", name_); }
    std::string name_;
  };

  Dictionary dict;
  dict.insert<ToLiveAndDieInLA>("2Pac", "2Pac");
  {
    auto &r = dict.get<ToLiveAndDieInLA>("2Pac");
    ASSERT_EQ(r.name_, "2Pac");
    EXPECT_TRUE(dict.has("2Pac"));
    dict.remove("2Pac");
    EXPECT_TRUE(!dict.has("2Pac"));
  }
}

TEST(Dictionary, EigenOverloadOperatorNew) {
  Dictionary dict;
  EXPECT_FALSE(Eigen::aligned_allocator<Overloaded>::used);
  dict.insert<Overloaded>("overloaded");
  EXPECT_TRUE(Eigen::aligned_allocator<Overloaded>::used);
  dict.remove("overloaded");
  EXPECT_FALSE(Eigen::aligned_allocator<Overloaded>::used);
}

TEST(Dictionary, WriteEmptyJSON) {
  Dictionary dict;
  std::ostringstream oss;
  oss << dict;
  ASSERT_EQ(oss.str(), "{}");
}

TEST(Dictionary, WriteJSON) {
  Dictionary dict;
  dict.insert<int>("test", 1);
  std::ostringstream oss;
  oss << dict;
  ASSERT_EQ(oss.str(), "{\"test\": 1}");
}

TEST(Dictionary, WriteMoreJSON) {
  Dictionary dict;
  dict.insert<int>("test", 1);
  dict.insert<int>("nice", 2);
  std::ostringstream oss;
  oss << dict;
  std::string case_1 = "{\"test\": 1, \"nice\": 2}";
  std::string case_2 = "{\"nice\": 2, \"test\": 1}";
  ASSERT_TRUE(oss.str() == case_1 || oss.str() == case_2);
}

TEST(Dictionary, WriteCustomTypeJSON) {
  Dictionary dict;
  dict.insert_initializer<Serializable>("foo", 1, "bar");
  std::ostringstream oss;
  oss << dict;
  ASSERT_EQ(oss.str(), "{\"foo\": {\"a\": 1, \"b\": \"bar\"}}");
}

TEST(Dictionary, WriteUnknownTypeJSON) {
  struct UnknownType {
    std::string mystery;
  };
  Dictionary dict;
  dict.insert_initializer<UnknownType>("unknown", "???");
  std::ostringstream oss;
  oss << dict;
  ASSERT_TRUE(oss.str().find("<typeid:") != std::string::npos);
}

}  // namespace palimpsest
