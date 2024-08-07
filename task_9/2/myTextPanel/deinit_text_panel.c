#include "myTextPanel.h"

void deinit_text_panel(TextPanel **panel) {
    int err = 0;
    if ((*panel)->win) {
        err = delwin((*panel)->win);
        if (err > 0) {
            perror("ERROR: The window is the parent of another window");
        }
    }
    free(*panel);
    *panel = NULL;
}