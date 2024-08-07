#include "myUiUtils.h"

void resize_text_panels(TextPanel **panels, int *num_text_panels, int old_width,
                        int old_height, int new_width, int new_height) {
    // FIXME: Требуются множественные доработки
    int delta_x, delta_y;
    if (old_width < new_width) {
        delta_x = new_width - old_width;
    }
    if (old_width >= new_width) {
        delta_x = old_width - new_width;
    }
    // delta_x = new_width - old_width;
    delta_y = new_height - old_height;

    for (int i = 0; i < *num_text_panels; i++) {
        if (panels[i] == NULL) {
            continue;
        }

        TextPanel *panel = panels[i];
        if (old_width < new_width) {
            panel->x = (int)(panel->x + delta_x);
        }
        if (old_width >= new_width) {
            panel->x = (int)(panel->x - delta_x);
        }

        panel->y = (int)(panel->y + delta_y);

        mvwin(panel->win, panel->y, panel->x);
        wresize(panel->win, panel->height, panel->width);
    }
}