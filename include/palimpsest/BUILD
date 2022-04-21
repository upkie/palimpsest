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
    name = "message_pack_writer",
    hdrs = [
        "MessagePackWriter.h",
    ],
    include_prefix = "palimpsest",
    deps = [
        ":mpack",
    ],
)

cc_library(
    name = "dictionary",
    hdrs = [
        "Dictionary.h",
    ],
    include_prefix = "palimpsest",
    deps = [
        "//include/palimpsest/internal",
        ":exceptions",
        ":json",
        ":message_pack_writer",
        ":mpack",
        "@fmt",
        "@spdlog",
    ],
)

add_lint_tests(enable_clang_format_lint = True)
