#include "myTextPanel.h"

int init_text_panel(TextPanel **panel, int type, const char *label,
                    const char *text, int y, int x, int height, int width) {
    (*panel) = malloc(sizeof(TextPanel));
    if (*panel == NULL) {
        perror("Malloc error");
        return 1;
    }
    (*panel)->type = type;
    (*panel)->y = y;
    (*panel)->x = x;
    (*panel)->height = height;
    (*panel)->width = width;
    strncpy((*panel)->label, label, 128);
    strncpy((*panel)->text, text, 256);

    (*panel)->win = newwin(height - 4, width, y, x);
    wrefresh((*panel)->win);
    return 0;
}