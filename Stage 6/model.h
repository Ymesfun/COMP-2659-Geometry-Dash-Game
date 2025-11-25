#ifndef MODEL_H
#define MODEL_H

#include "constant.h"

/* eventually, we should move these all to constants.h for cleanliness, maybe not tho*/
#define FLOOR 306 /*arb floor height*/
#define const int speed 2
#define GRAVITY 2
#define JUMP_SPEED -20
#define NUM_SPIKES 20
#define NUM_BLOCKS 20
#define NUM_HANGING_SPIKES 1
#define NUM_PLATFORMS 1

typedef enum {
  COLLISION_NONE,
  SAFE_COLLISION,
  COLLISION_HAZARD,
  WIN_COLLISION
} CollisionType;

typedef struct {
  CollisionType collision;
  int x, y;
  int prev_x[2], prev_y[2];
  int width, height;
  int dx, dy;
  bool render;
  bool eventflag;
  bool respawn;
  bool movestate;
} GameObject;

typedef enum {
  STATE_IDLE,
  STATE_MOVING,
  STATE_JUMPING,
  STATE_DEAD,
  STATE_FALLING,  
} PlayerState;

typedef struct {
  GameObject entity;
  PlayerState state;
  int player_state;
  int jump_multiplier;
  bool alive;
  bool jump_pressed;
  bool on_ground;
  bool on_platform;
  bool goal;
  unsigned int deathcount;
} Player;

typedef struct{
  Player Player;
  GameObject Spikes[NUM_SPIKES];
  int Spikecount;
  GameObject Blocks[NUM_BLOCKS];
  GameObject HangingSpike[NUM_HANGING_SPIKES];
  GameObject platforms[NUM_PLATFORMS];
  int Platformcount;
  int Hangingspikecount;
  int Blockcount;  
  GameObject Goal;
}Model;

void initialize_spike_gameobj(GameObject *Object, int x, int y, int Speed);
void initialize_block_gameobj(GameObject *Object, int x, int y, int Speed);
void initialize_goal_gameobj(GameObject *Object, int x, int y, int Speed);
void initialize_player_gameobj(GameObject *Object, int x, int y, int Speed);
void initialize_player_obj(Player *PlayerObj, int x, int y, int Speed);
void initialize_hanging_spike_gameobj(GameObject *Object, int x, int y, int Speed);
void initialize_platform_gameobj(GameObject *Object, int x, int y, int Speed);

bool on_ground(Player *player);
void player_move(Player *player);
void player_death(Player *player);
void player_idle(Player *player);
bool object_collisioncheck (Player *player, GameObject *object);
void player_respawn (Player *player);
void object_idle(GameObject *object);
void portal(Player *player);
void object_respawn(GameObject *object, Player *player);
void object_move(GameObject *object);
bool within_bounds(GameObject *object);
void fall(Player *player);
void player_jump(Player *player);
void player_on_floor(Player *player, int height);
bool prev_bounded(int x, int y);
bool platform_top_collision(Player *player, GameObject *plat);
bool platform_side_collision(Player *player, GameObject *plat);
bool handle_platform_collisions(Player *player, GameObject *blocks, int count);

#endif