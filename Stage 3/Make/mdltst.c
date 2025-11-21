#include <osbind.h>
#include <stdio.h>
#include "mdltst.h"
#include "model.h"
#include "events.h"


/*******************************************************************************
    PURPOSE: Tests initializing a single player object
    INPUT:   - Model Model
             - int* failcount
    OUTPUT:  - N/A
*******************************************************************************/
void test_player_initialization(Model *model, int *failcount){
    initialize_player_obj(&model->Player,320,200,10);
    if(model->Player.entity.x ==  320 && model->Player.entity.y == 200 && model->Player.entity.dx == 10){
        printf("Player Object initialized successfully\n");
    }else{
        printf("Error initializing player.\n");
        (*failcount)++; /*Increment the value in the address without actually returning anything*/
    }

}
/*******************************************************************************
    PURPOSE: Helper function that tests initializing every spike object
    INPUT:   - Model Model
             - int* failcount
    OUTPUT:  - N/A
*******************************************************************************/
void test_spike_initialization(Model *model, int *failcount){
    int i;
    for(i = 0;i<model->Spikecount; i++){
        initialize_spike_gameobj(&model->Spikes[i],i*50,i*50,i);
    }
    for(i = 0;i<model->Spikecount;i++){
        if(model->Spikes[i].x == i*50 && model->Spikes[i].y == i*50 && model->Spikes[i].dx == i && model->Spikes[i].dy == 0){
            printf("Spike %d initialized successfully.\n",i);
        }else{
            printf("Error initializing spike %d.\n",i);
            (*failcount)++;
        }
    }
}
/*******************************************************************************
    PURPOSE: Helper function that tests initializing block objects
    INPUT:   - Model Model
             - int* failcount
    OUTPUT:  - N/A
*******************************************************************************/
void test_block_initialization(Model *model,int *failcount){
    int i;
    for(i = 0; i<model->Blockcount;i++){
        initialize_block_gameobj(&model->Blocks[i],i*100, i*100, i*2);
    }
    for(i = 0;i<model->Blockcount;i++){
        if(model->Blocks[i].x == (i*100) && model->Blocks[i].y == (i*100) && model->Blocks[i].dx == (i*2) && model->Blocks[i].dy == 0){
            printf("Block %d initialized successfully.\n",i);
        }else{
            printf("Error initializing block %d.\n",i);
            (*failcount)++;
        }
    }
}
/*******************************************************************************
    PURPOSE: Helper function that tests initializing a single goal object
    INPUT:   - Model Model
             - int* failcount
    OUTPUT:  - N/A
*******************************************************************************/
void test_goal_initialization(Model *model, int *failcount){
    initialize_goal_gameobj(&model->Goal, 200, 200, 0);
    if(model->Goal.x == 200 && model->Goal.y == 200 && model->Goal.dx == 0 && model->Goal.dy ==0){
        printf("Goal initialized successfully.\n");
    }else{
        printf("Error initializing goals.\n");
        (*failcount)++;
    }
}
/*******************************************************************************
    PURPOSE: Tests initializing every single object type in model
    INPUT:   - N/A
    OUTPUT:  - N/A
*******************************************************************************/
void test_model_initialization(){
    Model model;
    int failcount = 0;
    model.Spikecount = num_spikes;
    model.Blockcount = num_blocks;
    printf("Testing player positioning:\n");
    test_player_initialization(&model,&failcount);
    printf("Testing spike initialization:\n");
    test_spike_initialization(&model,&failcount);
    printf("Testing block initialization:\n");
    test_block_initialization(&model,&failcount);
    printf("Testing goal initialization\n");
    test_goal_initialization(&model,&failcount);
    if(failcount == 0){
        printf("All initialization tests passed!\n");
    }else if(failcount < 6){
        printf(" %dinitialization tests failed.\n",failcount);
    }else{
        printf("All initialization tests failed!\n");
    }
}
/*******************************************************************************
    PURPOSE: Helper function that tests moving a single player object.
    INPUT:   - Model Model
             - int* failcount
    OUTPUT:  - N/A
*******************************************************************************/
void test_player_movement(Model model, int *failcount){
    int i;
    for(i = 0;i<5;i++){
        player_move(&model.Player);
    }  /* TODO - confirm velocity is going in the right direction. I think this is wrong.*/
    if(model.Player.entity.x == 100 && model.Player.entity.y == 150 && model.Player.entity.dx == 10 && model.Player.entity.dy == 0){
        printf("Player movement works as expected!\n");
    }else{
        printf("ERROR: Player movement not working as expected!\n");
        (*failcount)++;
    }
}

