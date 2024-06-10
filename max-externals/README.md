# Airwindows Max/MSP externals

## How to compile

### macOS

Generate the Xcode projects using:

```shell
mkdir build
cd build
cmake -G Xcode ..
```

Then either open the Xcode project file for each external (e.g. `build/source/projects/MV~/MV_tilde.xcodeproj`) and run the build with the Xcode GUI, or build all externals with the command (from inside the `build/` director created above):

```shell
cmake --build .
```

### Windows

Check the official Max SDK docs. The process will be similar to the instructions for macOS above using CMake.
- https://github.com/Cycling74/max-sdk
- https://www.youtube.com/watch?v=il5WblTBUgs
