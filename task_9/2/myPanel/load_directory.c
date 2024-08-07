#include "myPanel.h"

void load_directory(Panel *panel) {
    DIR *dir = opendir(panel->path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    panel->file_count = 0;

    strncpy(panel->files[panel->file_count], ".", MAX_PATH);
    panel->file_count++;
    strncpy(panel->files[panel->file_count], "..", MAX_PATH);
    panel->file_count++;

    while ((entry = readdir(dir)) != NULL && panel->file_count < MAX_FILES) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        strncpy(panel->files[panel->file_count], entry->d_name, MAX_PATH);
        panel->file_count++;
    }

    closedir(dir);
}