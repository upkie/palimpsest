# -*- python -*-
#
# Copyright 2022 Stéphane Caron
#
# This file incorporates work covered by the following copyright and permission
# notice:
#
#     Copyright 2012-2016 Robot Locomotion Group @ CSAIL
#     License: BSD-3-Clause
#
# Custom build file to use the package with Bazel.

package(default_visibility = ["//visibility:public"])

# Export doc files for website publication.
exports_files(glob([
    "*",
    "include/*",
]))

# We can't set name="cpplint" here because that's the directory name so the
# sandbox gets confused.  We'll give it a private name with a public alias.
py_binary(
    name = "cpplint_binary",
    srcs = ["cpplint/cpplint.py"],
    imports = ["cpplint"],
    main = "cpplint/cpplint.py",
    visibility = [],
)

alias(
    name = "cpplint",
    actual = ":cpplint_binary",
)

# We use py_binary here because externals' tests are not run by
# default during `bazel test //...`, so `py_test` here would be
# misleading.  We can't even `alias()` the test into Drake due to
# https://github.com/bazelbuild/bazel/issues/10893
py_binary(
    name = "cpplint_unittest",
    srcs = ["cpplint/cpplint_unittest.py"],
    data = [
        "cpplint/cpplint_test_header.h",
    ],
    deps = ["cpplint_binary"],
    testonly = 1,
)
