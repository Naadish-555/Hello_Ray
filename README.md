# Hello_Ray

> Based on **Peter Shirley’s** “Ray Tracing in One Weekend.” Rendered outputs are kept in `output/`.

## Overview
A simple C++ ray tracer: camera, spheres, shading, and image output in PPM format.

## Building & Running (Visual Studio solution)
1) Open the provided `.sln` in Visual Studio.
2) Set configuration: **Release** and platform: **x64**.
3) Build (Ctrl+Shift+B).
4) Run:
   - From Visual Studio (Start without debugging).
   - Or from `Developer Command Prompt for VS`:
     ```cmd
     msbuild YourSolution.sln /p:Configuration=Release /p:Platform=x64
     ```
     Then execute the built `.exe` (typically under `x64\Release\`):
     ```cmd
     x64\Release\raytracer.exe > output\image.ppm
     ```

## Output
- Generated images are stored in `output/` (tracked).

## Next Steps
- anti-aliasing
- Metals and dielectric (glass) materials.
- Try to integrate into boids sim

## Attribution
Original tutorial by **Peter Shirley** — “Ray Tracing in One Weekend.”
