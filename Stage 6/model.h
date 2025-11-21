#ifndef MODEL_H
#define MODEL_H

#include "constant.h"

/* eventually, we should move these all to constants.h for cleanliness, maybe not tho*/
#define FLOOR 306 /*arb floor height*/
#define const int speed 2
#define GRAVITY 2
#define JUMP_SPEED -20
#define num_spikes 2
#define num_blocks 2
#define num_hanging_spikes 1
#define num_platforms 1

typedef enum {
  COLLISION_NONE,
  SAFE_COLLISION,
  COLLISION_HAZARD,
  WIN_COLLISION
} CollisionType;

typedef struct {
  CollisionType collision;
  int x, y;
  int width, height;
  int dx, dy;
  bool eventflag;
  bool respawn;
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
unsigned int deathcount;
} Player;

typedef struct{
  Player Player;
  GameObject Spikes[num_spikes];
  int Spikecount;
  GameObject Blocks[num_blocks];
  GameObject HangingSpike[num_hanging_spikes];
  GameObject platforms[num_platforms];
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
bool platform_collision(Player *player, GameObject *object);
void player_move(Player *player);
bool player_on_platform(Player *player, GameObject *object);
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
void player_move(Player *player);
void player_on_floor(Player *player, int height);

#endif