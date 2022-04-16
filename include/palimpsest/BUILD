# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "exceptions",
    hdrs = [
        "exceptions.h",
    ],
    include_prefix = "palimpsest",
)

cc_library(
    name = "json",
    hdrs = [
        "json_write.h",
    ],
    include_prefix = "palimpsest",
    deps = [
        "@eigen",
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
