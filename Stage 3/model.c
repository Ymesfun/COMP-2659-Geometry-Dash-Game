#include "model.h"
/*
This is a simple function designed to update the players vertical and horizontal speed
if the player decides to jump, while horizontal speed is a constant velocity rate. 
It will try to keep the player in boudns if there is an issue.
*/
void move_player(Player p){
    p.x += p.hriz_spd;
    p.y += p.vcal_spd;
    if(p.vcal_spd!= 0){
        if(!in_bounds(p)){
            p.y = min_y;
        };
    }
}
/*
Purpose: Checking if the player is in bounds very quickly. May need to add more checks/use cases. 
*/
bool in_bounds(Player p)
{
    if (p.y<min_y)
    {
        return false;
    }
    return true;
    
}
/*
Purpose: This detects a wall collision and returns true or false based on if it detects a collision.
The logic of this function is simple. Check if our max x value is greater than a block, 
but our base x value is less than the block. Then check if our height is greater than the full height of the wall.
If the if statement gets a true in all 3, we have a wall collision. Otherwise return false.
*/
bool wall_collision(Player p, Block b){
    if(p.x+p.length>b.x &&p.x<b.x+b.width && && p.y<b.y){
        return true;
    }
    return false;
}
bool spike_collision(Player p, Spike s){
    if(p.x+p.length>s.x && p.x<s.x+s.width && p.y<s.y+s.length ){
        return true;
    }
    return false;
}
/*
Purpose: This detects a player goal collision and returns true or false based on if there is a collision
with the goal zone. The logic of this function checks if our x+length is greater than the goals x, which
means we're either inside or past it, but checks if our base x is less than or equal to the goal zone to
see if we arent past it. If this returns a true, game ends. If it returns a false, keep playing
*/
bool goal(Player p, Goal_Zone g){
    if(p.x+p.width>g.x && p.x<=g.x && p.y+p.length>g.y && p.y<g.y+g.col_y){
        return true;
    }
    return false;
}