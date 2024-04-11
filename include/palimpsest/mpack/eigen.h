// Copyright 2022 Stéphane Caron
// SPDX-License-Identifier: Apache-2.0
/*
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 *     MessagePackBuilder from https://github.com/jrl-umi3218/mc_rtc/
 *     Copyright 2015-2019 CNRS-UM LIRMM, CNRS-AIST JRL
 *     SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <mpack.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace palimpsest::mpack {

/*! Deserialize an Eigen matrix.
 *
 * @param[in] node Node to deserialize matrix values from.
 */
inline Eigen::Matrix3d mpack_node_matrix3d(mpack_node_t node) {
  assert(mpack_node_array_length(node) == 9);
  Eigen::Matrix3d matrix;
  for (Eigen::Index i = 0; i < 3; ++i) {
    for (Eigen::Index j = 0; j < 3; ++j) {
      matrix(i, j) = mpack_node_double(mpack_node_array_at(node, 3 * i + j));
    }
  }
  return matrix;
}

/*! Deserialize an Eigen quaternion.
 *
 * @param[in] node Node to deserialize quaternion values from.
 *
 * @note Quaternion coordinates are orderded as `[w x y z]`.
 */
inline Eigen::Quaterniond mpack_node_quaterniond(mpack_node_t node) {
  assert(mpack_node_array_length(node) == 4);
  Eigen::Quaterniond quaternion;
  quaternion.w() = mpack_node_double(mpack_node_array_at(node, 0));
  quaternion.x() = mpack_node_double(mpack_node_array_at(node, 1));
  quaternion.y() = mpack_node_double(mpack_node_array_at(node, 2));
  quaternion.z() = mpack_node_double(mpack_node_array_at(node, 3));
  return quaternion;
}

/*! Deserialize an Eigen 2D vector.
 *
 * @param[in] node Node to deserialize the vector from.
 */
inline Eigen::Vector2d mpack_node_vector2d(mpack_node_t node) {
  assert(mpack_node_array_length(node) == 2);
  Eigen::Vector2d vector;
  vector(0) = mpack_node_double(mpack_node_array_at(node, 0));
  vector(1) = mpack_node_double(mpack_node_array_at(node, 1));
  return vector;
}

/*! Deserialize an Eigen 3D vector.
 *
 * @param[in] node Node to deserialize the vector from.
 */
inline Eigen::Vector3d mpack_node_vector3d(mpack_node_t node) {
  assert(mpack_node_array_length(node) == 3);
  Eigen::Vector3d vector;
  vector(0) = mpack_node_double(mpack_node_array_at(node, 0));
  vector(1) = mpack_node_double(mpack_node_array_at(node, 1));
  vector(2) = mpack_node_double(mpack_node_array_at(node, 2));
  return vector;
}

/*! Deserialize an Eigen vector.
 *
 * @param[in] node Node to deserialize the vector from.
 */
inline Eigen::VectorXd mpack_node_vectorXd(mpack_node_t node) {
  const unsigned length = mpack_node_array_length(node);
  Eigen::VectorXd vector(length);
  for (Eigen::Index i = 0; i < length; ++i) {
    vector(i) = mpack_node_double(mpack_node_array_at(node, i));
  }
  return vector;
}

}  // namespace palimpsest::mpack
