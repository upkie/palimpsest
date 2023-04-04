# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_test(
    name = "tests",
    srcs = glob([
        "**/*.cpp",
        "**/*.h",
    ]),
    deps = [
        "//:palimpsest",
        "@eigen",
        "@googletest//:main",
    ],
)

add_lint_tests()