/*******************************************************************************
    PURPOSE: Helper function that tests jumping with a single player object
    INPUT:   - Model Model
             - int* failcount
    OUTPUT:  - N/A
*******************************************************************************/
void test_player_jump(Model model, int *failcount){
    int i;
    model.Player.jump_pressed = true;
    for(i = 0;i<5;i++){
        player_move(&model.Player);
    }
    if(model.Player.entity.x == 100 && model.Player.entity.y == 150 && model.Player.entity.dx == 10 && model.Player.entity.dy == 0){
        printf("Player jumping works as expected!\n");
    }else{
        printf("ERROR: Player jumping not working as expected!\n");
        (*failcount)++;
    }
}
/*******************************************************************************
    PURPOSE: Helper function that tests moving the spike objects in model.
    INPUT:   - Model Model
             - int* failcount
    OUTPUT:  - N/A
*******************************************************************************/
void test_spike_move(Model model, int *failcount){
    int i;
    int j;
    for(i = 0; i<model.Spikecount; i++){
        initialize_spike_gameobj(&model.Spikes[i],100,150,10);
    }
    for(i = 0;i<5;i++){
        for(j = 0;j<model.Spikecount;j++){
            object_move(&model.Spikes[j]); /*More efficient algo that isnt O(n^2) but this is two small iterations, so why not?*/
        }
    }
    for(i = 0;i<num_spikes;i++){
        if(model.Spikes[i].x == 50 && model.Spikes[i].y == 150 && model.Spikes[i].dx == 10 && model.Spikes[i].dy == 0){
            printf("Spike %d movement working successfully.\n",i);
        }else{
            printf("Error moving spike %d.\n",i);
            (*failcount)++;
        }
    }
}
/*******************************************************************************
    PURPOSE: Helper function that tests moving block object(s).
    INPUT:   - Model Model
             - int* failcount
    OUTPUT:  - N/A
*******************************************************************************/
void test_block_move(Model model, int *failcount){
    int i;
    int j;
    for(i = 0; i<model.Blockcount; i++){
        initialize_block_gameobj(&model.Blocks[i],100,150,10);
    }
    for(i = 0; i<5; i++){
        for(j = 0; j<model.Blockcount;j++){
            object_move(&model.Blocks[j]);
        }
    }
    for(i = 0;i<model.Blockcount;i++){
        if(model.Blocks[i].x == 50 && model.Blocks[i].y == 150 && model.Blocks[i].dx == 10 && model.Blocks[i].dy == 0){
            printf("Block %d movement working successfully.\n",i);
        }else{
            printf("Error moving block %d.\n",i);
            (*failcount)++;
        }
    }
}
/*******************************************************************************
    PURPOSE: Helper function that tests moving a single goal object.
    INPUT:   - Model Model
             - int* failcount
    OUTPUT:  - N/A
*******************************************************************************/
void test_goal_move(Model model, int *failcount){
    int i;
    initialize_goal_gameobj(&model.Goal,100,150,10);
    for(i = 0;i<5;i++){
        object_move(&model.Goal);
    }
    if(model.Goal.x == 50 && model.Goal.y == 150 && model.Goal.dx == 10 && model.Goal.dy == 0){
        printf("Goal movement test working successfully.\n");
    }else{
        printf("Error detected! Issue in your movement!\n");
    }
}
/*******************************************************************************
    PURPOSE: Tests moving every single object type in model
    INPUT:   - N/A
    OUTPUT:  - N/A
*******************************************************************************/
void test_movement(){
    Model model;
    int failcount;
    model.Spikecount = num_spikes;
    model.Blockcount = num_blocks;
    initialize_player_obj(&model.Player,50,150,10); /*This uses DRY - dont wanna repeat myself for jump/move intitializations*/
    printf("Player movement test\n");
    test_player_movement(model, &failcount);
    printf("Player jump test\n");
    /*test_player_jump(model, &failcount);*/
    printf("Spike move test\n");
    test_spike_move(model, &failcount);
    printf("Block move test\n");
    test_block_move(model,&failcount);
    printf("Goal move test\n");
    test_goal_move(model,&failcount);
    if(failcount == 0){
        printf("All movement tests passed!\n");
    }else if(failcount<7){
        printf("%d movement tests failed!\n",failcount);
    }else{
        printf("All movement tests failed!\n");
    }
}

