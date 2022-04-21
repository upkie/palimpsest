# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "internal",
    hdrs = [
        "Allocator.h",
        "is_valid_hash.h",
        "type_name.h",
    ],
    include_prefix = "palimpsest/internal",
)

add_lint_tests(enable_clang_format_lint = True)
