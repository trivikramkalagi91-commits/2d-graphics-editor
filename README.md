"# 2D Graphics Editor" 
# 2D Graphics Editor

A terminal-based 2D graphics editor written in C that renders shapes using `*` and `_` characters on a 30×80 character canvas.

## Features

- Draw **Circle**, **Rectangle**, **Line**, and **Triangle** using `*` or `_`
- **Add** objects interactively through a menu
- **Delete** objects by ID
- **Modify** objects (change position, size, fill character)
- **List** all current objects with their properties
- **Clear** the canvas
- Live canvas display after every action

## Build & Run

```bash
# Compile
make

# Run
./graphics_editor

# Or in one step
make run

# Clean build artefacts
make clean
```

Requires: `gcc`, `make`, standard C library with `math.h`.

## Canvas coordinate system

```
(0,0) ──────────────────────────── (79,0)
  |                                   |
  |   col = X axis (left → right)     |
  |   row = Y axis (top  → bottom)    |
  |                                   |
(0,29) ─────────────────────────── (79,29)
```

## Project structure

| File          | Purpose                                      |
|---------------|----------------------------------------------|
| `graphics.h`  | Constants, structs, function prototypes      |
| `main.c`      | Entry point                                  |
| `canvas.c`    | Canvas init, render-all, display             |
| `draw.c`      | Bresenham circle/line, rectangle, triangle   |
| `objects.c`   | Add / delete / modify / list objects         |
| `menu.c`      | Interactive text menu                        |
| `utils.c`     | read_int, read_char, clear_screen, header    |

## Example session

```
  ╔══════════════════════════════════╗
  ║   2D GRAPHICS EDITOR  (*/_ mode) ║
  ╚══════════════════════════════════╝

+--------------------------------------------------------------------------------+
|                                                                                |
|                          *****                                                 |
|                       ***     ***                                              |
|                      *           *                                             |
|                      *           *                                             |
|                       ***     ***                                              |
|                          *****                                                 |
|                                                                                |
+--------------------------------------------------------------------------------+

  ┌─── MENU ─────────────────────────┐
  │  1. Add object                   │
  │  2. Delete object                │
  │  3. Modify object                │
  │  4. List all objects             │
  │  5. Clear canvas                 │
  │  0. Quit                         │
  └──────────────────────────────────┘
```