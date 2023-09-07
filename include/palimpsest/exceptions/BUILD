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
    include_prefix = "palimpsest/exceptions",
)

add_lint_tests()
