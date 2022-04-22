# palimpsest — Fast serializable C++ dictionaries

[![Build](https://img.shields.io/github/workflow/status/stephane-caron/palimpsest/CI)](https://github.com/stephane-caron/palimpsest/actions)
![C++ version](https://img.shields.io/badge/C++-17/20-blue.svg?style=flat)

_palimpsest_ is a small C++ library that provides a ``Dictionary`` type meant for fast value updates and serialization, with an API similar to Python's ``dict``. It is called [palimpsest](https://en.wiktionary.org/wiki/palimpsest) because these dictionaries are optimized for frequent rewritings (values change all the time) on the same support (keys change once in a while).

## Features and non-features

There are two main assumptions in _palimpsest_ dictionaries:

* **Keys** are strings.
* **Values** hold either a sub-dictionary or a type that can be unambiguously serialized/deserialized.

They allow us to write straightforwardly structures like:

```cpp
using palimpsest::Dictionary;

Dictionary world;
world("name") = "example";
world("temperature") = 28.0;

auto& bodies = world("bodies");
bodies("plane")("orientation") = Eigen::Quaterniond{0.9239, 0.3827, 0., 0.};
bodies("plane")("position") = Eigen::Vector3d{0.0, 0.0, 100.0};
bodies("truck")("orientation") = Eigen::Quaterniond::Identity();
bodies("truck")("position") = Eigen::Vector3d{42.0, 0.0, 0.0};

std::cout << world << std::endl;
```

This example outputs:

```json
{"bodies": {"truck": {"position": [42, 0, 0], "orientation": [1, 0, 0, 0]}, "plane": {"position": [0, 0, 100], "orientation": [0.9239, 0.3827, 0, 0]}}, "temperature": 28, "name": "example"}
```

_palimpsest_'s design decisions are rooted in the robotics applications that prompted its development. Since all design decisions have their pros and cons, check the detailed features and non-features below to decide if it is a fit for _your_ use case.

### Features

* References to sub-dictionaries or values to avoid future key lookups
* Built-in support for [Eigen](https://eigen.tuxfamily.org/)
* Serialize to and deserialize from [MessagePack](https://msgpack.org/)
* Print dictionaries to standard output as JSON
* Extensible to new types

### Non-features

* Array values are limited to Eigen tensors (matrix, quaternion, vector)
* Copy constructors are disabled

## Install

### Bazel (recommended)

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

Make sure Eigen is installed system-wise, for instance on Debian-based distributions:

```console
sudo apt install libeigen3-dev
```

Then follow the standard CMake procedure:

```console
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
make install
```

Note that by default MPack will be built and installed from the [``third_party``](third_party) folder. Set ``-DBUILD_MPACK=OFF`` if you already have MPack installed on your system.

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

### Adding custom types

...

## Alternatives

* [nlohmann::json](https://github.com/nlohmann/json) - ...
* [RapidJSON](https://github.com/Tencent/rapidjson/) - ...
* [std::map](https://www.cplusplus.com/reference/map/map/) - if your values all have the same type, you might as well use a standard map directly.
* [std::unordered\_map](https://www.cplusplus.com/reference/unordered_map/unordered_map/) - similar use case to ``std::map``, this variant can perform faster.

## Contribute 👷

All contributions big and small are welcome! Make sure you read the [contribution guidelines](CONTRIBUTING.md).
