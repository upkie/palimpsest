# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "mpack",
    srcs = [
        "Writer.cpp",
    ],
    deps = [
        "//include/palimpsest/mpack",
    ],
)

add_lint_tests()
