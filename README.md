# palimpsest — Fast serializable C++ dictionaries

[![Build](https://img.shields.io/github/workflow/status/stephane-caron/palimpsest/CI)](https://github.com/stephane-caron/palimpsest/actions)
![C++ version](https://img.shields.io/badge/C++-17/20-blue.svg?style=flat)

_palimpsest_ is a C++ header-only library that exposes a single ``Dictionary`` type meant for fast value updates, with an API similar to Python's ``dict``. It is called [palimpsest](https://en.wiktionary.org/wiki/palimpsest) because these dictionaries are optimized for frequent rewritings (values change all the time) on the same support (keys change once in a while).

## Features and non-features

All design decisions have their pros and cons. _palimpsest_ was designed for inter-process communication between real-time control programs, so it lies somewhere specific on the spectrum. Check the features and caveats below to see if it is a fit for _your_ use case.

### Features

* References to sub-dictionaries or values to avoid future key lookups
* Built-in support for [Eigen](https://eigen.tuxfamily.org/)
* Serialize to and deserialize from [MessagePack](https://msgpack.org/)
* Print dictionaries to standard output as JSON

```cpp
Dictionary dict;
Dictionary& foo = dict("foo");
foo("bar") = 42;
const int& bar = dict("foo")("bar");
foo("bar") /= 7;  // now dict("foo")("bar") == 6
```

### Non-features

* Array values are limited to matrices and vectors
* Copy constructors are disabled

## Install

### Bazel (faster compile times)

You can build _palimpsest_ straight from the repository by:

```console
./tools/bazelisk build //...
```

To use it in your project, create a git repository rule such as:

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

Then call this rule from your Bazel ``WORKSPACE``, and use the ``@palimpsest`` dependency in your C++ rules.

### CMake

...

## Performance

...

## Q and A

Why isn't _palimpsest_ also distributed as a header-only library?

> The main blocker so far is that we set a custom flush function
> ``mpack_std_vector_writer_flush`` to our internal MPack writers. The [MPack
> Write API](https://ludocode.github.io/mpack/group__writer.html) requires a
> function pointer for that, and we define that function in
> [`Writer.cpp`](src/mpack/Writer.cpp). Open a PR if you have ideas to go
> around that!

## Details

This means arrays of "things" are not allowed, only arrays of numbers. For instance,

```json
{"foo": [1.0, 2.0]}
```

can be handled and its value will be deserialized as an ``Eigen::Vector2d``. However,

```json
{"foo": ["string", {"bar": 42}]}  # not OK
```

cannot be handled, as the array cannot be deserialized to an Eigen type.

## 👷 Contribute

All contributions big and small are welcome! Make sure you read the [contribution guidelines](CONTRIBUTING.md).
