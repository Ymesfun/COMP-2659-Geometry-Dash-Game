/*******************************************************************************
 AUTHORS: Yacob Mesfun, Lorenzo Primiterra
 COURSE: COMP2659-002
 INSTRUCTOR: Steve Kalmar
 DATE: October 15, 2025

 FILE: model.c
 SUMMARY: Contains the data structures and related functions for the game model.

**********************************************************************************/

#include "model.h"
#include "constant.h"

/* Small helper func for collision*/
bool aabb_overlap(GameObject *a, GameObject *b){
    return (
        a->x < b->x + b->width  &&
        a->x + a->width  > b->x &&
        a->y < b->y + b->height &&
        a->y + a->height > b->y
    );
}



/*******************************************************************************
    PURPOSE: Initializes a GameObject into being a spike.
    INPUT:   - GameObject *Object: Referring to the Object that should be initialized as a spike
             -  int x: referring to x position of the object
             -  int y: referring to y position of the object
             -  int speed: referring to speed/velocity of the object, or dx/change in x pos
    OUTPUT:  - N/A
*******************************************************************************/
void initialize_spike_gameobj(GameObject *Object, int x, int y, int Speed){
    Object->collision =2;
    /*initialize visual model here*/
    Object->x = x;
    Object->y = y;
    Object->dx = Speed;
    Object->dy = 0; /* non-player gameobjs really shouldnt be jumping or flying around.*/
    Object->width = 32;
    Object->height = 32;
    Object->eventflag = false;
    Object->respawn = false;
    if(x <= 608 && x >= 0 && y <= 368 && y>=0 ){
        Object->render = true;
    }else{
        Object->render = false;
    }
    Object->movestate = true;

}

/*******************************************************************************
    PURPOSE: Initializes a GameObject into being a hanging spike.
    INPUT:   - GameObject *Object: Referring to the Object that should be initialized as a spike
             -  int x: referring to x position of the object
             -  int y: referring to y position of the object
             -  int speed: referring to speed/velocity of the object, or dx/change in x pos
    OUTPUT:  - N/A
*******************************************************************************/

void initialize_hanging_spike_gameobj(GameObject *Object, int x, int y, int Speed){
    int i;
    Object->collision =2;
    /*initialize visual model here*/
    Object->x = x;
    Object->y = y;
    Object->dx = Speed;
    for(i = 0; i<2; i++){
        Object->prev_x[i] = 0;
        Object->prev_y[i] = 0;
    }
    Object->dy = 0; /* non-player gameobjs really shouldnt be jumping or flying around.*/
    Object->width = 32;
    Object->height = 32;
    Object->eventflag = false;
    Object->respawn = false;
    if(x <= 608 && x >= 0 && y <= 368 && y>=0 ){
        Object->render = true;
    }else{
        Object->render = false;
    }

    Object->movestate = true;


}
/*******************************************************************************
    PURPOSE: Initializes a GameObject into being a block.
    INPUT:   - GameObject *Object: Referring to the Object that should be initialized as a block
             -  int x: referring to x position of the object
             -  int y: referring to y position of the object
             -  int speed: referring to speed/velocity of the object, or dx/change in x pos
    OUTPUT:  - N/A
*******************************************************************************/
void initialize_block_gameobj(GameObject *Object, int x, int y, int Speed){
    int i;
    Object->collision = 2;
    Object->x = x;
    Object->y = y;
    for(i = 0; i<2; i++){
        Object->prev_x[i] = 0;
        Object->prev_y[i] = 0;
    }
    Object->dx = Speed;
    Object->dy = 0; /* non-player gameobjs really shouldnt be jumping or flying around.*/
    Object->width = 32;
    Object->height = 32;
    Object->eventflag = false;
    Object->respawn = false;
    if(x <= 608 && x >= 0 && y <= 368 && y>=0 ){
        Object->render = true;
    }else{
        Object->render = false;
    }
    Object->movestate = true;


}

