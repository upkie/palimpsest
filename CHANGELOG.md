# Changelog

All notable changes to this project will be documented in this file.

## [2.0.0] - 2023/10/09

### Breaking changes

- Remove `extend` function
- Remove `insert_initializer` function
- The `update` function now inserts keys that are not already present

### Added

- Bazel: Find clang-format on various operating systems

### Changed

- Add underscore suffix to private functions
- Bazel: Separate coverage, linting and testing jobs
- Bazel: Update Bazelisk script
- Compile in optimized rather than fast-build mode by default
- Remove Makefile from examples directory

## [1.1.0] - 2022/10/04

### Added

- CMake workflow alongside Bazel in CI
- Lint-only test config
- Report unit test coverage
- Unit tests for ``mpack::Writer``
- Unit tests for ``mpack::read`` functions

### Fixed

- Bazel: Label ``build_file`` attributes for downstream dependencies

## [1.0.0] - 2022/04/25

This is the initial release of _palimpsest_, a small C++ library that provides a ``Dictionary`` type meant for fast value updates and serialization. It is called palimpsest because these dictionaries are designed for frequent rewritings (values change fast) on the same support (keys change slow).
