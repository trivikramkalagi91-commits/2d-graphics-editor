#include "graphics.h"

/* Read a single integer from stdin with a prompt */
int read_int(const char *prompt)
{
    int val = 0;
    char buf[64];

    printf("%s", prompt);
    fflush(stdout);

    if (fgets(buf, sizeof(buf), stdin) != NULL)
        val = atoi(buf);

    return val;
}

/* Read a single non-whitespace character; flush the rest of the line */
char read_char(const char *prompt)
{
    char buf[64];
    if (*prompt) printf("%s", prompt);
    fflush(stdout);

    if (fgets(buf, sizeof(buf), stdin) != NULL) {
        for (int i = 0; buf[i]; i++) {
            if (buf[i] != '\n' && buf[i] != '\r' && buf[i] != ' ')
                return buf[i];
        }
    }
    return '\0';
}

/* Portable screen-clear (works on Linux/macOS and Windows) */
void clear_screen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* Print a section header */
void print_header(const char *title)
{
    printf("\n  ── %s ──\n\n", title);
}
