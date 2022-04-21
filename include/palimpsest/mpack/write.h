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
 *     MessagePackBuilder from https://github.com/jrl-umi3218/mc_rtc/
 *     Copyright 2015-2019 CNRS-UM LIRMM, CNRS-AIST JRL
 *     License: BSD-2-Clause
 */

#pragma once

#include <mpack.h>

#include <string>

namespace palimpsest::mpack {

/*
 * Templated functions to serialize values to an mpack_writer_t. This allows
 * the compiler to select the appropriate function in mpack::write<T>(value).
 */

/*! Write a value to MPack.
 *
 * \param writer MPack writer.
 * \param value Value to write.
 *
 * This is the non-specialized version of this function. It reports a
 * non-serializable value to MPack as a type hash string.
 */
template <typename T>
void write(mpack_writer_t* writer, const T& value) {
  auto type_name = std::string("<typeid:") + typeid(T).name() + ">";
  return write<std::string>(writer, type_name);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const bool& value) {
  mpack_write_bool(writer, value);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const int8_t& value) {
  mpack_write_i8(writer, value);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const int16_t& value) {
  mpack_write_i16(writer, value);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const int32_t& value) {
  mpack_write_i32(writer, value);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const int64_t& value) {
  mpack_write_i64(writer, value);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const uint8_t& value) {
  mpack_write_u8(writer, value);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const uint16_t& value) {
  mpack_write_u16(writer, value);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const uint32_t& value) {
  mpack_write_u32(writer, value);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const uint64_t& value) {
  mpack_write_u64(writer, value);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const float& value) {
  mpack_write_float(writer, value);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const double& value) {
  mpack_write_double(writer, value);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const std::string& value) {
  mpack_write_str(writer, value.c_str(), static_cast<uint32_t>(value.size()));
}

/*! Write a matrix to MPack.
 *
 * \param writer MPack writer.
 * \param matrix Matrix to write.
 */
template <typename T>
inline void write_matrix(mpack_writer_t* writer, const T& matrix) {
  for (Eigen::Index i = 0; i < matrix.rows(); ++i) {
    for (Eigen::Index j = 0; j < matrix.cols(); ++j) {
      write<double>(writer, matrix(i, j));
    }
  }
}

/*! Write a vector to MPack.
 *
 * \param writer MPack writer.
 * \param vector Vector to write.
 */
template <typename T>
inline void write_vector(mpack_writer_t* writer, const T& vector) {
  for (Eigen::Index i = 0; i < vector.size(); ++i) {
    write<double>(writer, vector(i));
  }
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const Eigen::Vector2d& value) {
  mpack_start_array(writer, 2);
  write_vector(writer, value);
  mpack_finish_array(writer);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const Eigen::Vector3d& value) {
  mpack_start_array(writer, 3);
  write_vector(writer, value);
  mpack_finish_array(writer);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const Eigen::VectorXd& value) {
  mpack_start_array(writer, static_cast<size_t>(value.size()));
  write_vector(writer, value);
  mpack_finish_array(writer);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const Eigen::Quaterniond& value) {
  mpack_start_array(writer, 4);
  write<double>(writer, value.w());
  write<double>(writer, value.x());
  write<double>(writer, value.y());
  write<double>(writer, value.z());
  mpack_finish_array(writer);
}

//! Specialization of \ref mpack_write<T>(writer, value)
template <>
inline void write(mpack_writer_t* writer, const Eigen::Matrix3d& value) {
  mpack_start_array(writer, 9);
  write_matrix(writer, value);
  mpack_finish_array(writer);
}

}  // namespace palimpsest::mpack
