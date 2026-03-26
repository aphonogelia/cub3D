# cub3d

Raycasting engine in C — pseudo-3D rendering à la Wolfenstein 3D, built as part of the 42 Berlin curriculum.

---

## What it does

Renders a first-person 3D environment in real time using the DDA (Digital Differential Analyzer) raycasting algorithm. Reads a `.cub` map file and produces a textured, interactive scene at 60+ FPS.

---

## Technical highlights

- **Raycasting engine** — DDA algorithm for ray-wall intersection, depth-based rendering, Z-buffer
- **Texture mapping** — per-face wall textures, floor and ceiling color
- **Map parser** — validates `.cub` files, checks boundary integrity, handles malformed input gracefully
- **Bonus** — doors, mirrors, mouse look

---

## Build & run

```bash
# Standard
make
./cub3d maps/map.cub

# Bonus
make bonus
./cub3d_bonus maps/bonus.cub
```

**Dependencies:** GCC, Make, GLFW3, CMake (for MLX42)

---

## Controls

| Key | Action |
|-----|--------|
| `W A S D` | Move |
| `← →` | Rotate camera |
| `Mouse` | Look around (bonus) |
| `ESC` | Exit |

---

## Map format

```
NO ./textures/north.xpm
SO ./textures/south.xpm
EA ./textures/east.xpm
WE ./textures/west.xpm
F 220,100,0
C 225,30,0

111111111111111
100000000000001
101010101010101
100000000000001
111111111111111
```

`NO/SO/EA/WE` — wall texture paths · `F/C` — floor/ceiling RGB · `0` empty · `1` wall · `N/S/E/W` player start

---

## Structure

```
cub3d/
├── src/
│   ├── parsing/       # Map parser and validation
│   ├── raycasting/    # Engine and renderer
│   └── main.c
├── src_bonus/
├── libft/
├── MLX42/
├── maps/
├── inc/
└── inc_bonus/
```
