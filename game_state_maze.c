#include "game_state_maze.h"
#include "maze_stuff.h"
#include <stdio.h>
#include <stdlib.h>

void metagame_set_level_Maze(Meta_Game *mg)
{
    mg->frame_code = (Meta_Game_Frame_Code)game_state_Maze_frame;
    mg->init_code = (Meta_Game_Init_Code)game_state_Maze_init;
    mg->data = malloc(sizeof(Game_State_Maze));
}

void game_state_Maze_init(Game_State_Maze *new_g)
{
    Game_State_Maze g;
    g.w = world_state0_init(GAME_STATE_MAZE_WIDTH);
    g.player = (Player){.length = 2, .idx_pos = 1, .current_direction = Dir_Nothing, .next_direction = Dir_Right};
    g.player.positions[1] = (Pos){.x = g.w.width / 2, g.w.height / 2};
    g.player.positions[0] = (Pos){.x = g.w.width / 2 - 1, g.w.height / 2};

    Pos poses0[] = {{29, 3}, {29, 4}, {29, 5}, {29, 6}};
    Snake_Pather_Way ways0[] = {{Dir_Right, 2}, {Dir_Down, 6}, {Dir_Left, 2}, {Dir_Up, 6}};
    g.evil_snake_paths[0] = snake_pather_init(poses0, 4, ways0, 4);

    Pos poses1[] = {{12, 10}, {12, 11}, {12, 12}, {12, 13}};
    Snake_Pather_Way ways1[] = {{Dir_Right, 14}, {Dir_Down, 7}, {Dir_Left, 14}, {Dir_Up, 7}};
    g.evil_snake_paths[1] = snake_pather_init(poses1, 4, ways1, 4);

    printf("Size of Maze_Cell type: %lu\n",
           sizeof(Maze0_Cell)); // this WAS SO stupid, why are enums minimum 4 bytes??!?!?!
    printf("Size of matrix: %lu\n", sizeof(g.maze));
    // clang-format off
    const char *maze_str[] = { "----------------------------------------" ,
                               "----------------------------------------",
                               "-|||||||------------------||||||||||||--",
                               "-|-----|------------------|--S-------|--",
                               "-|-----|------------------|----------|--",
                               "-|--F--|------------------|--------F-|--",
                               "-|-----|------------------|----------|--",
                               "-|-----|------------------|----------|--",
                               "-|||--||----------|||||||||----------|--",
                               "---|--|----||||||||------------------|--",
                               "---|--|----|S---------------||||||||||--",
                               "---|--|----|-||||||-||||||--|--------|--",
                               "---|--||||||-|-----------|-||--------|--",
                               "---|---------|-----------|-|-----F---|--",
                               "---|||||||||-|-----------|-|---------|--",
                               "-----------|-|-----------|-|---------|--",
                               "-----------|-|||||||||||||-|--||||||||--",
                               "-----------|---------------|-|-------|--",
                               "---------|||||||||||-|||||||-|--|-|--|--",
                               "--||||||-|---|||||||-|-------|--|-||-|--",
                               "--|----|-|-|-|||||||-|----|||||||-|--|--",
                               "--|-F--|-|-|-|---|||-|------------|-||--",
                               "--|----|-|-|-|-|-|||-|----||||-||||--|--",
                               "--|----|-|-|-|-|-|||-|---|---|-|---|-|--",
                               "--|----|-|-|-|-|-|||-|--||---|||-----|--",
                               "--|----|||-|-|-|-|||-|-|||---|-------|--",
                               "--|--------|---|---------------------|--",
                               "--||||||||||||||||||||||||||||||||||||--",
                               "----------------------------------------",
                               "----------------------------------------", };
	//clang-format on
    maze0_init_from_string(maze_str, GAME_STATE_MAZE_WIDTH, GAME_STATE_MAZE_HEIGHT, g.foods, (Maze0_Cell *)g.maze);
    g.time_for_move = 1.0;

    *new_g = g;
}

Level_Return game_state_Maze_frame(Game_State_Maze *g)
{
    World_State0 *w = &g->w;
    // logic

    player_set_direction_from_input(&g->player);

    if (time_move_logic_general(&g->time_for_move, 0.123))
    {
		maze0_player_move((Maze0_Cell *)g->maze, GAME_STATE_MAZE_WIDTH, &g->player, w);

        for (Int i = 0; i < GAME_STATE_MAZE_TOTAL_EVIL_SNAKE_PATHS; ++i)
            snake_pather_move(&g->evil_snake_paths[i], w);

        for (Int i = 0; i < GAME_STATE_MAZE_TOTAL_EVIL_SNAKE_PATHS; ++i)
        {
            if (snake_pather_player_intersection(&g->evil_snake_paths[i], &g->player))
            {
                return Level_Return_Reset_Level;
            }
        }

        for (Int i = 0; i < GAME_STATE_MAZE_FOODS; ++i)
        {
            food_player_collision_logic_food_disappear(&g->player, &g->foods[i]);
        }
    }

    Int food_left_to_win = (DEV ? 6 : 6) - g->player.length;

    if (food_left_to_win <= 0)
        return Level_Return_Next_Level;

    // drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);

    draw_food_left(food_left_to_win);
    maze0_draw((Maze0_Cell *)g->maze, GAME_STATE_MAZE_WIDTH, GAME_STATE_MAZE_HEIGHT, w);
    player_draw_extra(&g->player, w);
    for (Int i = 0; i < GAME_STATE_MAZE_FOODS; ++i)
    {
        food_draw(&g->foods[i], w);
    }
    for (Int i = 0; i < GAME_STATE_MAZE_TOTAL_EVIL_SNAKE_PATHS; ++i)
    {
        snake_pather_draw(&g->evil_snake_paths[i], w);
    }

    draw_fps();
    EndDrawing();
    return Level_Return_Continue;
}
