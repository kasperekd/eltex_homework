#ifndef MY_UI_UTILS_H
#define MY_UI_UTILS_H

#include "myPanel.h"
#include "myTextPanel.h"

void switch_panel(Panel **panels, int *current_panel, int *num_panels);
void resize_panels(Panel **panels, int *MAX_LENGTH, int *num_panels);
void resize_text_panels(TextPanel **panels, int *num_text_panels, int old_width,
                        int old_height, int new_width, int new_height);

#endif  // MY_UI_UTILS_H