/*******************************************************************************
    PURPOSE: Initializes a GameObject into being a platform.
    INPUT:   - GameObject *Object: Referring to the Object that should be initialized as a block
             -  int x: referring to x position of the object
             -  int y: referring to y position of the object
             -  int speed: referring to speed/velocity of the object, or dx/change in x pos
    OUTPUT:  - N/A
*******************************************************************************/
void initialize_platform_gameobj(GameObject *Object, int x, int y, int Speed){
    int i;
    Object->collision = 2;
    Object->x = x;
    Object->y = y;
    Object->dx = Speed;
    Object->dy = 0; /* non-player gameobjs really shouldnt be jumping or flying around.*/
    Object->width = 32;
    Object->height = 32;
    Object->eventflag = false;
    Object->respawn = false;
    for(i = 0; i<2; i++){
        Object->prev_x[i] = 0;
        Object->prev_y[i] = 0;
    }
    if(x <= 608 && x >= 0 && y <= 368 && y>=0 ){
        Object->render = true;
    }else{
        Object->render = false;
    }
    Object->movestate = true;


}

/*******************************************************************************
    PURPOSE: Initializes a GameObject into being a goal.
    INPUT:   - GameObject *Object: Referring to the Object that should be initialized as a goal
             -  int x: referring to x position of the object
             -  int y: referring to y position of the object
             -  int speed: referring to speed/velocity of the object, or dx/change in x pos
    OUTPUT:  - N/A
*******************************************************************************/
void initialize_goal_gameobj(GameObject *Object, int x, int y, int Speed){
    int i;
    Object->collision = 3;
    Object->x = x;
    Object->y = y;
    Object->dx = Speed;
    Object->dy = 0; /* non-player gameobjs really shouldnt be jumping or flying around.*/
    for(i = 0; i<2; i++){
        Object->prev_x[i] = 0;
        Object->prev_y[i] = 0;
    }
    Object->width = 32;
    Object->height = 32;
    Object->eventflag = false;
    Object->respawn = false;
    if(x <= 608 && x >= 0 && y <= 368 && y>=0 ){
        Object->render = true;
    }else{
        Object->render = false;
    }
    Object->movestate = true;
}

/*******************************************************************************
    PURPOSE: Initializes a GameObject into being a Player GameObj.
    INPUT:   - GameObject *Object: Referring to the Object that should be initialized as a Player GameObj
             -  int x: referring to x position of the object
             -  int y: referring to y position of the object
             -  int speed: referring to speed/velocity of the object, or dx/change in x pos
    OUTPUT:  - N/A
*******************************************************************************/
void initialize_player_gameobj(GameObject *Object, int x, int y, int Speed){
    int i;
    Object->collision = 0;
    Object->x = x;
    Object->y = y;
    Object->dx = Speed;
    Object->dy = 0;
    for(i = 0; i<2; i++){
        Object->prev_x[i] = 0;
        Object->prev_y[i] = 0;
    }
    Object->width = 32;
    Object->height = 32;
    Object->eventflag = false;
    Object->respawn = false;
    if(x <= 608 && x >= 0 && y <= 368 && y>=0 ){
        Object->render = true;
    }else{
        Object->render = false;
    }
    Object->movestate = true;
}

void initialize_player_obj(Player *PlayerObj, int x, int y, int Speed){
    initialize_player_gameobj(&PlayerObj->entity, x, y, Speed);
    PlayerObj->goal = false;
    PlayerObj->player_state = STATE_MOVING;
    PlayerObj->jump_multiplier = 1;
    PlayerObj->alive = true;
    PlayerObj->on_ground = true;
    PlayerObj->on_platform = false;
    PlayerObj->jump_pressed = false;
    PlayerObj->deathcount = 0;
}

/*******************************************************************************
    PURPOSE:Checks if the player is currently standing on the floor (ground level).
            Useful for determining when jumping, landing, or performing safe checks.
    INPUT:   - player: pointer to the Player object to be checked
    OUTPUT:  - returns true if the player is on the floor, false otherwise
*******************************************************************************/
    bool on_ground(Player *player){
        return(player->entity.y >= FLOOR);
}




