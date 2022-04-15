# -*- python -*-
#
# Copyright 2022 Stéphane Caron

load("//tools/workspace/eigen:repository.bzl", "eigen_repository")
load("//tools/workspace/googletest:repository.bzl", "googletest_repository")
load("//tools/workspace/mpack:repository.bzl", "mpack_repository")
load("//tools/workspace/mypy_integration:repository.bzl", "mypy_integration_repository")
load("//tools/workspace/rules_foreign_cc:repository.bzl", "rules_foreign_cc_repository")

def add_default_repositories():
    """
    Declare workspace repositories for all dependencies. This function should
    be loaded and called from a WORKSPACE file.
    """
    eigen_repository()
    googletest_repository()
    mpack_repository()
    mypy_integration_repository()
    rules_foreign_cc_repository()
