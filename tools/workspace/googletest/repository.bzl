# -*- python -*-
#
# Copyright 2022 Stéphane Caron

load("//tools/workspace:github_archive.bzl", "github_archive")

def googletest_repository(
        commit = "release-1.10.0",
        sha256 = "94c634d499558a76fa649edb13721dce6e98fb1e7018dfaeba3cd7a083945e91"):
    """
    Download repository from GitHub as a ZIP archive, decompress it, and make
    its targets available for binding.

    Args:
        commit: commit of the guide to download.
        sha256: SHA-256 checksum of the downloaded archive.
    """
    github_archive(
        name = "googletest",
        repository = "google/googletest",
        commit = commit,
        sha256 = sha256,
        build_file = Label("//tools/workspace/googletest:package.BUILD"),
    )
