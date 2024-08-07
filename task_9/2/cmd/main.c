/*TODO
    [x]1. Фиксировать размер рамки для панелей
    [x]2. Возможность "прокрутки" содержимого панели
    [x]3. "." и ".." всегда наверху + шорткаты для них
    [x]4. Вывод информации о файле
    [x] 5. Исправить мерцания (отрисовка не через clear)
    6. Окно с информацией по навигации
    [x]7. Проверить максимально возможный путь
    8. Использовать юникод
    9. Если нет доступа к файлу - выводит сообщение
    [x]10. При запуске отрисовывать полный путь, а не "."
    11. При perror создавать новое окно с ошибкой
    [x]12. Проверить на утечки valgrind --leak-check=full ./build/main
    [x]13. Выделять память под поля структуры или структуру целиком (со
   статическими полями)
    [x]14. Изменять размер полей от размера окна
*/

#include <ncurses.h>

#include "myFileUtils.h"
#include "myPanel.h"
#include "myTextPanel.h"
#include "myUiUtils.h"

#define MAX_FILES 100
#define MAX_PATH 512  // linux max path 4096 char

#define exit goto END;

int main() {
    int current_panel = 0;  // Переменная в которую записывается текущая Panel
    int num_panels = 2;  // Максимальное количество иницализируемых Panel...
    int num_text_panels = 4;  // ... и TextPanels
    int MAX_LENGTH;  // Определяется в зависимости от размера окна

    // Выделение память под списки Panels и TextPanel
    Panel **panels = NULL;
    panels = (Panel **)malloc(num_panels * sizeof(Panel *));
    if (panels == NULL) {
        perror("Fail init panels");
        exit
    }
    for (int i = 0; i < num_panels; i++) {
        panels[i] = NULL;
    }

    TextPanel **text_panels = NULL;
    text_panels = (TextPanel **)malloc(num_text_panels * sizeof(TextPanel *));
    if (text_panels == NULL) {
        perror("Fail init text panels");
        exit
    }
    for (int i = 0; i < num_panels; i++) {
        panels[i] = NULL;
    }

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);   // Директории
    init_pair(2, COLOR_GREEN, COLOR_BLACK);  // Исполняемые файлы
    init_pair(3, COLOR_WHITE, COLOR_BLACK);   // Остальные файлы
    init_pair(4, COLOR_RED, COLOR_BLACK);     // Ошибка
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);  // Легенда

    char init_path[MAX_PATH];
    realpath(".", init_path);  // Полный путь
    // TODO: Можно сделать инициализацию через цикл, а не каждую отдельно
    int err = init_panel(&panels[0], init_path, 0, 0, LINES, COLS / 2);
    if (err > 0) {
        perror("Fail init panel 0");
        exit
    }

    err = init_panel(&panels[1], init_path, 0, COLS / 2, LINES, COLS / 2);
    if (err > 0) {
        perror("Fail init panel 1");
        exit
    }
    load_directory(panels[0]);
    load_directory(panels[1]);

    // Возможно оставить для будущей доработки ресайза TextPanel
    // int old_cols = COLS;
    // int old_lines = LINES;
    resize_panels(panels, &MAX_LENGTH, &num_panels);
    while (1) {
        for (int i = 0; i < num_panels; i++) {
            if (panels[i] != NULL) {
                draw_panel(panels[i], &MAX_LENGTH);
            }
        }
        for (int i = 0; i < num_text_panels; i++) {
            if (text_panels[i] != NULL) {
                draw_text_panel(text_panels[i]);
            }
        }

        int ch = getch();
        switch (ch) {
            case 'q':
            exit case '\t':
                switch_panel(panels, &current_panel, &num_panels);
                break;
            case KEY_UP:
                move_up(panels[current_panel]);
                break;
            case KEY_DOWN:
                move_down(panels[current_panel]);
                break;
            case '\n':
                change_directory(panels[current_panel]);
                break;
            // case 't':
            //     init_text_panel(
            //         &text_panels[0], TP_ERROR, "TEST TEXT_PANEL\0",
            //         "THIS IS A SOME TEXT On new panel\n THIS IS A NEW
            //         LINE\0", LINES / 2 - 10, COLS / 2 - 10, 10, 20);
            //     break;
            // case 'y':
            //     deinit_text_panel(&text_panels[0]);
            //     break;
            case KEY_RESIZE:
                resize_panels(panels, &MAX_LENGTH, &num_panels);
                // resize_text_panels(text_panels, &num_text_panels, old_cols,
                // old_lines, COLS, LINES); old_cols = COLS; old_lines = LINES;
                break;
        }
    }

END:
    for (int i = 0; i < num_panels; i++) {
        if (panels[i] != NULL) {
            deinit_panel(&panels[i]);
        }
    }
    if (panels != NULL) {
        free(panels);
    }

    for (int i = 0; i < num_text_panels; i++) {
        if (text_panels[i] != NULL) {
            deinit_text_panel(&text_panels[i]);
        }
    }
    if (text_panels != NULL) {
        free(text_panels);
    }
    endwin();
    return 0;
}