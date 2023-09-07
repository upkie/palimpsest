# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "mpack",
    hdrs = [
        "eigen.h",
        "read.h",
        "write.h",
        "Writer.h",
    ],
    include_prefix = "palimpsest/mpack",
    deps = [
        "//include/palimpsest/exceptions",
        "@eigen",
        "@mpack",
    ],
)

add_lint_tests()

