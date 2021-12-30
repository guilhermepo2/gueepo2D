![gueepo2D](branding/gueepo2D.png)

![GitHub](https://img.shields.io/github/license/guilhermepo2/gueepo2D)
[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/c%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
![GitHub repo size](https://img.shields.io/github/repo-size/guilhermepo2/gueepo2D)

# gueepo2D
gueepo2D is a simple 2D game engine, aimed towards being easy to use and easy to read!

## Design Motivations
1. Easy to use.
2. Easy to read.
3. Multiplatform.

## Features
Soon™

## Platforms
- Windows (x64) with OpenGL (SDL2)

Currently that's the only platform/backend available, here's a roadmap:

### Platforms
- [ ] **Windows (x86)** ( Still thinking about it. )
- [ ] **Linux**
- [ ] **macOS**

### Graphics Backends
- [ ] DirectX 11
- [ ] Vulkan
- [ ] Metal

## Requirements
- C++ 17
- CMake 3.10+

## Building
1. Download the repository `git clone --recursive https://github.com/guilhermepo2/gueepo2D.git`
2. Run cmake `cmake -Bbuild .` - You can download and manually set `SDL2_PATH` on `CMakeLists.txt` on the `engine/` folder, if that's not defined, CMake will download SDL2 2.0.18 automatically.
3. Open `gueepo2D.sln` on the `build/` folder.

## Learning/Documentation
As stated, this is a project that is still very early in its conception. It is on my mind to have some sort of online documentation explaining the architecture as well as how to make things using this, sample projects are in my mind as well.

## How to Contribute
Soon™

## License
This project is under MIT License which is just a fancy way to say "do whatever you want as long as you mention me"

[![Twitter](https://img.shields.io/twitter/url/https/twitter.com/guilhermepo2.svg?style=social&label=%40guilhermepo2)](https://twitter.com/guilhermepo2)
