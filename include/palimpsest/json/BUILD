# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "json",
    hdrs = [
        "write.h",
    ],
    include_prefix = "palimpsest/json",
    deps = [
        "@eigen",
    ],
)

add_lint_tests()