/*******************************************************************************
    PURPOSE: Helper function that tests spike collisions with the player.
    INPUT:   - Model Model
             - int* failcount
    OUTPUT:  - N/A
*******************************************************************************/
void test_spike_collision(Model model, int*failcount){
    int i;
    initialize_spike_gameobj(&model.Spikes[0],80,50,10);/*vertical collision where object is to right*/
    initialize_spike_gameobj(&model.Spikes[1],50,81,10);/*horizontal collision where object is below*/
    for(i=0;i<model.Spikecount;i++){    /*Test if direct collisions are working*/
        if(object_collisioncheck (&model.Player, &model.Spikes[i])){
            printf("Spike collision %d working correctly\n",i);
        }else{
            printf("Spike collision %d is not working!\n",i);
            (*failcount)++;
        }
    }
    model.Spikes[0].x +=3;/*Miss where object is to right*/
    model.Spikes[1].y +=3;/*Miss where object is below*/
    for(i = 0; i<model.Spikecount;i++){
        if(!object_collisioncheck(&model.Player,&model.Spikes[i])){
            printf("Object %d down/right miss collision working successfully.\n",i);
        }else{
            printf("Object %d down/right miss collision not working!\n",i);
            (*failcount)++;
        }
    }
    model.Spikes[0].x = 17; /*Miss where object is to left*/
    model.Spikes[1].y = 17; /*Miss where object is above */
    for(i = 0; i<model.Spikecount;i++){
        if(!object_collisioncheck(&model.Player,&model.Spikes[i])){
            printf("Object %d left/up miss collision working correctly.\n",i);
        }else{
            printf("Object %d up/left miss collision not working!\n",i);
            (*failcount)++;
        }
    }
}
/*******************************************************************************
    PURPOSE: Helper function that tests wall collisions with the player.
    INPUT:   - Model Model
             - int* failcount
    OUTPUT:  - N/A
*******************************************************************************/
void test_wall_collision(Model model, int *failcount){
    int i;
    for(i = 0; i<model.Blockcount;i++){
        initialize_block_gameobj(&model.Blocks[i],50,82-i,0);
    }
    if(player_on_platform(&model.Player, &model.Blocks[0])){
        printf("Player standing on platform works!\n");
    }else{
        printf("Player standing on platform not working!\n");
        (*failcount)++;
    }
    if(!player_on_platform(&model.Player, &model.Blocks[1])){
        printf("Player block collision works!\n");
    }else{
        printf("Player block collision is broken!\n");
        (*failcount)++;
    }

}
/*******************************************************************************
    PURPOSE: Tests collisions with every single object type in model
    INPUT:   - N/A
    OUTPUT:  - N/A
*******************************************************************************/
void test_collisions(){
    Model model;
    int failcount = 0;
    model.Blockcount = num_blocks;
    model.Spikecount = num_spikes;
    initialize_player_obj(&model.Player,50,50,0);
    printf("Testing spike/general obj collision\n");
    test_spike_collision(model,&failcount);
    printf("Testing wall collision\n");
    test_wall_collision(model,&failcount);
    if(failcount == 0){
        printf("All collision tests working!\n");
    }else if(failcount<8){
        printf("%d collision tests failing!\n",failcount);
    }else{
        printf("All tests failing! This is %d tests!\n",failcount);
    }
}
/*******************************************************************************
    PURPOSE: Main function that calls every other test function
    INPUT:   - N/A
    OUTPUT:  - N/A
*******************************************************************************/
int main(){
    printf("This test file is designed to test p3 functionality.\n");
    printf("First test is initialization, then movement, then collision.\n");
    printf("Press any input to continue and see model initialization results:\n");
    Cnecin();
    test_model_initialization();
    printf("Next, movement test results. Press any key to continue.\n");
    Cnecin();
    test_movement();
    printf("Lastly, a collision test.\n");
    Cnecin();
    test_collisions();
    return 0;
}