# Guide for MapLibre Native

This document provides a concise guide for

## Build Instructions Summary

## Setup

Clone the repository with submodules:

```
git submodule update --recursive
```

Install dependencies:

```
apt install build-essential clang cmake ninja-build pkg-config libcurl4-openssl-dev libglfw3-dev libuv1-dev libpng-dev libicu-dev libjpeg-turbo8-dev libwebp-dev xvfb libegl1-mesa-dev
```

Also install `sccache`:

```
curl -LO https://github.com/mozilla/sccache/releases/download/v0.10.0/sccache-dist-v0.10.0-x86_64-unknown-linux-musl.tar.gz
tar -xzf sccache-dist-v0.10.0-x86_64-unknown-linux-musl.tar.gz
sudo mv sccache-dist-v0.10.0-x86_64-unknown-linux-musl/sccache-dist /usr/local/bin/sccache
sudo chmod +x /usr/local/bin/sccache
rm -rf sccache-dist-v0.10.0-x86_64-unknown-linux-musl*
```

Configure the CMake project:

```
cmake --preset linux-opengl-sccache
```

## Building

Before making any commits always make sure that the project builds:

```
cmake --build build-linux-opengl
```
