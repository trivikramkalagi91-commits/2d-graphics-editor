#include "graphics.h"

/* ── Add sub-menu ───────────────────────────────────────────────── */

void menu_add(void)
{
    print_header("ADD OBJECT");
    printf("  1. Circle\n");
    printf("  2. Rectangle\n");
    printf("  3. Line\n");
    printf("  4. Triangle\n");
    printf("  0. Back\n");

    int choice = read_int("\nChoice: ");
    char fill  = '*';

    printf("Fill character (* or _) [default *]: ");
    char c = read_char("");
    if (c == '*' || c == '_') fill = c;

    switch (choice) {
        case 1: {
            int cx = read_int("Centre X (col 0-79): ");
            int cy = read_int("Centre Y (row 0-29): ");
            int r  = read_int("Radius             : ");
            obj_add_circle(cx, cy, r, fill);
            break;
        }
        case 2: {
            int x = read_int("Top-left X (col 0-79): ");
            int y = read_int("Top-left Y (row 0-29): ");
            int w = read_int("Width                : ");
            int h = read_int("Height               : ");
            obj_add_rectangle(x, y, w, h, fill);
            break;
        }
        case 3: {
            int x1 = read_int("Start X1: ");
            int y1 = read_int("Start Y1: ");
            int x2 = read_int("End   X2: ");
            int y2 = read_int("End   Y2: ");
            obj_add_line(x1, y1, x2, y2, fill);
            break;
        }
        case 4: {
            printf("Enter 3 vertices (x,y):\n");
            int x1 = read_int("  Vertex 1 X: ");
            int y1 = read_int("  Vertex 1 Y: ");
            int x2 = read_int("  Vertex 2 X: ");
            int y2 = read_int("  Vertex 2 Y: ");
            int x3 = read_int("  Vertex 3 X: ");
            int y3 = read_int("  Vertex 3 Y: ");
            obj_add_triangle(x1, y1, x2, y2, x3, y3, fill);
            break;
        }
        case 0:
            return;
        default:
            printf("Invalid choice.\n");
    }
}

/* ── Delete sub-menu ────────────────────────────────────────────── */

void menu_delete(void)
{
    print_header("DELETE OBJECT");
    obj_list();
    if (obj_count == 0) return;

    int id = read_int("\nEnter ID to delete (0 to cancel): ");
    if (id != 0)
        obj_delete(id);
}

/* ── Modify sub-menu ────────────────────────────────────────────── */

void menu_modify(void)
{
    print_header("MODIFY OBJECT");
    obj_list();
    if (obj_count == 0) return;

    int id = read_int("\nEnter ID to modify (0 to cancel): ");
    if (id != 0)
        obj_modify(id);
}

/* ── Main menu loop ─────────────────────────────────────────────── */

void menu_main(void)
{
    canvas_clear();

    while (1) {
        canvas_render_all();
        clear_screen();

        printf("\n");
        printf("  ╔══════════════════════════════════╗\n");
        printf("  ║   2D GRAPHICS EDITOR  (*/_ mode) ║\n");
        printf("  ╚══════════════════════════════════╝\n\n");

        canvas_display();

        printf("\n");
        printf("  ┌─── MENU ─────────────────────────┐\n");
        printf("  │  1. Add object                   │\n");
        printf("  │  2. Delete object                │\n");
        printf("  │  3. Modify object                │\n");
        printf("  │  4. List all objects             │\n");
        printf("  │  5. Clear canvas                 │\n");
        printf("  │  0. Quit                         │\n");
        printf("  └──────────────────────────────────┘\n");

        int choice = read_int("\n  Choice: ");

        switch (choice) {
            case 1:
                menu_add();
                break;
            case 2:
                menu_delete();
                break;
            case 3:
                menu_modify();
                break;
            case 4:
                print_header("ALL OBJECTS");
                obj_list();
                printf("\nPress ENTER to continue...");
                getchar();
                break;
            case 5:
                /* Remove all objects */
                obj_count = 0;
                canvas_clear();
                printf("Canvas cleared.\n");
                break;
            case 0:
                printf("Goodbye!\n");
                return;
            default:
                printf("Invalid option.\n");
        }
    }
}
