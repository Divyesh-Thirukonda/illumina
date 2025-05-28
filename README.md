# Illumina
A minimal, extensible C++ game-engine MVP inspired by Unity.

## Project Structure
    illumina/
    ├── CMakeLists.txt          # Build config
    ├── externals/              # Third-party libraries
    │   └── glfw/               # GLFW source (built via CMake)
    └── src/                    # Engine source code
        ├── main.cpp            # Entry point
        ├── Engine.h            # Engine interface
        └── Engine.cpp          # Engine implementation

## Features
- Window creation & rendering loop via GLFW  
- Simple `Engine` class with `Init`, `Run`, and `Shutdown` methods  
- Placeholder subsystems: input, update logic, rendering

## Prerequisites
- **Windows** (instructions below) or other platforms with CMake support  
- **Visual Studio 2022** (Desktop development with C++)  
- **CMake** (≥ 3.10)  
- **GLFW** source in `externals/glfw`  
- **OpenGL** (system-provided)

## Setup & Build (Windows)
1. Clone the repo:
       git clone <repo-url> illumina
       cd illumina
2. Fetch/clone GLFW source:
       git submodule add https://github.com/glfw/glfw.git externals/glfw
3. Create and enter build directory:
       mkdir build && cd build
4. Configure with CMake:
       cmake .. -G "Visual Studio 17 2022"
5. Build and run:
       cmake --build . --config Debug
       Debug\illumina.exe

## Next Steps
- Implement **Scene Graph** & **GameObject** system  
- Add **Component**-based architecture  
- Integrate **scripting** (Lua/Python)  
- Add **physics**, **asset loading**, **UI**  
