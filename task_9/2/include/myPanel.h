#ifndef MY_PANEL_H
#define MY_PANEL_H

#include <dirent.h>
#include <errno.h>
#include <malloc.h>
#include <ncurses.h>
#include <sys/stat.h>
#include <time.h>
#define __USE_MISC
#include <stdlib.h>
#undef __USE_MISC
#include <string.h>

#include "myFileUtils.h"

#define MAX_FILES 100
#define MAX_PATH 512

typedef struct {
    int file_count;
    int selected_file;
    int last_selected;
    int y, x, height, width;
    int start_display;
    WINDOW *win;
    char path[MAX_PATH];
    char files[MAX_FILES][MAX_PATH];
} Panel;

int init_panel(Panel **panel, const char *path, int y, int x, int height,
               int width);
void deinit_panel(Panel **panel);
void load_directory(Panel *panel);
void draw_panel(Panel *panel, int *MAX_LENGTH);
void move_up(Panel *panel);
void move_down(Panel *panel);
void change_directory(Panel *panel);
void center_list(Panel *panel);

#endif  // MY_PANEL_H