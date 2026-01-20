# Presentation
This is a small beginner-level 3D rendering engine. It allows you to load a textured model, add point lights and directional lights to the scene and will eventually be used for physical simulation projects in the near future. This is a personal project to improve my skills in the early stages of software development.

The project can be tested using the following demo :
https://github.com/alexislaurent1321-gif/Model_loader.git

### Upcoming improvements:
- loading non-textured models (handling of materials)
- loading multiple models
- loading models directly from the user interface
- correcting class structure (dependency between context and scene)
- unifying and improving user interface management
- bug fixes (especially with regard to the suppression of light in the scene)

# Installation

## Dependencies
The library uses the vcpkg package manager to load external libraries. To install, install **vcpkg** in the `C:/` folder.
Then, install the libraries using the following instructions :

```bash
cd /
cd vcpkg
.\vcpkg install glad
.\vcpkg install glfw
.\vcpkg install glm
.\vcpkg install stb
.\vcpkg install imgui
.\vcpkg install assimp
```
Use the following include paths in the `cpp_properties.json` : 
```
"includePath": [
                "${workspaceFolder}/**",
                "C:\\vcpkg\\installed\\x64-windows\\include",
                "include/**"
            ],
```

## Compilation

Compilation on Windows, preferably with **MSVC**. Use the **VS Code** interface if possible

# Credits
This project uses code and concepts inspired by the following tutorials:
- **[LearnOpenGL](https://learnopengl.com/)** by Joey de Vries.
  Code license : [MIT](https://opensource.org/licenses/MIT).
  Content license : [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/).
- Victor Gordan **[youtube tutorials](https://github.com/VictorGordan/opengl-tutorials)**
