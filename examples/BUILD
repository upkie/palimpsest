# -*- python -*-
#
# Copyright 2022 Stéphane Caron

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

py_binary(
    name = "load_dictionary",
    srcs = ["load_dictionary.py"],
)

cc_binary(
    name = "save_dictionary",
    srcs = ["save_dictionary.cpp"],
    deps = ["@palimpsest"],
)

cc_binary(
    name = "save_load_dictionary",
    srcs = ["save_load_dictionary.cpp"],
    deps = ["@palimpsest"],
)

cc_binary(
    name = "simple_dictionary",
    srcs = ["simple_dictionary.cpp"],
    deps = ["@palimpsest"],
)

cc_binary(
    name = "simple_logger",
    srcs = ["simple_logger.cpp"],
    deps = ["@palimpsest"],
)

add_lint_tests()
