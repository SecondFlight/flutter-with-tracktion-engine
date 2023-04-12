This is a proof-of-concept for using Tracktion Engine in a Flutter app. This demo only supports Windows, but the concepts should be the same for other platforms supported by both Flutter and Tracktion Engine.

Tracktion Engine is built into a DLL. The code for this is self-contained in the `./engine/` folder. You could probably work this into the platform build code, but I prefer to leave it separate. If my platform build code is identical to the generated template code, then it's easier to maintain.

## Building

### Prerequisites
You will need:
- Windows
- [Flutter](https://docs.flutter.dev/get-started/install)
- A development stack for building C++ code on Windows
- [CMake](https://cmake.org/download/)

### Instructions
1. Clone the repo with `--recursive` (this repo includes JUCE and Tractkion as Git submodules)
2. `cd (repo folder)/engine`
3. Run `build.ps1`
4. Run the Flutter project using `flutter run` or from your IDE
