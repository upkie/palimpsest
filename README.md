# palimpsest — Fast serializable C++ dictionaries

[![Build](https://img.shields.io/github/workflow/status/stephane-caron/palimpsest/CI)](https://github.com/stephane-caron/palimpsest/actions)
![C++ version](https://img.shields.io/badge/C++-17/20-blue.svg?style=flat)

_palimpsest_ is a small C++ library that provides a ``Dictionary`` type meant for fast value updates and serialization, with an API similar to Python's ``dict``. It is called [palimpsest](https://en.wiktionary.org/wiki/palimpsest) because these dictionaries are designed for frequent rewritings (values change fast) on the same support (keys change slow).

## Overview

The two main assumptions in _palimpsest_ dictionaries are that:

* **Keys** are strings.
* **Values** hold either a sub-dictionary or a type that can be unambiguously serialized.

Numbers, strings and tensors can be readily serialized, so we can straightforwardly write structures like:

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
{"bodies": {"truck": {"position": [42, 0.5, 0], "orientation": [1, 0, 0, 0]}, "plane": {"position": [0.1, 0, 100], "orientation": [0.9239, 0.3827, 0, 0]}}, "temperature": 28, "name": "example"}
```

We can serialize the dictionary to a file using the convenience [write](\ref palimpsest::Dictionary::write) function:

```cpp
world.write("world.mpack");
```

And deserialize it likewise:

```cpp
Dictionary world_bis;
world_bis.read("world.mpack");
std::cout << world_bis << std::endl;
```

While one-time writing to files can be useful, dictionaries can be more generally [serialized to bytes](#serialization-to-bytes) for transmission over your preferred medium, be it a TCP connection, shared memory mapping, transcontinental telegraph line, etc.

## Features and non-features

All design decisions have their pros and cons, and the ones in _palimpsest_ are rooted in the robotics applications that prompted its development. Take a look at the features and non-features below to decide if it is also a fit for _your_ use case.

### Features

* References to sub-dictionaries or values to avoid future key lookups
* Built-in support for [Eigen](https://eigen.tuxfamily.org/)
* Serialize to and deserialize from [MessagePack](https://msgpack.org/)
* Print dictionaries to standard output as [JSON](https://www.json.org/json-en.html)
* [Extensible](#adding-new-types) to new types (as long as they deserialize unambiguously)

### Non-features

* Array values are mostly limited to Eigen tensors (matrix, quaternion, vector)
* Copy constructors are disabled
* (Extensible to new types) as long as they deserialize unambiguously
* [WIP](#contribute): key collisions are pretty much left up to the user
* [WIP](#contribute): shallow and deep copies are not implemented yet

Check out the [alternatives](#alternatives) below if any of these is a no-go for you.

## Install

### Bazel (recommended)

You can build _palimpsest_ straight from the repository by running ``./tools/bazelisk build //...`` from the root folder. To use it in your project, create a git repository rule such as:

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

Call this rule from your Bazel ``WORKSPACE``, and use the ``@palimpsest`` dependency in your C++ rule ``deps``.

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

### Serialization to bytes

#### Serialization

Dictionaries can be serialized to vectors of bytes via the serialize function:

```cpp
Dictionary world;
std::vector<char> buffer;
size_t size = world.serialize(buffer);
```

The function call will resize the buffer automatically if needed.

#### Deserialization

Dictionaries can be *extended* from byte vectors:

```cpp
std::vector<char> buffer(size);
some_source.read(buffer.data(), size);

Dictionary dict;
dict.extend(buffer.data(), size);
```

A single dictionary can be extended multiple times from different sources. The catch is that key collisions are ignored [for now](#contribute), so that extending ``{"a": 12}`` with ``{"a": 42, "b": 1}`` will result in ``{"a": 12, "b": 1}`` (and a warning).

### Updates

...

### Adding new types

...

## Alternatives

* [nlohmann::json](https://github.com/nlohmann/json) - ...
* [RapidJSON](https://github.com/Tencent/rapidjson/) - ...
* [std::map](https://www.cplusplus.com/reference/map/map/) - if your values all have the same type, you might as well use a standard map directly.
* [std::unordered\_map](https://www.cplusplus.com/reference/unordered_map/unordered_map/) - similar use case to ``std::map``, this variant can perform faster.

## Contribute

There are many open leads to improve this project, as you already know if you landed here from a link in this README 😉 All contributions are welcome, big or small! Make sure you read the 👷 [contribution guidelines](CONTRIBUTING.md).
