#include "myUiUtils.h"

void switch_panel(Panel **panels, int *current_panel, int *num_panels) {
    panels[*current_panel]->last_selected =
        panels[*current_panel]->selected_file;
    panels[*current_panel]->selected_file = -1;
    *current_panel = (*current_panel + 1) % *num_panels;
    panels[*current_panel]->selected_file =
        panels[*current_panel]->last_selected;
}