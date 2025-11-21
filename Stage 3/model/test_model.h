#ifndef TEST_MODEL_H
#define TEST_MODEL_H

void test_player_initialization(Model model, int *failcount);
void test_block_initialization(Model model,int *failcount);
void test_goal_initialization(Model model, int *failcount);
void test_model_initialization();
void test_player_movement(Model model, int *failcount);
void test_player_jump(Model model, int *failcount);
void test_spike_move(Model model, int *failcount);
void test_block_move(Model model, int *failcount);
void test_goal_move(Model model, int *failcount);
void test_movement();
void test_spike_collision(Model model, int*failcount);
void test_wall_collision(Model model, int *failcount);
void test_collisions();

#endif 