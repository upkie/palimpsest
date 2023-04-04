# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "dictionary",
    srcs = [
        "Dictionary.cpp",
    ],
    deps = [
        "//include/palimpsest:dictionary",
        "//src/mpack",
    ],
)

add_lint_tests()
