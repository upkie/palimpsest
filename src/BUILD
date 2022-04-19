# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "message_pack_writer",
    srcs = [
        "MessagePackWriter.cpp",
    ],
    deps = [
        "//include/palimpsest:message_pack_writer",
    ],
)

cc_library(
    name = "dictionary",
    srcs = [
        "Dictionary.cpp",
    ],
    deps = [
        "//include/palimpsest:dictionary",
        ":message_pack_writer",
    ],
)

add_lint_tests(enable_clang_format_lint = True)
