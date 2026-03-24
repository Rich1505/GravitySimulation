# Gravity Simulation

A real-time N-body gravitational simulation built with [raylib](https://www.raylib.com/) and [raygui](https://github.com/raysan5/raygui). Simulate planetary systems, watch bodies collide and merge, and interactively add or drag celestial objects.

---

## Features

- **N-body gravity** — every body exerts gravitational force on every other body using Newton's law of universal gravitation
- **Inelastic collisions** — when two bodies collide, they merge into a single body conserving total mass
- **Circular orbit calculator** — automatically computes the correct initial velocity for a circular orbit around a target body
- **Interactive drag** — click and hold to drag any body with the mouse
- **Body spawning** — click anywhere in the simulation space to spawn a new body with a chosen mass and color
- **Orbit trails** — each body leaves a fading trail showing its recent trajectory
- **Adjustable simulation speed** — speed up or slow down time on the fly
- **Pause / resume** — freeze the simulation at any moment
- **Camera controls** — pan with right-click drag, zoom with the mouse wheel
- **Resizable window** — the UI adapts dynamically to window size changes

---

## Controls

| Input | Action |
|---|---|
| `Space` | Pause / Resume |
| `↑` / `↓` Arrow Keys | Increase / Decrease simulation speed |
| Right-click + Drag | Pan camera |
| Mouse Wheel | Zoom in / out |
| Left-click (short) | Spawn new body at cursor position |
| Left-click + Hold | Drag the body under the cursor |
| Color buttons (UI) | Select color for the next spawned body |
| Mass selector (UI) | Set mass for the next spawned body |

---

## Project Structure

```
.
├── CMakeLists.txt        # Build configuration (fetches raylib and raygui)
├── src/
│   ├── main.cpp          # Entry point
│   ├── Game.cpp / .h     # Main game loop, rendering, and camera
│   ├── Physics.cpp / .h  # Gravitational force, collision, orbit math
│   ├── Body.cpp / .h     # Celestial body data and movement logic
│   ├── UserInterface.cpp / .h  # UI panels, buttons, input handling
```

---

## Dependencies

| Library | Version | Purpose |
|---|---|---|
| [raylib](https://github.com/raysan5/raylib) | 5.5 | Window, rendering, input |
| [raygui](https://github.com/raysan5/raygui) | latest (master) | Immediate-mode GUI widgets |

Both libraries are fetched automatically by CMake via `FetchContent` — no manual installation required.

---

## Building

### Prerequisites

- CMake ≥ 3.11
- A C++17-compatible compiler (GCC, Clang, or MSVC)
- Git (for raygui FetchContent)

### Steps

```bash
# Clone the repository
git clone <repository-url>
cd <repository-folder>

# Configure the build
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Compile
cmake --build build

# Run
./build/raylib_game
```

> **macOS**: The required system frameworks (`IOKit`, `Cocoa`, `OpenGL`) are linked automatically by CMakeLists.txt.

---

## Physics Model

The simulation uses a simplified Newtonian model:

**Gravitational force** between two bodies *a* and *b*:

```
F = G * (m_a * m_b) / r²
```

where `G = 1.0` (dimensionless, tuned for the simulation scale).

**Body radius** is derived from mass assuming uniform density:

```
r = cbrt( (3 * mass) / (4 * π * density) )
```

**Integration** uses Euler's method, applied `gameSpeed` times per frame with a clamped delta time (max `0.1 s`) to prevent instability during window events such as dragging.

**Collision** is inelastic: the lighter body is removed and the heavier one absorbs its mass, with its radius updated accordingly.

---

## Default Scene

On startup, the simulation initializes with:

- A massive central star (`mass = 800,000`, yellow)
- A small planet (`mass = 5,000`, white) placed at offset `(0, -700)` and given the exact circular orbit velocity around the star

---

## License

This project is provided as-is for educational and personal use. See `LICENSE` for details if present.
