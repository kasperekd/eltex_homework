#include "myPanel.h"

void center_list(Panel *panel) {
    if (panel->selected_file < 0) {
        return;
    }

    if (panel->file_count <= panel->height - 4) {
        panel->start_display = 0;
        return;
    }

    if (panel->selected_file >= panel->start_display + panel->height - 4) {
        panel->start_display = panel->selected_file - (panel->height - 4);
    } else if (panel->selected_file < panel->start_display) {
        panel->start_display = panel->selected_file;
    }

    if (panel->start_display > panel->file_count - (panel->height - 4)) {
        panel->start_display = panel->file_count - (panel->height - 4);
    }
}