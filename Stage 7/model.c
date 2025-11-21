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
    Object->collision = 2;
    Object->x = x;
    Object->y = y;
    Object->dx = Speed;
    Object->dy = 0; /* non-player gameobjs really shouldnt be jumping or flying around.*/
    Object->width = 32;
    Object->height = 32;
    Object->eventflag = false;
    Object->respawn = false;
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
    Object->collision = 2;
    Object->x = x;
    Object->y = y;
    Object->dx = Speed;
    Object->dy = 0; /* non-player gameobjs really shouldnt be jumping or flying around.*/
    Object->width = 32;
    Object->height = 32;
    Object->eventflag = false;
    Object->respawn = false;
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
    Object->collision = 3;
    Object->x = x;
    Object->y = y;
    Object->dx = Speed;
    Object->dy = 0; /* non-player gameobjs really shouldnt be jumping or flying around.*/
    Object->width = 32;
    Object->height = 32;
    Object->eventflag = false;
    Object->respawn = false;
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
    Object->collision = 0;
    Object->x = x;
    Object->y = y;
    Object->dx = Speed;
    Object->dy = 0;
    Object->width = 32;
    Object->height = 32;
    Object->eventflag = false;
    Object->respawn = false;
}

void initialize_player_obj(Player *PlayerObj, int x, int y, int Speed){
    initialize_player_gameobj(&PlayerObj->entity, x, y, Speed);
    PlayerObj->player_state = STATE_IDLE;
    PlayerObj->jump_multiplier = 1;
    PlayerObj->alive = true;
    PlayerObj->jump_pressed = 0;
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
     if (player->entity.y+player->entity.height >= FLOOR){
            return true;
    }
        return false;
    }




/*******************************************************************************
    PURPOSE: Detects collision between the player and a platform-like object.
             If a collision occurs while the player is alive, the player dies.
    INPUT:   - player: pointer to the Player object
             - object: pointer to the GameObject to check collision against
    OUTPUT:  - N/A (calls player_death if collision occurs)
*******************************************************************************/
bool platform_collision(Player *player, GameObject *object){
    int px = player->entity.x;
    int py = player->entity.y;
    int pw = player->entity.width;
    int ph = player->entity.height;
    int ox = object->x;
    int oy = object->y;
    int oh = object->height;
    int ow = object->width;
    if( px < ox + ow &&        /* player’s left is left of object’s right*/
        px + pw > ox &&        /* player’s right is right of object’s left*/
        py < oy + oh &&        /* player’s top is above object’s bottom*/
        py + ph > oy && player->alive == true){
        if(py-player->entity.dy<oy+oh && py-player->entity.dy+ph>oy && player->alive == true){ /*I subtracted, make sure this math is actually right*/
            player_death(player);
            return true;
        }
    } 
    return false;
}



/*******************************************************************************
    PURPOSE: Checks if the player is standing on top of a platform object.
             This is determined by overlap in the x-axis and the player's bottom
             aligning with the object's top.
    INPUT:   - player: pointer to the Player object
             - object: pointer to the GameObject to check against
    OUTPUT:  - returns true if the player is on the platform, false otherwise
*******************************************************************************/
bool player_on_platform(Player *player, GameObject *object){
    int px = player->entity.x;
    int py = player->entity.y;
    int pw = player->entity.width;
    int ph = player->entity.height;
    int ox = object->x;
    int oy = object ->y;
    int ow = object->width;
    int platform = oy - ph;
   
    bool overlap_x = (px < ox + ow) && (px + pw > ox);
    bool on_top = (py + ph == oy);

    if (overlap_x && on_top) {
        player->on_platform = true;
        player_on_floor(player, oy - ph);   
        return true;
    }

        if (player->on_platform == false && player->jump_pressed == false){     /* if on the platform and you dont jump you need to fall*/
            if (player->entity.y <= FLOOR) {
            
            }
            return false;
        }
        player->on_platform = false;
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
player->entity.x = 100;
player->entity.y = 100;
player->alive = true;
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
player_idle(player);

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

 object -> x -= (object -> dx);
 object -> y -= (object -> dy);
}



/*******************************************************************************
    PURPOSE: Checks whether an object is within the defined gameplay boundaries.
    INPUT:   - object: pointer to the GameObject to be checked
    OUTPUT:  - returns true if the object is within bounds, false otherwise
*******************************************************************************/
bool within_bounds(GameObject *object){
if (object->x >= 0 && object->x <= 640 &&
    object->y >=0 && object->y <= 400){
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
    if(on_ground(player)&& player->jump_pressed == false){
        player->entity.dy = 0;
        player->entity.y = FLOOR;
    }else{
        player->entity.dy += GRAVITY;
        player->entity.y += player->entity.dy;
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
    if (player->jump_pressed && on_ground(player)){
        player->on_ground = false;
        player->entity.dy = JUMP_SPEED;
        player->entity.y += player->entity.dy; 
        fall(player);
    }else if (player->jump_pressed && player->on_platform){
        player->on_platform = false; 
        player->entity.dy = JUMP_SPEED;
        player->entity.y += player->entity.dy; 
        fall(player);
    }else if (player->entity.y == FLOOR) {
        player_on_floor(player, FLOOR);
    }
    player->jump_pressed = false;
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