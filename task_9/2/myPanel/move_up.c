#include "myPanel.h"

void move_up(Panel *panel) {
    if (panel->selected_file > 0) {
        panel->selected_file--;
    }
}