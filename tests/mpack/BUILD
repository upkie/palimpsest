# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_test(
    name = "read_test",
    srcs = ["read_test.cpp"],
    deps = [
        "//:palimpsest",
        "@eigen",
        "@googletest//:main",
    ],
)

cc_test(
    name = "writer_test",
    srcs = ["WriterTest.cpp"],
    deps = [
        "//:palimpsest",
        "@eigen",
        "@googletest//:main",
    ],
)

add_lint_tests()
