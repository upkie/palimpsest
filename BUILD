# -*- python -*-
#
# Copyright 2022 Stéphane Caron

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

exports_files([
    "CPPLINT.cfg",
    ".clang-format",
])

cc_library(
    name = "palimpsest",
    deps = [
        "//include/palimpsest:dictionary",
        "//src:dictionary",
    ],
)

add_lint_tests()
