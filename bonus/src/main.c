#include "corewar_gui.h"

sfRenderWindow *create_my_window(void)
{
    sfRenderWindow *win;

    sfVideoMode mode = {1920, 1080, 32};
    win = sfRenderWindow_create(mode, "Corewar", sfResize, NULL);
    return (win);
}

void display_texts(cgui_t *cgui)
{
    static char buff[200];
    static char tab_text[10][100] = {"Cycles limit : %d", "Current cycle : %d", "Process : %d"};
    int tab_int[10] = { cgui->limit_cycles, cgui->current_cycle, cgui->nb_process};

    for (int i = 0; i < 3; i++) {
        sprintf(buff, tab_text[i], tab_int[i]);
        sfText_setString(cgui->text, buff);
        sfText_setPosition(cgui->text, (sfVector2f){1450, 20 + (i * 70)});
        sfRenderWindow_drawText(cgui->win, cgui->text, NULL);
    }
}

void display_player_stats(cgui_t *cgui)
{
    static char buff[200];

    for (int i = 0; i < cgui->nb_players; i++) {
        sprintf(buff, "Player %d -> %s", i + 1, cgui->players_names[i]);
        sfText_setString(cgui->text, buff);
        sfText_setPosition(cgui->text, (sfVector2f){1450, 300 + (i * 100)});
        sfRenderWindow_drawText(cgui->win, cgui->text, NULL);

        sprintf(buff, "Last live : %d", cgui->last_live[i]);
        sfText_setString(cgui->text, buff);
        sfText_setPosition(cgui->text, (sfVector2f){1480, 330 + (i * 100)});
        sfRenderWindow_drawText(cgui->win, cgui->text, NULL);

        sprintf(buff, "Live in current period : %d", cgui->live_in_the_current_period[i]);
        sfText_setString(cgui->text, buff);
        sfText_setPosition(cgui->text, (sfVector2f){1480, 350 + (i * 100)});
        sfRenderWindow_drawText(cgui->win, cgui->text, NULL);
    }
}

void display_hud(cgui_t *cgui)
{
    // white line
    sfRectangleShape_setFillColor(cgui->rect, sfWhite);
    sfRectangleShape_setSize(cgui->rect, (sfVector2f){8, 1080});
    sfRectangleShape_setPosition(cgui->rect, (sfVector2f){1400, 0});
    sfRenderWindow_drawRectangleShape(cgui->win, cgui->rect, NULL);
    // texts
    display_texts(cgui);
    display_player_stats(cgui);
}




void display_corewar(cgui_t *cgui)
{
    sfEvent event;

    while (sfRenderWindow_isOpen(cgui->win)) {
        while (sfRenderWindow_pollEvent(cgui->win, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(cgui->win);
        }
        sfRenderWindow_clear(cgui->win, sfBlack);
        display_hud(cgui);
        sfRectangleShape_setSize(cgui->rect, (sfVector2f){8, 8});
        for (int j = 0; j < 150; j++) {
            for (int i = 0; i < 150; i++) {
                if (i % 2)
                    sfRectangleShape_setFillColor(cgui->rect, sfRed);
                else
                    sfRectangleShape_setFillColor(cgui->rect, sfBlue);
                sfRectangleShape_setPosition(cgui->rect, (sfVector2f){10 + i * 8, 10 + j * 8});
                sfRenderWindow_drawRectangleShape(cgui->win, cgui->rect, NULL);
            }
        }
        sfRenderWindow_display(cgui->win);
    }
}

void init_cgui(cgui_t *cgui)
{
    cgui->win = create_my_window();
    cgui->rect = sfRectangleShape_create();
    cgui->font = sfFont_createFromFile("asset/font.ttf");
    cgui->text = sfText_create();
    sfText_setFont(cgui->text, cgui->font);
    sfRectangleShape_setOutlineColor(cgui->rect, sfBlack);
    sfRectangleShape_setOutlineThickness(cgui->rect, 1);
    sfText_setFillColor(cgui->text, sfWhite);
    sfText_setCharacterSize(cgui->text, 20);
    // Variables :
    cgui->nb_players = 4;
    strcpy(cgui->players_names[0], "toto");
    strcpy(cgui->players_names[1], "titi");
    strcpy(cgui->players_names[2], "tutu");
    strcpy(cgui->players_names[3], "tata");
    cgui->last_live[0] = 12;
    cgui->last_live[1] = 12;
    cgui->last_live[2] = 12;
    cgui->last_live[3] = 12;
    cgui->cycle_to_die = 2421;
    cgui->live_in_the_current_period[0] = 23;
    cgui->live_in_the_current_period[1] = 23;
    cgui->live_in_the_current_period[2] = 23;
    cgui->live_in_the_current_period[3] = 23;
    cgui->limit_cycles = 5000;
    cgui->current_cycle = 3453;
    cgui->nb_process = 39;
}

int main(void)
{
    cgui_t *cgui = malloc(sizeof(cgui_t));
    init_cgui(cgui);

    display_corewar(cgui);
    return (0);
}