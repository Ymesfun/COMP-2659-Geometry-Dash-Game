#ifndef MODEL_H //Check if header is alreaday compiled
#define MODEL_H

typedef int bool;
#define true 1
#define false 0
#define min_y 150  //Currently an arbitrary number - give it an actual number


/* The idea is that our player cube has an x and y coordinate,
 and a length and width (fixed 16x16) which defines the square the player exists in.
 hriz_spd is its horizontal speed, and vcal_spd is the vertical, or jump speed.
*/
typedef struct 
{
    int x, y, hriz_spd, vcal_spd, length, width;
} Player;

/*The idea with the spike is to have an x/y coordinate, a length/width (likely fixed 16x16) 
and a collision hitbox, to allow us to have less precise hitboxes if collisions feel bad
*/
typedef struct
{
    int x, y, length, width, col_x, col_y;
    
} Spike;
/*The idea with the block is the same x/y coordinate, a length/width int (16x16) 
and a collision hitbox that only really cares about if the player collides with the x.
*/
typedef struct 
{
    int x, y, length, width, col_x;
}Block;

/* Similar idea to block/spike. Idea here is that if you touch the goal, you win
*/
typedef struct
{
    int x, y, length, width, col_x, col_y;
} Goal_Zone;






#endif //If header is already compiled, return