/*******************************************************************************
    PURPOSE: Detects collision between the player and a platform-like object.
             If a collision occurs while the player is alive, the player dies.
    INPUT:   - player: pointer to the Player object
             - object: pointer to the GameObject to check collision against
    OUTPUT:  - N/A (calls player_death if collision occurs)
*******************************************************************************/
bool platform_side_collision(Player *player, GameObject *plat){
    if (aabb_overlap(&player->entity, plat)) {
        player_death(player);
        return true;
    }
    return false;
}
/*******************************************************************************
    PURPOSE: Detects collision between the player and a block
             If a collision occurs while the player is alive, the player dies.
    INPUT:   - player: pointer to the Player object
             - object: pointer to the GameObject to check collision against
             - count : size of the blocks array
    OUTPUT:  - N/A (calls player_death if collision occurs)
*******************************************************************************/
bool handle_platform_collisions(Player *player, GameObject *blocks, int count){
    int i;
    player->on_platform = false;

    for (i = 0; i < count; i++){
        GameObject *plat = &blocks[i];

        if (!plat->render) continue;

        if (platform_top_collision(player, plat)) {
            return true;    
        }
        if (platform_side_collision(player, plat)) {
            return true;    
        }
    }
    return false;
}
/*******************************************************************************
    PURPOSE: Detects if a player is standing on the top of a platform/block.
             Helper function to the platform/block collision function.
    INPUT:   - player: pointer to the Player object
             - plat: pointer to the GameObject to check if theyre standing on it
    OUTPUT:  - N/A (calls player_death if collision occurs)
*******************************************************************************/
bool platform_top_collision(Player *player, GameObject *plat){
    int px = player->entity.x;
    int py = player->entity.y;
    int pw = player->entity.width;
    int ph = player->entity.height;
    int ox = plat->x;
    int oy = plat->y;
    int ow = plat->width;

    int bottom = py + ph;
    int top = oy;

    bool x_overlap = (px < ox + ow) && (px + pw > ox);
    bool falling   = player->entity.dy > 0;

    bool crossing_top =
        (bottom <= top) &&
        (bottom + player->entity.dy >= top);

    if (x_overlap && falling && crossing_top){
        player->entity.y = top - ph;
        player->entity.dy = 0;
        player->on_platform = true;
        return true;
    }
    return false;
}

/*******************************************************************************
	PURPOSE: Handles player death by marking the player as not alive, incrementing
             the death counter, and setting the state to STATE_DEAD.
    INPUT:   - player: pointer to the Player object
    OUTPUT:  - N/A (updates player state and counters directly)
*******************************************************************************/
void player_death(Player *player){

    player->alive = false; 
    player->deathcount += 1;
    player->state = STATE_DEAD;

}


/*******************************************************************************
	PURPOSE: Initializes the player into an idle state at a fixed starting position.
             Sets alive = true, state = STATE_IDLE, and zeroes out velocity.
    INPUT:   - player: pointer to the Player object
    OUTPUT:  - N/A (updates player state and position directly)
*******************************************************************************/
void player_idle(Player *player){
    /* defines player start before key press (frozen)
    - could just set state = STATE_IDLE and freeze movement until input changes it.
    */
    player->state = STATE_IDLE;
    player->entity.dx = 0;
    player->entity.dy = 0;

}



/*******************************************************************************
	PURPOSE: Checks for a general collision between the player and an object
             using axis-aligned bounding box (AABB) collision detection.
    INPUT:   - player: pointer to the Player object
             - object: pointer to the GameObject to check against
    OUTPUT:  - returns true if a collision occurs, false otherwise
*******************************************************************************/
bool object_collisioncheck (Player *player, GameObject *object){
/* a function that will check whether the player rect has collided with an object rect and return a bool?*/
    int px = player->entity.x;
    int py = player->entity.y;
    int pw = player->entity.width;
    int ph = player->entity.height;

    int ox = object->x;
    int oy = object->y;
    int ow = object->width;
    int oh = object->height;

    if (px < ox + ow &&        /* player’s left is left of object’s right*/
        px + pw > ox &&        /* player’s right is right of object’s left*/
        py < oy + oh &&        /* player’s top is above object’s bottom*/
        py + ph > oy) {        /* player’s bottom is below object’s top*/
        return true;
    }

    return false;
}

/*******************************************************************************
	PURPOSE: Implements the player's jump mechanic. If jump is pressed and the
             player is on the ground, applies an upward velocity. Gravity is
             applied each frame, updating vertical position. Prevents falling
             through the floor by clamping to FLOOR level.
    INPUT:   - player: pointer to the Player object
             - jump_pressed: boolean indicating if jump input is active
    OUTPUT:  - N/A (updates player position and velocity directly)
*******************************************************************************/





/*******************************************************************************
    PURPOSE: Respawns the player at the starting state. Resets position, state,
             and flags to their initial values, ensuring the player is alive.
    INPUT:   - player: pointer to the Player object to be respawned
    OUTPUT:  - N/A (updates player state and position directly)
*******************************************************************************/
void player_respawn (Player *player){

    player->entity.x = 100;
    player->entity.y = 100;
}


