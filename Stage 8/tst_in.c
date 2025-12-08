/*******************************************************************************
 AUTHORS: Yaccob Mesfun, Lorenzo Primiterra
 COURSE: COMP2659-002
 INSTRUCTOR: Steve Kalmar
 DATE: October 30, 2025

 FILE: test_input.c
 SUMMARY: Tests the input.c file in various cases to make sure there is proper 
 functionality.
*******************************************************************************/
#include <stdio.h>
#include <osbind.h>
#include "input.h"

/*******************************************************************************
    PURPOSE: Main Render function that draws the screen
    INPUT:   - const Model *model, the model of the world
             - unsigned long *base, the pointer to the frame buffer
    OUTPUT:  - N/A
*******************************************************************************/

void main(){
    char key;
    printf("This test file is designed to test input functionality.\n");
    key = input_read();
    printf("%c\n",key);






}