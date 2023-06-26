#include "game_state_Seeker.h"
#include "player_related.h"
#include <stdlib.h>

void game_state_init_Seeker(Game_State_Seeker *new_g)
{
    Game_State_Seeker g;
    g.w = world_state0_init(28);
    g.player = (Player){.length = 1, .idx_pos = 0, .current_direction = Dir_Nothing, .next_direction = Dir_Right};
    g.player.positions[0] = (Pos){.x = g.w.width / 2, g.w.height / 2};
    food_init_position(&g.food, &g.player, &g.w);
    g.time_for_move = 1.0;
    g.seeker_time_for_move = 1.0;

    g.seeker =
        (Seeker_Snake){.length = 2, .direction = Dir_Left, .positions = {{.x = 26, .y = 10}, {.x = 27, .y = 10}}};
    g.moves = 0;

    *new_g = g;
}

void seeker_move(Seeker_Snake *snake, World_State0 *w)
{
    for (int i = snake->length - 1; i >= 1; --i)
    {
        snake->positions[i] = snake->positions[i - 1];
    }
    snake->positions[0] = move_inside_grid(snake->positions[0], snake->direction, w);
}

void seeker_draw(const Seeker_Snake *snake, const World_State0 *w)
{
    const Int length = snake->length;
    for (Int j = 0; j < length; ++j)
    {
        draw_block_at(snake->positions[j], (j == 0) ? SKYBLUE : BLUE, w);
    }
}

// returns true on collision
bool seeker_player_collision_logic(const Seeker_Snake *snake, const Player *player)
{
    for (int i = 0; i < player->length; ++i)
    {
        for (int j = 0; j < snake->length; ++j)
        {
            if (pos_equal(player_nth_position(player, i), snake->positions[j]))
            {
                return true;
            }
        }
    }
    return false;
}

Level_Return game_state_frame_Seeker(Game_State_Seeker *g)
{
    World_State0 *w = &g->w;
    // logic
    if (IsKeyPressed(KEY_A))
    {
        TraceLog(LOG_INFO, "%s", "also this works!");
    }

    player_set_direction_from_input(&g->player);

    bool seeker_grows = false;

    if (time_move_logic_general(&g->seeker_time_for_move, 0.135894))
    {
        ++g->moves;
        seeker_grows = (g->moves % 25 == 0) && (g->seeker.length < SEEKER_MAX_LENGTH);
        if (seeker_grows)
            g->seeker.length++;

        {
            Pos p_pos = player_nth_position(&g->player, 0);
            Pos s_pos = g->seeker.positions[0];
            Dir d;
            if (abs(p_pos.x - s_pos.x) > abs(p_pos.y - s_pos.y))
            {
                d = ((p_pos.x - s_pos.x) < 0) ? Dir_Left : Dir_Right;
            }
            else
            {
                d = ((p_pos.y - s_pos.y) < 0) ? Dir_Up : Dir_Down;
            }

            Dir prev = g->seeker.direction;
            if (prev == Dir_Right && d == Dir_Left)
            {
                d = Dir_Up;
            }
            else if (prev == Dir_Left && d == Dir_Right)
            {
                d = Dir_Up;
            }
            else if (prev == Dir_Up && d == Dir_Down)
            {
                d = Dir_Left;
            }
            else if (prev == Dir_Down && d == Dir_Up)
            {
                d = Dir_Left;
            }
            g->seeker.direction = d;
        }

        seeker_move(&g->seeker, w);

        if (seeker_player_collision_logic(&g->seeker, &g->player))
        {
            return Level_Return_Reset_Level;
        }
    }

    if (time_move_logic(&g->time_for_move))
    {
        if (player_move(&g->player, w))
        {
            // player died
            TraceLog(LOG_INFO, "%s", "YOU DIED!");

            return Level_Return_Reset_Level;
        }

        food_player_collision_logic(&g->player, &g->food, w);
    }
    Int food_left_to_win = (DEV ? 8 : 8) - g->player.length;

    if (food_left_to_win <= 0)
        return Level_Return_Next_Level;

    // drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (seeker_grows)
    {
        DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, RED);
    }

    draw_food_left(food_left_to_win);

    player_draw(&g->player, w);
    seeker_draw(&g->seeker, w);
    food_draw(&g->food, w);

    draw_fps();
    EndDrawing();
    return 0;
}