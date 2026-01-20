# Presentation
This is a small beginner-level 3D rendering engine. It allows you to load a textured model, add spotlights and directional lights to the scene and will eventually be used for physical simulation projects in the near future. This is a personal project to improve my skills in the early stages of software development.

The project can be tested using the following demo :

### Upcoming improvements:
- loading multiple 
- loading models directly from the user interface
- correcting class structure (dependency between context and scene)
- unifying and improving user interface management
- bug fixes (especially with regard to the suppression of light in the scene)

# Installation

## Dependencies
The library uses the vcpkg package manager to load external libraries. To install, install vcpkg in the C:/ folder.
Then, install the libraries using the following instructions :

```bash
cd /
cd vcpkg
.\vcpkg install glad
.\vcpkg install glfw
.\vcpkg install glm
.\vcpkg install stb
.\vcpkg install assimp
```

## Compilation

Compilation on Windows, preferably with MSVC
