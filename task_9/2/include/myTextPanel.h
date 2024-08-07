#ifndef MY_TEXT_PANEL_H
#define MY_TEXT_PANEL_H

#include <malloc.h>
#include <ncurses.h>
#include <string.h>

#define TP_MAX_LABEL 128
#define TP_MAX_TEXT 256

// TextPanel types:
#define TP_INFO 1
#define TP_TEXT 2
#define TP_ERROR 3

typedef struct {
    int type;
    int y, x, height, width;
    WINDOW *win;
    char label[TP_MAX_LABEL];
    char text[TP_MAX_TEXT];
} TextPanel;

int init_text_panel(TextPanel **panel, int type, const char *label,
                    const char *text, int y, int x, int height, int width);
void deinit_text_panel(TextPanel **panel);
void draw_text_panel(TextPanel *panel);

#endif  // MY_TEXT_PANEL_H