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
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
cargo install sccache
echo 'export PATH="$HOME/.cargo/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
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
