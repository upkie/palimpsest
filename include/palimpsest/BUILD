# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "exceptions",
    hdrs = [
        "PalimpsestError.h",
        "KeyError.h",
        "TypeError.h",
    ],
    include_prefix = "palimpsest",
)

cc_library(
    name = "dictionary",
    hdrs = [
        "Dictionary.h",
    ],
    include_prefix = "palimpsest",
    deps = [
        "//include/palimpsest/internal",
        "//include/palimpsest/json",
        "//include/palimpsest/mpack",
        ":exceptions",
        "@fmt",
        "@spdlog",
    ],
)

add_lint_tests()
