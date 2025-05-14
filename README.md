# Platforms

_This project is a work in progress._

**Platforms** is a 2D platformer game built with **Raylib**, **C++**, and **Tiled** for level design. This project is a personal exploration into game development without the use of a full game engine.

The focus is on learning low-level game architecture, rendering, and level parsing. If you're interested in how to integrate Tiled maps into a Raylib-based game, you may find the tilemap loading and `.tmx` parsing code particularly useful.

Feel free to explore, adapt, or reuse any part of the project.

---

## 🛠 Building

All dependencies are included as Git submodules. Make sure to initialize them recursively after cloning this repo.

This project uses **CMake** for building. A cross-platform configuration is provided, including support for building a web version using **Emscripten**.

To build the web version, you'll need to already have Emscripten installed.

On Windows, PowerShell scripts are included to:

- Build the web version.
- Serve the output using Python (required for WASM to function correctly — opening the HTML file directly will not work).

---

## 📦 Dependencies

- [Raylib](https://www.raylib.com/)
- [tinyxml2](https://github.com/leethomason/tinyxml2)

---

## 🎨 Acknowledgements

This project uses the [Brackeys Platformer Assets](https://brackeysgames.itch.io/brackeys-platformer-bundle).  
All visual assets belong to their respective creators.
