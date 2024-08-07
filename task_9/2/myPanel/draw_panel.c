#include "myPanel.h"

void draw_panel(Panel *panel, int *MAX_LENGTH) {
    if (panel == NULL) {
        return;  // TODO: Можно выводить сообщение об ошибке
    }
    werase(panel->win);
    center_list(panel);

    // Ширина столбцов
    int filename_width = *MAX_LENGTH / 2;                 // 50% для Filename
    int size_width = (*MAX_LENGTH - filename_width) / 2;  // 25% для Size
    int modified_width = *MAX_LENGTH - filename_width -
                         size_width;  // Остальное для Last Modified

    char modified_text[30];
    if (modified_width > 15) {
        strcpy(modified_text, "Last Modified");
    } else if (modified_width >= 10) {
        strcpy(modified_text, "L. Mod");
    } else {
        modified_text[0] = '\0';
    }

    wattron(panel->win, A_BOLD | COLOR_PAIR(5));
    mvwprintw(panel->win, 1, 1, "%-*s %-*s %-*s", filename_width, "Filename",
              size_width, "Size", modified_width, modified_text);
    wattroff(panel->win, A_BOLD | COLOR_PAIR(5));

    time_t current_time = time(NULL);
    struct tm *current_tm = localtime(&current_time);

    for (int i = panel->start_display;
         i < panel->file_count && i - panel->start_display < panel->height - 3;
         i++) {
        if (i == panel->selected_file) {
            wattron(panel->win, A_REVERSE);
        }

        struct stat file_stat;
        char full_path[MAX_PATH * 2];
        snprintf(full_path, sizeof(full_path), "%s/%s", panel->path,
                 panel->files[i]);

        if (stat(full_path, &file_stat) == 0) {
            // Цвет в зависимости от типа файла
            if (S_ISDIR(file_stat.st_mode)) {
                wattron(panel->win, COLOR_PAIR(1));
            } else if (file_stat.st_mode & S_IXUSR) {
                wattron(panel->win, COLOR_PAIR(2));
            } else {
                wattron(panel->win, COLOR_PAIR(3));
            }

            char date_str[30];
            struct tm *file_time = localtime(&file_stat.st_ctime);
            int year_diff = current_tm->tm_year - file_time->tm_year;

            if (modified_width > 15) {
                if (year_diff == 0) {
                    strftime(date_str, sizeof(date_str), "%b %d %H:%M",
                             file_time);
                } else {
                    strftime(date_str, sizeof(date_str), "%b %d %Y", file_time);
                }
            } else if (modified_width >= 10) {
                strftime(date_str, sizeof(date_str), "%b %d", file_time);
            } else {
                date_str[0] = '\0';
            }

            char shortened_filename[filename_width + 1];
            shorten_name(panel->files[i], shortened_filename,
                         filename_width - 1);

            char shortened_size[size_width + 1];
            shorten_number((long long)file_stat.st_size, shortened_size,
                           size_width);

            mvwprintw(panel->win, i + 2 - panel->start_display, 1,
                      "%-*s %-*s %-*s", filename_width, shortened_filename,
                      size_width, shortened_size, modified_width, date_str);

            wattroff(panel->win, COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3));
        }

        if (i == panel->selected_file) {
            wattroff(panel->win, A_REVERSE);
        }

        wclrtoeol(panel->win);
    }

    box(panel->win, 0, 0);

    char shortened_path[*MAX_LENGTH + 1];
    shorten_name(panel->path, shortened_path, *MAX_LENGTH - 10);
    mvwprintw(panel->win, 0, 1, " Path: %s ", shortened_path);

    wrefresh(panel->win);
}