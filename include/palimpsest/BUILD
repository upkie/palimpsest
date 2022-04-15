# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "exceptions",
    hdrs = [
        "exceptions.h",
    ],
)

cc_library(
    name = "mpack",
    hdrs = [
        "mpack_eigen.h",
        "mpack_read.h",
        "mpack_write.h",
    ],
    include_prefix = "palimpsest",
    deps = [
        ":exceptions",
        "@eigen",
        "@mpack",
    ],
)

cc_library(
    name = "palimpsest",
    deps = [
        ":exceptions",
        ":mpack",
    ],
)

add_lint_tests(enable_clang_format_lint = True)
