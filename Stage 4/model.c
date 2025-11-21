/*******************************************************************************
 AUTHORS: Yaccob Mesfun, Lorenzo Primiterra
 COURSE: COMP2659-002
 INSTRUCTOR: Steve Kalmar
 DATE: October 15, 2025

 FILE: model.c
 SUMMARY: Contains the data structures and related functions for the game model.

**********************************************************************************/


#include "model.h"

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
    PlayerObj->deathcount = 0;
}

/*******************************************************************************
    PURPOSE:Checks if the player is currently standing on the floor (ground level).
            Useful for determining when jumping, landing, or performing safe checks.
    INPUT:   - player: pointer to the Player object to be checked
    OUTPUT:  - returns true if the player is on the floor, false otherwise
*******************************************************************************/
    bool on_ground(Player *player){
        if (player->entity.y == FLOOR){
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
void platform_collision(Player *player, GameObject *object){
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
        player_death(player);
        return;
    } 
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
    if(px < ox + ow &&          /* player’s left is left of object’s right*/
        px + pw > ox &&         /* player’s right is right of object’s left*/
        py + ph == oy){         /* player's bottom is same as object's top*/
            
            player->on_ground = true;
            player->entity.dy = 0;
            py + ph = oy;
            return true;
        }
        player->on_ground = false;
        return false;
    }


/*******************************************************************************
    PURPOSE: Moves the player horizontally and vertically according to its
             velocity (dx) and makes a call to player_jump to handle gravity
    INPUT:   - player: pointer to the Player object to be moved
    OUTPUT:  - N/A (updates player position directly)
*******************************************************************************/
void player_move(Player *player) {
    player->entity.x += player->entity.dx;
    player->entity.y += player->entity.dy;
    /*Prevent falling through the floor*/
    if (player->entity.y >= FLOOR) {
        player->entity.y = FLOOR;
        player->entity.dy = 0;
    }
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
void player_jump(Player *player, bool jump_pressed){
if (jump_pressed && on_ground(player) == true){
   player->entity.dy  = JUMP_SPEED;   
}
    /* Apply gravity every frame*/
    player->entity.dy += GRAVITY;
    player->entity.y += player->entity.dy;
}




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


/*player_update() incorperates all or some of the player functions needed for the player to function ie input, coolision, moving, triggering states via collision etc.
*/


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


/* object_update() incorperates all or some of the object functions needed for the object to function.*/



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
             x/y movement is handled in an intuitive sense from what velocity is,
             objects move to the left with a positive dx (subtraction) and move up
             by using a negative dy (because unintuitively, negative is upward and positive is downward in the y coordinate space.)
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