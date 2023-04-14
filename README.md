This is a proof-of-concept for using Tracktion Engine in a Flutter app. This demo only supports Windows, but the concepts should be the same for other platforms supported by both Flutter and Tracktion Engine.

## Branches

This repository contains two branches. The `main` branch contains a demo with JUCE and Tracktion Engine. The `juce-sine-tone` branch contains a simpler demo with only JUCE.

## Building

### Prerequisites
You will need:
- Windows
- [Flutter](https://docs.flutter.dev/get-started/install)
- A development stack for building C++ code on Windows
- [CMake](https://cmake.org/download/)

### Instructions
1. Clone the repo
2. Run `git submodule init` and `git submodule update` in the root of the repository
3. `cd (repo folder)/engine`
4. Run `build.ps1`
5. Run the Flutter project using `flutter run` or from your IDE

## A note on bundling

In this demo, Tracktion Engine is built into a DLL. The code for this is self-contained in the `./engine/` folder. I haven't found a good way to work this into the platform build code yet. I really don't want to modify the platform build code to do this - if my platform build code is identical to the generated template code, then it's easier to maintain, and I want any changes to this code to be easy to re-apply if I ever need to update the platform build code to match the latest template from Flutter.

However, there is an issue. `DemoEngine.dll` should really be bundled with the application executable. As far as I can tell, Flutter doesn't provide a way to do this without modifying platform build code. The way I'm doing it here is hacky. I'm bundling the DLL as an asset, and hard-coding the relative path to the asset when I load the DLL. This feels especially bad because Flutter could reasonably change this path in the future, and it could reasonably vary by platform.

This isn't an issue I've solved to my satisfaction yet, but I'm sure there's a good way to do it, which I'll go hunting for at some point.
