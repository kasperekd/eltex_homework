#include "myPanel.h"

void change_directory(Panel *panel) {
    if (panel->selected_file < 0) {
        return;
    }

    char new_path[MAX_PATH * 2];
    snprintf(new_path, sizeof(new_path), "%s/%s", panel->path,
             panel->files[panel->selected_file]);

    DIR *dir = opendir(new_path);
    if (dir) {
        closedir(dir);
        realpath(new_path, panel->path);  // Полный путь
        load_directory(panel);
        panel->selected_file = 0;
    } else if (errno == ENOTDIR) {
        // TODO: Выводить уведомление
    } else {
        perror("chdir");
    }
}