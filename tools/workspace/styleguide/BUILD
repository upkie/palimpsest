# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

py_test(
    name = "cpplint_unittest",
    size = "small",
    srcs = ["@styleguide//:cpplint_unittest"],
    tags = ["lint", "no_kcov"],
)

add_lint_tests()
