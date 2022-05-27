# -*- python -*-

load("//tools/workspace:github_archive.bzl", "github_archive")

def styleguide_repository(
        commit = "748ed4dd4e543001421c6618646a60e2a2dca8ea",
        sha256 = "b5981b4a03bb9b1c354b072c2d6b36b88232cc7cbbd2cb49d5b30fb32be9694f"):
    """
    Download repository from GitHub as a ZIP archive, decompress it, and make
    its targets available for binding.

    Args:
        version: commit of the guide to download.
        sha256: SHA-256 checksum of the downloaded archive.
    """
    github_archive(
        name = "styleguide",
        repository = "google/styleguide",
        commit = commit,
        sha256 = sha256,
        build_file = Label("//tools/workspace/styleguide:package.BUILD"),
    )
