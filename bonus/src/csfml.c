/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** run vm
*/

#include "corewar_gui.h"

sfRenderWindow *create_my_window(void)
{
    sfRenderWindow *win;

    sfVideoMode mode = {1920, 1080, 32};
    win = sfRenderWindow_create(mode, "Corewar", sfResize, NULL);
    return (win);
}

void display_texts(cgui_t *cgui, environment_t *env)
{
    static char buff[200];
    static char tab_text[10][100] = {"Cycles limit : %d", "Current cycle"
    ": %d", "Process : %d", "Nbr live : %d"};
    int tab_int[10] = {cgui->limit_cycles, env->nbr_cycle, cgui->nb_process,
    env->live_instruction_nb};

    for (int i = 0; i < 4; i++) {
        sprintf(buff, tab_text[i], tab_int[i]);
        sfText_setString(cgui->text, buff);
        sfText_setPosition(cgui->text, (sfVector2f){1650, 20 + (i * 70)});
        sfRenderWindow_drawText(cgui->win, cgui->text, NULL);
    }
}

void display_player_stats(cgui_t *cgui, environment_t *env)
{
    static char buff[200];

     for (int i = 0; i < cgui->nb_players; i++) {
         sprintf(buff, "Player %d : %s", get_list_index(PROC_HEAD(env), i)->
         prog_number, get_list_index(PROC_HEAD(env), i)->header.prog_name);
         sfText_setString(cgui->text, buff);
         sfText_setPosition(cgui->text, (sfVector2f){1650, 300 + (i * 100)});
         sfRenderWindow_drawText(cgui->win, cgui->text, NULL);
         sprintf(buff, "Cycle to die : %d", get_list_index(PROC_HEAD(env), i)
         ->cycles_to_die);
         sfText_setString(cgui->text, buff);
         sfText_setPosition(cgui->text, (sfVector2f){1680, 330 + (i * 100)});
         sfRenderWindow_drawText(cgui->win, cgui->text, NULL);
         sprintf(buff, "Cycle left : %d", get_list_index(PROC_HEAD(env), i)
         ->cycles_left);
         sfText_setString(cgui->text, buff);
         sfText_setPosition(cgui->text, (sfVector2f){1680, 350 + (i * 100)});
         sfRenderWindow_drawText(cgui->win, cgui->text, NULL);
    }
}

void display_hud(cgui_t *cgui, environment_t *env)
{
    sfColor tab[4] = {sfRed, sfGreen, sfBlue, sfYellow};

    sfRectangleShape_setFillColor(cgui->rect, sfWhite);
    sfRectangleShape_setSize(cgui->rect, (sfVector2f){8, 1080});
    sfRectangleShape_setPosition(cgui->rect, (sfVector2f){1600, 0});
    sfRenderWindow_drawRectangleShape(cgui->win, cgui->rect, NULL);
    sfRectangleShape_setSize(cgui->rect, (sfVector2f){15, 15});
    for (int i = 0; i < cgui->nb_players; i++) {
        sfRectangleShape_setFillColor(cgui->rect, tab[i]);
        sfRectangleShape_setPosition(cgui->rect, (sfVector2f){1620, 307 + (i * 100)});
        sfRenderWindow_drawRectangleShape(cgui->win, cgui->rect, NULL);
    }
    display_texts(cgui, env);
    display_player_stats(cgui, env);
}

int get_color_id(environment_t *env, int pos)
{
    if (pos > get_list_index(PROC_HEAD(env), 0)->address && pos <
    get_list_index(PROC_HEAD(env), 0)->address +
    get_list_index(PROC_HEAD(env), 0)->header.prog_size)
        return 1;
    if (pos > get_list_index(PROC_HEAD(env), 1)->address && pos <
    get_list_index(PROC_HEAD(env), 1)->address +
    get_list_index(PROC_HEAD(env), 1)->header.prog_size)
        return 2;
    if (pos > get_list_index(PROC_HEAD(env), 2)->address && pos <
    get_list_index(PROC_HEAD(env), 2)->address +
    get_list_index(PROC_HEAD(env), 2)->header.prog_size)
        return 3;
    if (pos > get_list_index(PROC_HEAD(env), 3)->address && pos <
    get_list_index(PROC_HEAD(env), 3)->address +
    get_list_index(PROC_HEAD(env), 3)->header.prog_size)
        return 4;
    return 0;
}

void display_memory(cgui_t *cgui, environment_t *env)
{
    sfColor color_tab[5] = {sfGrey, sfYellow, sfGreen, sfBlue, sfRed};
    int x = 0;
    int y = 0;
    char buff[20];

    sfRectangleShape_setSize(cgui->rect, (sfVector2f){17.7, 15.3});
    sfText_setCharacterSize(cgui->text, 8);
    for (int j = 0; j <= MEM_SIZE; j++) {
        printf("%d", j);
        sprintf(buff, "%x", j);
        sfText_setString(cgui->text, buff);
        if (x == 90) {
            x = 0;
            y++;
        }
        sfRectangleShape_setFillColor(cgui->rect,
        color_tab[get_color_id(env, j + 1)]);
        sfRectangleShape_setPosition(cgui->rect,
        (sfVector2f){1 + x * 17.7, 1 + y * 15.3});
        sfRenderWindow_drawRectangleShape(cgui->win, cgui->rect, NULL);
        x++;
    }
    printf("\n");

    sfText_setCharacterSize(cgui->text, 20);
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
    cgui->nb_players = 4;
    cgui->cycle_to_die = 2421;
    cgui->limit_cycles = 5000;
    cgui->current_cycle = 3453;
    cgui->nb_process = 39;
}

int run_vm_gui(environment_t *env)
{
    cgui_t *cgui = malloc(sizeof(cgui_t));
    init_cgui(cgui);
    sfEvent event;

    PROC_TAIL(env) = PROC_HEAD(env);
    env->cycle_to_die = CYCLE_TO_DIE;
    init_processes(env);
    while (sfRenderWindow_isOpen(cgui->win)) {

        while (PROC_TAIL(env) && env->cycle_to_die > 0) {
            check_cycles(env);
            PROC_TAIL(env) = PROC_TAIL(env)->next;
        }
        while (sfRenderWindow_pollEvent(cgui->win, &event)) {
            if (event.type == sfEvtClosed
            || sfKeyboard_isKeyPressed(sfKeyEscape))
                sfRenderWindow_close(cgui->win);
        }
        sfRenderWindow_clear(cgui->win, sfBlack);
        display_hud(cgui, env);
        display_memory(cgui, env);
        sfRenderWindow_display(cgui->win);
        sfSleep((sfTime){0.1});
        PROC_TAIL(env) = PROC_HEAD(env);
    }
    return (0);
}