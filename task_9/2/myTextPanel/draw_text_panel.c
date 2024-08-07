#include "myTextPanel.h"

void draw_text_panel(TextPanel *panel) {
    if (panel == NULL) {
        return;  // TODO: Можно выводить сообщение об ошибке
    }
    // TODO: Добавить изменение цвета окна в зависимости от type
    werase(panel->win);

    mvwprintw(panel->win, 1, 1, "%s", panel->text);
    // mvwprintw(panel->win, 1 , 1, "%dx%d\n %dx%d", panel->width,
    // panel->height, panel->x, panel->y);

    box(panel->win, 0, 0);
    mvwprintw(panel->win, 0, 1, "%s", panel->label);

    // wclrtoeol(panel->win);
    wrefresh(panel->win);
}
