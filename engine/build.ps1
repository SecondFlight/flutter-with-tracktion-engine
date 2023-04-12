# Make a directory `build` in `.` if it doesn't exist.
if (-not (Test-Path .\build)) {
  New-Item .\build -Type Directory
}

# Push `build` to the stack.
Push-Location .\build

# Run `cmake ..`
cmake ..

# Run `cmake --build .`
cmake --build .

# Pop `build` from the stack
Pop-Location

# Create the directory `../assets` if it doesn't exist
if (-not (Test-Path ../assets)) {
  New-Item ../assets -Type Directory
}

# Copy `./build/Debug/DemoEngine.dll` to `../assets`
Copy-Item .\build\Debug\DemoEngine.dll ../assets
