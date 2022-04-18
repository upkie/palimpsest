# -*- python -*-

load("//tools/workspace:github_archive.bzl", "github_archive")

def cppcodec_repository(
        version = "0.2",
        sha256 = "b9ae98161f7d361ad1dbda86460119d3210a49ae485e89339c8eb3d0df41283e"):
    """
    Download repository from GitHub as a ZIP archive, decompress it, and make
    its targets available for binding.

    Args:
        version: version of the library to get.
        sha256: SHA-256 checksum of the downloaded archive.
    """
    github_archive(
        name = "cppcodec",
        repository = "tplgy/cppcodec",
        commit = "v{}".format(version),
        sha256 = sha256,
        strip_prefix = "cppcodec-{}".format(version),
        build_file = "//tools/workspace/{repo}:package.BUILD".format(repo="cppcodec"),
    )
