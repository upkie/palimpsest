# -*- python -*-

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")


def eigen_repository(
        version = "3.3.4",
        sha256 = "b4415a2e16bbaff7568e52853c9e131633248c9bc66d565086e095087e95877d"):
    """
    Download repository from GitLab as a ZIP archive, decompress it, and make
    its targets available for binding.

    Args:
        version: version of the library to get.
        sha256: SHA-256 checksum of the downloaded archive.
    """
    http_archive(
        name = "eigen",
        urls = [
            "https://gitlab.com/libeigen/eigen/-/archive/{}/eigen-{}.zip".format(version, version),
        ],
        sha256 = sha256,
        strip_prefix = "eigen-{}".format(version),
        build_file = Label("//tools/workspace/eigen:package.BUILD"),
    )
