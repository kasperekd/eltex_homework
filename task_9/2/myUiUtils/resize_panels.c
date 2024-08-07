#include "myUiUtils.h"

void resize_panels(Panel **panels, int *MAX_LENGTH, int *num_panels) {
    int half_width = COLS / 2;
    *MAX_LENGTH = half_width;  // Логика сокращения длины названия

    for (int i = 0; i < *num_panels; i++) {
        if (panels[i] != NULL) {
            panels[i]->width = half_width;
            panels[i]->height = LINES;
        }
    }
    for (int i = 0; i < *num_panels; i++) {
        if (panels[i] != NULL) {
            wresize(panels[i]->win, panels[i]->height, panels[i]->width);
        }
    }
    if (panels[*num_panels - 1] != NULL) {
        mvwin(panels[*num_panels - 1]->win, 0, half_width);
        // FIXME: тут происходит сдвиг окон, но пока только одно правое налево.
        // Если окон будет больше 2, то так может не сработает.
    }

    refresh();
}