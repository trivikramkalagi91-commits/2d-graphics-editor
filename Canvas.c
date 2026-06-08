#include "graphics.h"

/* Global definitions */
char   canvas[ROWS][COLS];
Object objects[MAX_OBJECTS];
int    obj_count = 0;
int    next_id   = 1;

/* Fill every cell with a blank space */
void canvas_clear(void)
{
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            canvas[r][c] = BLANK_CHAR;
}

/* Redraw all live objects onto the canvas */
void canvas_render_all(void)
{
    canvas_clear();
    for (int i = 0; i < obj_count; i++) {
        Object *o = &objects[i];
        switch (o->type) {
            case OBJ_CIRCLE:
                draw_circle(o->data.circle, o->fill);
                break;
            case OBJ_RECTANGLE:
                draw_rectangle(o->data.rectangle, o->fill);
                break;
            case OBJ_LINE:
                draw_line(o->data.line, o->fill);
                break;
            case OBJ_TRIANGLE:
                draw_triangle(o->data.triangle, o->fill);
                break;
        }
    }
}

/* Print the canvas with a border */
void canvas_display(void)
{
    /* Top border */
    printf("+");
    for (int c = 0; c < COLS; c++) printf("-");
    printf("+\n");

    for (int r = 0; r < ROWS; r++) {
        printf("|");
        for (int c = 0; c < COLS; c++)
            putchar(canvas[r][c]);
        printf("|\n");
    }

    /* Bottom border */
    printf("+");
    for (int c = 0; c < COLS; c++) printf("-");
    printf("+\n");
}
