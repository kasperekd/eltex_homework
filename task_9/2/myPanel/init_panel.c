#include "myPanel.h"

int init_panel(Panel **panel, const char *path, int y, int x, int height,
               int width) {
    *panel = (Panel *)malloc(sizeof(Panel));
    if (*panel == NULL) {
        perror("Malloc error");
        return 1;
    }

    strncpy((*panel)->path, path, MAX_PATH);
    (*panel)->file_count = 0;
    (*panel)->selected_file = -1;
    (*panel)->last_selected = -1;
    (*panel)->y = y;
    (*panel)->x = x;
    (*panel)->height = height;
    (*panel)->width = width;
    (*panel)->start_display = 0;
    (*panel)->win = newwin(height - 4, width, y, x);
    if ((*panel)->win == NULL) {
        perror("WINDOW malloc error");
        return 1;
    }

    wrefresh((*panel)->win);
    return 0;
}