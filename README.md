# palimpsest — Fast serializable C++ dictionaries

[![Build](https://img.shields.io/github/workflow/status/stephane-caron/palimpsest/CI)](https://github.com/stephane-caron/palimpsest/actions)
![C++ version](https://img.shields.io/badge/C++-17/20-blue.svg?style=flat)

_palimpsest_ is a C++ header-only library that exposes a single ``Dictionary`` type meant for fast value updates, with an API similar to Python's ``dict``. It is called [palimpsest](https://en.wiktionary.org/wiki/palimpsest) because these dictionaries are optimized for frequent rewritings (values change all the time) on the same support (keys change once in a while).

## Features and non-features

All design decisions have their pros and cons. _palimpsest_ was designed for inter-process communication between real-time control programs, so it lies somewhere specific on the spectrum. Check the features and caveats below to see if it is a fit for _your_ use case.

### Features

<details>
<summary>Direct references to sub-dictionaries or values</summary>

```c++
Dictionary dict;
Dictionary& foo = dict("foo");
foo("bar") = 42;
const int& bar = dict("foo")("bar");
foo("bar") /= 7;
assert(bar == 6);
```
</details>

## Install

### Header-only version

TODO(scaron): Copy the [include folder](include/palimpsest) to your build tree and use a C++11 compiler.

### Static library with Bazel (faster compile times)

Create a git repository rule for palimpsest, for instance:

```python
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

def palimpsest_repository():
    git_repository(
        name = "palimpsest",
        remote = "git@github.com:stephane-caron/palimpsest.git",
        commit = "...",
        shallow_since = "..."
    )
```

Then call this rule from the ``WORKSPACE`` file at the root of your Bazel repository.

## Performance

...
