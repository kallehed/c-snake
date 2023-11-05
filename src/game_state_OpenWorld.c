#include "game_state_OpenWorld.h"
#include "level_declarations.h"
#include "maze_stuff.h"
#include "player_related.h"
#include "raylib.h"
#include "snake_pather.h"
#include "very_general.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void level_set_OpenWorld(Level *mg)
{
    mg->frame_code = (Level_Frame_Code)game_state_frame_OpenWorld;
    mg->init_code = (Level_Init_Code)game_state_init_OpenWorld;
    mg->size = (sizeof(Game_State_OpenWorld));
}

void game_state_init_OpenWorld(Game_State_OpenWorld *new_g, Allo *allo, Sound sounds[])
{
    Game_State_OpenWorld g;
    g.w = world_state0_init_general(GAME_STATE_OPENWORLD_WIDTH, GAME_STATE_OPENWORLD_HEIGHT, 20, sounds);
	g.player = player_init((Pos){6,5},2, 100,Dir_Right, allo);
    g.time_for_move = 1.0;

    const char *map[] = {
        "--------------------------------------------------------------------------------------|------------|",
        "--------------------------------------------------------------------------------------|------------|",
        "--------------------------------------------------------------------------------------|------------|",
        "--------------------------------------------------------------------------------------|------------|",
        "--------------------------------------------------------------------------------------|------------|",
        "--------------------------------------------------------------------------------------|------F-----|",
        "--------------------------------------------------------------------------------------|------------|",
        "--------------------------------------------------------------------------------------|------------|",
        "--------------------------------------------------------------------------------------|------------|",
        "--------------------------------------------------------------------------------------|------------|",
        "--------------------------------------------------------------------------------------||||||||||||||",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "--------------------------------------------------------------------------|-------------------------",
        "------------------------------------------------------------------------|||-------------------------",
        "-----------------------------------------------------------------------||||-------------------------",
        "---------------------------------------------------------------------||||||-------------------------",
        "--------------------------------------------------------------------|||||||-------------------------",
        "------------------------------------------------------------------|||||||||-------------------------",
        "---------------------------------------------------------------------------F------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "-----------------------------------|----------|-----------------------------------------------------",
        "-----------------------------------|----------|-----------------------------------------------------",
        "-----------------------------------|----------|-----------------------------------------------------",
        "-----------------------------------|----------|-----------------------------------------------------",
        "-----------------------------------|-----F----|-----------------------------------------------------",
        "-----------------------------------|----------|-----------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "---------------------------|||||||--------------||||||||--------------------------------------------",
        "----------------------------------|||||||||||||||---------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "S---------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "--------------------------|-------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "-----------------------------|----------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------|-----------------------------------------------------------------------",
        "----------------------------------|-----------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "------------------------------||||||||||||||||||||--------------------------------------------------",
        "------------------------------|-----------------S|--------------------------------------------------",
        "------------------------------|-||||||||||||||||-|--------------------------------------------------",
        "------------------------------|-|S----|---|----|-|-----------------------------S--------------------",
        "------------------------------|-|--||-|---|----|-|--------------------------------------------------",
        "------------------------------|-|--||-|---|----|-|--------------------------------------------------",
        "------------------------------|-|--||-|---|----|-|----------------------------------F---------------",
        "------------------------------|-|--||-|---|----|-|--------------------------------------------------",
        "------------------------------|-|--||-|---|----|-|--------------------------------------------------",
        "------------------------------|----||----------|-|--------------------------------------------------",
        "------------------------------|-|--||--------F-|---------------------------------------S------------",
        "------------------------------|----||----------|-|--------------------------------------------------",
        "------------------------------|-|--||-|---|----|-|--------------------------------------------------",
        "------------------------------|-|--||-|---|----|-|--------------------------------------------------",
        "------------------------------|-|--||-|---|----|-|--------------------------------------------------",
        "----------S-------------------|-|--||-|---|----|-|--------------------------------------------------",
        "------------------------------|-|-----|---|----|-|--------------------------------------------------",
        "-------------F----------------|-||||||||||||||||-|--------------------------------------------------",
        "------------------------------|------------------|--------------------------------------------------",
        "------------------------------||||||||||||||||||||--------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
        "----------------------------------------------------------------------------------------------------",
    };
    Int tail_lengths[GAME_STATE_OPENWORLD_PATHERS];
    Dir tail_dirs[GAME_STATE_OPENWORLD_PATHERS];

    Int p_idx = 0;
    {
        Snake_Pather_Way ways[] = {
            {.dir = Dir_Right, .len = 100},
        };

        tail_lengths[p_idx] = 30;
        tail_dirs[p_idx] = Dir_Left;
        g.pathers[p_idx++] = snake_pather_init_except_position(ways, 1);
    }
    {
        Snake_Pather_Way ways[] = {{.dir = Dir_Down, .len = 17},
                                   {.dir = Dir_Left, .len = 17},
                                   {.dir = Dir_Up, .len = 17},
                                   {.dir = Dir_Right, .len = 17}};

        tail_lengths[p_idx] = 18;
        tail_dirs[p_idx] = Dir_Left;
        g.pathers[p_idx++] = snake_pather_init_except_position(ways, 4);
    }
    {
        Snake_Pather_Way ways[] = {{.dir = Dir_Right, .len = 4},
                                   {.dir = Dir_Down, .len = 13},
                                   {.dir = Dir_Left, .len = 4},
                                   {.dir = Dir_Up, .len = 13}};

        tail_lengths[p_idx] = 6;
        tail_dirs[p_idx] = Dir_Down;
        g.pathers[p_idx++] = snake_pather_init_except_position(ways, 4);
    }
    {
        Snake_Pather_Way ways[] = {{.dir = Dir_Right, .len = 2},
                                   {.dir = Dir_Down, .len = 5},
                                   {.dir = Dir_Left, .len = 2},
                                   {.dir = Dir_Up, .len = 5}};

        tail_lengths[p_idx] = 3;
        tail_dirs[p_idx] = Dir_Down;
        g.pathers[p_idx++] = snake_pather_init_except_position(ways, 4);
    }
    {
        Snake_Pather_Way ways[] = {{.dir = Dir_Right, .len = 2},
                                   {.dir = Dir_Down, .len = 4},
                                   {.dir = Dir_Left, .len = 2},
                                   {.dir = Dir_Up, .len = 4}};

        tail_lengths[p_idx] = 3;
        tail_dirs[p_idx] = Dir_Down;
        g.pathers[p_idx++] = snake_pather_init_except_position(ways, 4);
    }
    {
        Snake_Pather_Way ways[] = {{.dir = Dir_Right, .len = 6},
                                   {.dir = Dir_Down, .len = 6},
                                   {.dir = Dir_Left, .len = 6},
                                   {.dir = Dir_Up, .len = 6}};

        tail_lengths[p_idx] = 10;
        tail_dirs[p_idx] = Dir_Left;
        g.pathers[p_idx++] = snake_pather_init_except_position(ways, 4);
    }

    maze0_init_from_string(map, GAME_STATE_OPENWORLD_WIDTH, GAME_STATE_OPENWORLD_HEIGHT, g.foods, (Maze0_Cell *)g.maze,
                           g.pathers, tail_lengths, tail_dirs, NULL, &g.w);

    *new_g = g;
}
// normal snake
Level_Return game_state_frame_OpenWorld(Game_State_OpenWorld *g)
{
    World_State0 *w = &g->w;
    // logic
    player_set_direction_from_input(g->player);

    if (time_move_logic(&g->time_for_move))
    {
        if (maze0_player_move((Maze0_Cell *)g->maze, GAME_STATE_OPENWORLD_WIDTH, g->player, w))
        {
            // player died
            return Level_Return_Reset_Level;
        }
        for (Int i = 0; i < GAME_STATE_OPENWORLD_PATHERS; ++i)
        {
            snake_pather_move(&g->pathers[i], w);
        }
        for (Int i = 0; i < GAME_STATE_OPENWORLD_PATHERS; ++i)
        {
            if (snake_pather_player_intersection(&g->pathers[i], g->player))
            {
                return Level_Return_Reset_Level;
            }
        }
        for (Int i = 0; i < GAME_STATE_OPENWORLD_FOODS; ++i)
        {
            food_player_collision_logic_food_disappear(g->player, &g->foods[i], w);
        }
    }

    Int food_left_to_win = (GAME_STATE_OPENWORLD_FOODS + 2) - g->player->length;

    if (food_left_to_win <= 0)
        return Level_Return_Next_Level;

    // drawing
    BeginDrawing();
    {
        Pos p_pos = player_nth_position(g->player, 0);
        const float max_x = (float)w->block_pixel_len * (float)w->width - (float)WINDOW_WIDTH;
        const float max_y = (float)w->block_pixel_len * (float)w->height - (float)WINDOW_HEIGHT;
        float cam_x = fminf(max_x, fmaxf(0.f, (float)(p_pos.x * w->block_pixel_len - WINDOW_WIDTH / 2)));
        float cam_y = fminf(max_y, fmaxf(0.f, (float)(p_pos.y * w->block_pixel_len - WINDOW_HEIGHT / 2)));

        // printf("cam_x: %f, max_x: %f\n", cam_x, max_x);
        Camera2D s = (Camera2D){
            .offset = {.x = 0.f, .y = 0.f}, .target = {.x = cam_x, .y = cam_y}, .rotation = 0.f, .zoom = 1.f};
        BeginMode2D(s);
    }

    ClearBackground(RAYWHITE);
    maze0_draw((Maze0_Cell *)g->maze, GAME_STATE_OPENWORLD_WIDTH, GAME_STATE_OPENWORLD_HEIGHT, w);
    for (Int i = 0; i < GAME_STATE_OPENWORLD_PATHERS; ++i)
    {
        snake_pather_draw(&g->pathers[i], w);
    }
    draw_food_left_in_2D_space(food_left_to_win, w->width * w->block_pixel_len, w->height * w->block_pixel_len);

    player_draw(g->player, w);
    for (Int i = 0; i < GAME_STATE_OPENWORLD_FOODS; ++i)
    {
        food_draw(&g->foods[i], w);
    }

    EndMode2D();
    draw_fps();
    EndDrawing();

    return Level_Return_Continue;
}
