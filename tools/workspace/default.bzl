# -*- python -*-
#
# Copyright 2022 Stéphane Caron

load("//tools/workspace/cppcodec:repository.bzl", "cppcodec_repository")
load("//tools/workspace/eigen:repository.bzl", "eigen_repository")
load("//tools/workspace/fmt:repository.bzl", "fmt_repository")
load("//tools/workspace/googletest:repository.bzl", "googletest_repository")
load("//tools/workspace/mpack:repository.bzl", "mpack_repository")
load("//tools/workspace/rules_foreign_cc:repository.bzl", "rules_foreign_cc_repository")
load("//tools/workspace/rules_python:repository.bzl", "rules_python_repository")
load("//tools/workspace/spdlog:repository.bzl", "spdlog_repository")
load("//tools/workspace/styleguide:repository.bzl", "styleguide_repository")

def add_default_repositories():
    """
    Declare workspace repositories for all dependencies. This function should
    be loaded and called from a WORKSPACE file.
    """
    cppcodec_repository()
    eigen_repository()
    fmt_repository()
    googletest_repository()
    mpack_repository()
    rules_foreign_cc_repository()
    rules_python_repository()
    spdlog_repository()
    styleguide_repository()
