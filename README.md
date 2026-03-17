<p align="center">
  <img src="https://github.com/CanReader/SleakEngine/blob/main/logo.png" alt="SleakEngine" width="200">
</p>
<h1 align="center">SleakEngine Empty Template</h1>
<p align="center">
  <strong>Starter template for building games with SleakEngine</strong>
  <br />
  Use this template, build, and start writing game logic immediately.
</p>
<p align="center">
  <a href="LICENSE"><img src="https://img.shields.io/badge/license-MIT-blue?style=for-the-badge" alt="License"></a>
  <a href="https://github.com/CanReader/SleakEngine"><img src="https://img.shields.io/badge/C%2B%2B-23-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++23"></a>
</p>

---

## What is this?

This is a **game project template** for [SleakEngine](https://github.com/CanReader/SleakEngine). It includes:

- `Game/` &mdash; Example game logic (scenes, objects, components)
- `Client/` &mdash; Thin executable entry point
- `Engine/` &mdash; SleakEngine core, pulled in as a **git submodule**
- `scripts/` &mdash; Build helper scripts
- `docs/` &mdash; Scene system guide and documentation

The Engine is included as a git submodule. Use `git submodule update --remote` to fetch the latest version.

## Prerequisites

| Requirement | Minimum |
|---|---|
| **CMake** | 3.31+ |
| **C++ Compiler** | C++23 (MSVC, GCC, or Clang) |

All engine dependencies are vendored &mdash; no package manager needed.

## Quick Start

### 1. Create Your Repository

Click the **"Use this template"** button at the top of this page and select **"Create a new repository"**.

> **Why not fork?** Forking is for contributing back to the original. Using the template gives you a clean, independent repo with no link to this one — your game is yours entirely.

Name it after your game, choose public or private, and hit create.

### 2. Clone Your New Repository

```bash
git clone --recurse-submodules https://github.com/YourUsername/YourGameName.git
cd YourGameName
git submodule update --remote
```

> **Already cloned without `--recurse-submodules`?** Fetch the Engine submodule:
> ```bash
> git submodule update --init --recursive --remote
> ```

### Build
```bash
cmake --preset debug
cmake --build --preset debug
```

For an optimized build:
```bash
cmake --preset release
cmake --build --preset release
```

Output goes to `bin/` with all assets and runtime libraries in place.

### Run
```bash
./bin/SleakEngine -w 1280 -h 720 -t My_Game
```

| Flag | Description |
|---|---|
| `-w` | Window width |
| `-h` | Window height |
| `-t` | Window title (use `_` for spaces) |

## Project Structure

```
YourGameName/
├── CMakePresets.json      Build presets (debug / release)
├── Engine/                SleakEngine core (git submodule)
│   ├── include/           Public & private headers
│   ├── src/               Implementation
│   ├── assets/shaders/    Default shaders
│   └── vendors/           All third-party dependencies
├── Game/
│   ├── include/           Game headers
│   ├── src/               Game implementation
│   └── assets/            Textures, models, etc.
├── Client/
│   └── src/               main.cpp
├── scripts/               Build helper scripts
└── docs/                  Documentation
```

## Building Your Game

Edit `Game/src/Game.cpp` to implement your game logic:

```cpp
#include "Game.hpp"

void Game::Initialize() {
    auto* scene = CreateScene("MainScene");

    auto* player = scene->CreateObject("Player");
    player->AddComponent<Transform>();
    player->AddComponent<Mesh>();
    player->AddComponent<Material>();

    auto* camera = scene->CreateObject("Camera");
    camera->AddComponent<Transform>();
    camera->AddComponent<Camera>();

    SetActiveScene(scene);
}

void Game::Begin() {
    // Runs once after initialization
}

void Game::Loop(float DeltaTime) {
    // Runs every frame
}
```

See the **[Scene System Guide](docs/SCENE_SYSTEM_GUIDE.md)** for the complete API reference.

## Updating the Engine

To pull the latest Engine version:

```bash
cd Engine
git fetch origin
git checkout <desired-tag-or-commit>
cd ..
git add Engine
git commit -m "Update Engine to <version>"
```

Or to track the latest on the Engine's main branch:

```bash
git submodule update --remote Engine
git add Engine
git commit -m "Update Engine to latest"
```

## License

This project is released under the [MIT License](LICENSE).
