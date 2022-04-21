# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "allocator",
    hdrs = ["Allocator.h"],
    include_prefix = "palimpsest/internal",
)

cc_library(
    name = "is_valid_hash",
    hdrs = ["is_valid_hash.h"],
    include_prefix = "palimpsest/internal",
)

cc_library(
    name = "message_pack_writer",
    hdrs = [
        "MessagePackWriter.h",
    ],
    include_prefix = "palimpsest/internal",
    deps = [
        "//include/palimpsest:mpack",
    ],
)

cc_library(
    name = "type_name",
    hdrs = ["type_name.h"],
    include_prefix = "palimpsest/internal",
)

add_lint_tests(enable_clang_format_lint = True)
