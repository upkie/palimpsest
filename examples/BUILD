# -*- python -*-
#
# Copyright 2022 Stéphane Caron

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "cpp_to_python",
    srcs = ["cpp_to_python.cpp"],
    deps = ["@palimpsest"],
)

cc_binary(
    name = "readme",
    srcs = ["readme.cpp"],
    deps = ["@palimpsest"],
)

cc_binary(
    name = "simple_logger",
    srcs = ["simple_logger.cpp"],
    deps = ["@palimpsest"],
)

add_lint_tests(enable_clang_format_lint = True)
