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
    name = "dictionary",
    deps = [
        "//include/palimpsest:dictionary",
        "//src:dictionary",
    ],
)

cc_library(
    name = "message_pack_writer",
    deps = [
        "//include/palimpsest:message_pack_writer",
        "//src:message_pack_writer",
    ],
)

cc_library(
    name = "palimpsest",
    deps = [
        ":dictionary",
        ":message_pack_writer",
    ],
)

add_lint_tests()
