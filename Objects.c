#include "graphics.h"

/* ── Internal helper ────────────────────────────────────────────── */

/* Return a pointer to the object with the given id, or NULL */
Object *obj_find(int id)
{
    for (int i = 0; i < obj_count; i++)
        if (objects[i].id == id)
            return &objects[i];
    return NULL;
}

/* ── Add functions ──────────────────────────────────────────────── */

int obj_add_circle(int cx, int cy, int radius, char fill)
{
    if (obj_count >= MAX_OBJECTS) {
        printf("ERROR: object list full.\n");
        return -1;
    }
    Object *o      = &objects[obj_count++];
    o->id          = next_id++;
    o->type        = OBJ_CIRCLE;
    o->fill        = fill;
    o->data.circle = (Circle){ cx, cy, radius };
    printf("Circle added with ID %d.\n", o->id);
    return o->id;
}

int obj_add_rectangle(int x, int y, int w, int h, char fill)
{
    if (obj_count >= MAX_OBJECTS) {
        printf("ERROR: object list full.\n");
        return -1;
    }
    Object *o         = &objects[obj_count++];
    o->id             = next_id++;
    o->type           = OBJ_RECTANGLE;
    o->fill           = fill;
    o->data.rectangle = (Rectangle){ x, y, w, h };
    printf("Rectangle added with ID %d.\n", o->id);
    return o->id;
}

int obj_add_line(int x1, int y1, int x2, int y2, char fill)
{
    if (obj_count >= MAX_OBJECTS) {
        printf("ERROR: object list full.\n");
        return -1;
    }
    Object *o    = &objects[obj_count++];
    o->id        = next_id++;
    o->type      = OBJ_LINE;
    o->fill      = fill;
    o->data.line = (Line){ x1, y1, x2, y2 };
    printf("Line added with ID %d.\n", o->id);
    return o->id;
}

int obj_add_triangle(int x1, int y1, int x2, int y2,
                     int x3, int y3, char fill)
{
    if (obj_count >= MAX_OBJECTS) {
        printf("ERROR: object list full.\n");
        return -1;
    }
    Object *o        = &objects[obj_count++];
    o->id            = next_id++;
    o->type          = OBJ_TRIANGLE;
    o->fill          = fill;
    o->data.triangle = (Triangle){ x1, y1, x2, y2, x3, y3 };
    printf("Triangle added with ID %d.\n", o->id);
    return o->id;
}

/* ── Delete ─────────────────────────────────────────────────────── */

int obj_delete(int id)
{
    for (int i = 0; i < obj_count; i++) {
        if (objects[i].id == id) {
            /* Shift remaining objects left */
            for (int j = i; j < obj_count - 1; j++)
                objects[j] = objects[j + 1];
            obj_count--;
            printf("Object %d deleted.\n", id);
            return 0;
        }
    }
    printf("ERROR: ID %d not found.\n", id);
    return -1;
}

/* ── Modify ─────────────────────────────────────────────────────── */

int obj_modify(int id)
{
    Object *o = obj_find(id);
    if (!o) {
        printf("ERROR: ID %d not found.\n", id);
        return -1;
    }

    printf("\nModifying object %d (type %d).\n", id, o->type);
    printf("Choose fill character (* or _): ");
    char fill = read_char("");
    if (fill == '*' || fill == '_') o->fill = fill;

    switch (o->type) {
        case OBJ_CIRCLE:
            o->data.circle.cx     = read_int("New centre X: ");
            o->data.circle.cy     = read_int("New centre Y: ");
            o->data.circle.radius = read_int("New radius  : ");
            break;

        case OBJ_RECTANGLE:
            o->data.rectangle.x      = read_int("New top-left X: ");
            o->data.rectangle.y      = read_int("New top-left Y: ");
            o->data.rectangle.width  = read_int("New width     : ");
            o->data.rectangle.height = read_int("New height    : ");
            break;

        case OBJ_LINE:
            o->data.line.x1 = read_int("New X1: ");
            o->data.line.y1 = read_int("New Y1: ");
            o->data.line.x2 = read_int("New X2: ");
            o->data.line.y2 = read_int("New Y2: ");
            break;

        case OBJ_TRIANGLE:
            o->data.triangle.x1 = read_int("New X1: ");
            o->data.triangle.y1 = read_int("New Y1: ");
            o->data.triangle.x2 = read_int("New X2: ");
            o->data.triangle.y2 = read_int("New Y2: ");
            o->data.triangle.x3 = read_int("New X3: ");
            o->data.triangle.y3 = read_int("New Y3: ");
            break;
    }

    printf("Object %d updated.\n", id);
    return 0;
}

/* ── List all objects ───────────────────────────────────────────── */

void obj_list(void)
{
    if (obj_count == 0) {
        printf("  (no objects)\n");
        return;
    }

    static const char *type_name[] = {
        "", "Circle", "Rectangle", "Line", "Triangle"
    };

    printf("  %-4s  %-10s  %-5s  Details\n", "ID", "Type", "Fill");
    printf("  %-4s  %-10s  %-5s  -------\n", "--", "----", "----");

    for (int i = 0; i < obj_count; i++) {
        Object *o = &objects[i];
        printf("  %-4d  %-10s  %-5c  ", o->id,
               type_name[o->type], o->fill);

        switch (o->type) {
            case OBJ_CIRCLE:
                printf("cx=%d cy=%d r=%d",
                       o->data.circle.cx,
                       o->data.circle.cy,
                       o->data.circle.radius);
                break;
            case OBJ_RECTANGLE:
                printf("x=%d y=%d w=%d h=%d",
                       o->data.rectangle.x,
                       o->data.rectangle.y,
                       o->data.rectangle.width,
                       o->data.rectangle.height);
                break;
            case OBJ_LINE:
                printf("(%d,%d)->(%d,%d)",
                       o->data.line.x1, o->data.line.y1,
                       o->data.line.x2, o->data.line.y2);
                break;
            case OBJ_TRIANGLE:
                printf("(%d,%d) (%d,%d) (%d,%d)",
                       o->data.triangle.x1, o->data.triangle.y1,
                       o->data.triangle.x2, o->data.triangle.y2,
                       o->data.triangle.x3, o->data.triangle.y3);
                break;
        }
        putchar('\n');
    }
}
