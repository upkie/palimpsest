#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright 2022 Stéphane Caron
# Copyright 2023 Inria
#
# This file incorporates work covered by the following copyright and permission
# notice:
#
#     Copyright 2012-2016 Robot Locomotion Group @ CSAIL
#     License: BSD-3-Clause

import os
import shutil
import subprocess
import sys


def _is_cxx(filename):
    """Returns True only if filename is reasonable to clang-format."""
    root, ext = os.path.splitext(filename)
    _, penultimate_ext = os.path.splitext(root)

    # Don't clang-format CUDA files.
    if penultimate_ext == "cu":
        return False

    # Per https://bazel.build/versions/master/docs/be/c-cpp.html#cc_library
    return ext in [
        ".c",
        ".cc",
        ".cpp",
        ".cxx",
        ".c++",
        ".C",
        ".h",
        ".hh",
        ".hpp",
        ".hxx",
        ".inc",
    ]


def _check_clang_format_idempotence(filename):
    clang_format = shutil.which("clang-format")
    formatter = subprocess.Popen(
        [clang_format, "-style=file", filename], stdout=subprocess.PIPE
    )
    differ = subprocess.Popen(
        ["/usr/bin/diff", "-u", "-", filename],
        stdin=formatter.stdout,
        stdout=subprocess.PIPE,
    )
    changes = differ.communicate()[0]
    if not changes:
        return 0
    print("ERROR: {} needs clang-format".format(filename))
    print(f"You can fix it by `{clang_format} -style=file -i {filename}`")
    print(f"Full diff: {changes}")
    return 1


def main():
    """Checks that clang-format is idempotent on each path specified as a
    command-line argument.  Exit 1 if any of the paths are invalid or
    clang-format suggests any edits.  Otherwise exit 0.
    """
    total_errors = 0
    for filename in sys.argv[1:]:
        if not _is_cxx(filename):
            print("clang_format_lint.py: Skipping " + filename)
            continue
        print("clang_format_lint.py: Linting " + filename)
        total_errors += _check_clang_format_idempotence(filename)
    if total_errors == 0:
        sys.exit(0)
    else:
        sys.exit(1)


if __name__ == "__main__":
    main()
