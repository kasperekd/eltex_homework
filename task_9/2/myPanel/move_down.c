#include "myPanel.h"

void move_down(Panel *panel) {
    if (panel->selected_file < panel->file_count - 1) {
        panel->selected_file++;
    }
}