/*******************************************************************************
	PURPOSE: Freezes an object in place by setting its velocity to zero.
             Useful for start, death events, or end game states.
    INPUT:   - object: pointer to the GameObject to be frozen
    OUTPUT:  - N/A (updates object velocity directly)
*******************************************************************************/
void object_idle(GameObject *object){

    object->dx = 0;
    object->dy = 0;

}



/*******************************************************************************
   PURPOSE: Triggers the end game state when the player collides with a portal.
             Stops player movement and sets state to WIN_COLLISION.
    INPUT:   - player: pointer to the Player object
    OUTPUT:  - N/A (updates player state directly)
*******************************************************************************/
void portal(Player *player){
/* a function that when collided with would trigger end game state */
    player->entity.dx = 0;
    player->entity.dy = 0;
    player->state = WIN_COLLISION;
    player->goal = true;
}




/*******************************************************************************
	PURPOSE: Respawns an object at a fixed starting position if it goes out of
             bounds while the player is still alive.
    INPUT:   - object: pointer to the GameObject to be respawned
             - player: pointer to the Player object (used to check alive state)
    OUTPUT:  - N/A (updates object position directly)
*******************************************************************************/
void object_respawn(GameObject *object, Player *player){
/* would simply reset the object to a starting position as the level would not be randomized ?*/
    if (player->alive == true && within_bounds(object) == false){
        object -> x = 640;
        object -> y = 250;
    }
}


/*******************************************************************************
	 PURPOSE: Moves an object across the screen toward the player by updating
             its position based on velocity and a constant speed factor.
             Typically used for hazards like spikes or blocks.
    INPUT:   - object: pointer to the GameObject to be moved
    OUTPUT:  - N/A (updates object position directly)
*******************************************************************************/
void object_move(GameObject *object){
    object->x -= (object->dx);
    object->y -= (object->dy);
    if(object->x <= 0){
        object->x = 0;
        object->dx = 0;
        object->render = false;
        object->movestate = false;
    }else if(object->x <= 608 && object->x >= 0){
        object->render = true;
    }
}



/*******************************************************************************
    PURPOSE: Checks whether an object is within the defined gameplay boundaries.
    INPUT:   - object: pointer to the GameObject to be checked
    OUTPUT:  - returns true if the object is within bounds, false otherwise
*******************************************************************************/
bool within_bounds(GameObject *object){
    if (object->x >= 0 && object->x <= 608 &&
        object->y >=0 && object->y <= 368){
        return true;
    }
    return false;
}

/*******************************************************************************
    PURPOSE: Applies gravity to the player and updates vertical position.
    INPUT:   - none (uses global player reference)
    OUTPUT:  - modifies player's vertical velocity and position
*******************************************************************************/
void fall(Player *player){
    player->entity.y += player->entity.dy;
    player->entity.dy += GRAVITY;

    if (player->entity.y >= FLOOR){
        player->entity.y = FLOOR;
        player->entity.dy = 0;
        player->on_ground = true;
    } else {
        player->on_ground = false;
    }
}

void player_on_floor(Player *player, int height){
    player->entity.y = height;
    player->entity.dy = 0;
    player->on_ground = true;
}

/*******************************************************************************
    PURPOSE: Handles player jump logic based on ground or platform status.
    INPUT:   - player: pointer to the Player object
             - jump_pressed: boolean indicating if jump input is active
    OUTPUT:  - updates player's vertical velocity and position
             - modifies ground/platform state flags
*******************************************************************************/
void player_jump(Player *player){
    if (player->jump_pressed){
        if (player->on_ground || player->on_platform){
            player->entity.dy = JUMP_SPEED;
            player->on_ground = false;
            player->on_platform = false;
        }
    }
}
/*******************************************************************************
    PURPOSE: Moves the player horizontally and triggers jump logic if applicable.
    INPUT:   - player: pointer to the Player object
    OUTPUT:  - updates player's horizontal position
                & triggers jump check logic 
*******************************************************************************/

void player_move(Player *player){
    player->entity.x += player->entity.dx;
    fall(player);
}

bool prev_bounded(int x, int y){ /*32+608=640, 32+368 = 400*/
    return(x <= 608 && x >= 0 && y >= 0 && y <= 368 );
}