#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Canvas dimensions */
#define ROWS 30
#define COLS 80
#define MAX_OBJECTS 100

/* Object types */
#define OBJ_CIRCLE    1
#define OBJ_RECTANGLE 2
#define OBJ_LINE      3
#define OBJ_TRIANGLE  4

/* Draw characters */
#define FILL_CHAR  '*'
#define EMPTY_CHAR '_'
#define BLANK_CHAR ' '

/* ─── Data Structures ───────────────────────────────────────────────── */

typedef struct {
    int cx, cy;   /* centre */
    int radius;
} Circle;

typedef struct {
    int x, y;     /* top-left corner */
    int width;
    int height;
} Rectangle;

typedef struct {
    int x1, y1;
    int x2, y2;
} Line;

typedef struct {
    int x1, y1;  /* vertex 1 */
    int x2, y2;  /* vertex 2 */
    int x3, y3;  /* vertex 3 */
} Triangle;

typedef union {
    Circle    circle;
    Rectangle rectangle;
    Line      line;
    Triangle  triangle;
} ShapeData;

typedef struct {
    int       id;
    int       type;
    ShapeData data;
    char      fill;   /* '*' or '_' */
} Object;

/* ─── Canvas ────────────────────────────────────────────────────────── */
extern char canvas[ROWS][COLS];
extern Object objects[MAX_OBJECTS];
extern int    obj_count;
extern int    next_id;

/* ─── Function Prototypes ───────────────────────────────────────────── */

/* canvas.c */
void canvas_clear(void);
void canvas_display(void);
void canvas_render_all(void);

/* draw.c */
void draw_circle(Circle c, char ch);
void draw_rectangle(Rectangle r, char ch);
void draw_line(Line l, char ch);
void draw_triangle(Triangle t, char ch);

/* objects.c */
int  obj_add_circle(int cx, int cy, int radius, char fill);
int  obj_add_rectangle(int x, int y, int w, int h, char fill);
int  obj_add_line(int x1, int y1, int x2, int y2, char fill);
int  obj_add_triangle(int x1, int y1, int x2, int y2,
                      int x3, int y3, char fill);
int  obj_delete(int id);
int  obj_modify(int id);
void obj_list(void);
Object *obj_find(int id);

/* menu.c */
void menu_main(void);
void menu_add(void);
void menu_delete(void);
void menu_modify(void);

/* utils.c */
int  read_int(const char *prompt);
char read_char(const char *prompt);
void clear_screen(void);
void print_header(const char *title);

#endif /* GRAPHICS_H */
