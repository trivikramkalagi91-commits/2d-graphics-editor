#include "graphics.h"

/* Safely set one pixel inside canvas bounds */
static void put_pixel(int r, int c, char ch)
{
    if (r >= 0 && r < ROWS && c >= 0 && c < COLS)
        canvas[r][c] = ch;
}

/* ── Circle (Bresenham midpoint algorithm) ────────────────────────── */
void draw_circle(Circle circ, char ch)
{
    int cx = circ.cx, cy = circ.cy, rad = circ.radius;
    int x = 0, y = rad;
    int d = 1 - rad;

    while (x <= y) {
        /* Plot 8-way symmetry */
        put_pixel(cy + y, cx + x, ch);
        put_pixel(cy - y, cx + x, ch);
        put_pixel(cy + y, cx - x, ch);
        put_pixel(cy - y, cx - x, ch);
        put_pixel(cy + x, cx + y, ch);
        put_pixel(cy - x, cx + y, ch);
        put_pixel(cy + x, cx - y, ch);
        put_pixel(cy - x, cx - y, ch);

        if (d < 0)
            d += 2 * x + 3;
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

/* ── Rectangle (outline) ─────────────────────────────────────────── */
void draw_rectangle(Rectangle rect, char ch)
{
    int x = rect.x, y = rect.y;
    int w = rect.width, h = rect.height;

    /* Top and bottom edges */
    for (int c = x; c < x + w; c++) {
        put_pixel(y,         c, ch);
        put_pixel(y + h - 1, c, ch);
    }
    /* Left and right edges */
    for (int r = y; r < y + h; r++) {
        put_pixel(r, x,         ch);
        put_pixel(r, x + w - 1, ch);
    }
}

/* ── Line (Bresenham) ────────────────────────────────────────────── */
void draw_line(Line ln, char ch)
{
    int x0 = ln.x1, y0 = ln.y1;
    int x1 = ln.x2, y1 = ln.y2;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        put_pixel(y0, x0, ch);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 <  dx) { err += dx; y0 += sy; }
    }
}

/* ── Triangle (three lines) ──────────────────────────────────────── */
void draw_triangle(Triangle tri, char ch)
{
    Line l1 = { tri.x1, tri.y1, tri.x2, tri.y2 };
    Line l2 = { tri.x2, tri.y2, tri.x3, tri.y3 };
    Line l3 = { tri.x3, tri.y3, tri.x1, tri.y1 };

    draw_line(l1, ch);
    draw_line(l2, ch);
    draw_line(l3, ch);
}
