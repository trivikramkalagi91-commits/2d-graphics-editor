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

---

## Build & Run

**Windows (no make):**
```bash
gcc -Wall -std=c11 -o graphics_editor main.c canvas.c draw.c objects.c menu.c utils.c -lm
.\graphics_editor.exe
```

**Linux / Mac:**
```bash
make
./graphics_editor
```

Requires: `gcc`, standard C library with `math.h`.

---

## Canvas coordinate system

```
(0,0) ──────────────────────────── (79,0)
  |                                   |
  |   col = X axis (left → right)     |
  |   row = Y axis (top  → bottom)    |
  |                                   |
(0,29) ─────────────────────────── (79,29)
```

- **X** = column, ranges from **0 to 79** (left to right)
- **Y** = row,    ranges from **0 to 29** (top to bottom)
- Centre of canvas: **X=40, Y=15**
- Shapes drawn outside these bounds get clipped at the edge

---

## Input guide — what values to enter

### Circle
| Prompt       | Good value | Notes                        |
|--------------|-----------|------------------------------|
| Fill char    | `*`       | or `_` for underscore style  |
| Centre X     | 40        | middle horizontally          |
| Centre Y     | 15        | middle vertically            |
| Radius       | 8         | keep under 15 to stay on canvas |

```
Choice: 1   (Add object)
Choice: 1   (Circle)
Fill: *
Centre X: 40
Centre Y: 15
Radius: 8
```

---

### Rectangle
| Prompt       | Good value | Notes                              |
|--------------|-----------|-------------------------------------|
| Fill char    | `*`       | or `_`                              |
| Top-left X   | 5         | left edge of rectangle              |
| Top-left Y   | 2         | top edge of rectangle               |
| Width        | 20        | X + Width must be <= 79             |
| Height       | 10        | Y + Height must be <= 29            |

```
Choice: 1   (Add object)
Choice: 2   (Rectangle)
Fill: *
Top-left X: 5
Top-left Y: 2
Width: 20
Height: 10
```

---

### Line
| Prompt  | Good value | Notes                            |
|---------|-----------|-----------------------------------|
| Fill char | `*`     | or `_`                            |
| X1      | 0         | start column                      |
| Y1      | 0         | start row (top-left corner)       |
| X2      | 79        | end column                        |
| Y2      | 29        | end row (bottom-right corner)     |

```
Choice: 1   (Add object)
Choice: 3   (Line)
Fill: *
X1: 0
Y1: 0
X2: 79
Y2: 29
```
This draws a diagonal line from top-left to bottom-right.

---

### Triangle
| Prompt      | Good value | Notes                         |
|-------------|-----------|--------------------------------|
| Fill char   | `*`       | or `_`                         |
| Vertex 1 X  | 40        | tip of triangle (top centre)   |
| Vertex 1 Y  | 2         |                                |
| Vertex 2 X  | 55        | bottom-right corner            |
| Vertex 2 Y  | 18        |                                |
| Vertex 3 X  | 25        | bottom-left corner             |
| Vertex 3 Y  | 18        |                                |

```
Choice: 1   (Add object)
Choice: 4   (Triangle)
Fill: *
Vertex 1 X: 40
Vertex 1 Y: 2
Vertex 2 X: 55
Vertex 2 Y: 18
Vertex 3 X: 25
Vertex 3 Y: 18
```

---

### Delete an object
```
Choice: 2         (Delete object)
Enter ID: 1       (use the ID shown in the object list)
```

### Modify an object
```
Choice: 3         (Modify object)
Enter ID: 1       (ID to modify)
New fill char: _  (change * to _)
... then re-enter the shape's values
```

### List all objects
```
Choice: 4         (shows all objects with their IDs and parameters)
```

### Clear canvas
```
Choice: 5         (removes all objects and clears the screen)
```

---

## Sample session — all 4 shapes together

Enter these one after another to see all shapes on one canvas:

```
1 → 1 → * → 40 → 15 → 8        (circle in centre)
1 → 2 → _ → 2  → 1  → 30 → 12  (rectangle top-left)
1 → 3 → * → 0  → 0  → 79 → 29  (diagonal line)
1 → 4 → _ → 40 → 1  → 60 → 25 → 20 → 25  (triangle)
```

---

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