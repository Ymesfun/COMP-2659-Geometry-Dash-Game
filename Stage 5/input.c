/*******************************************************************************
 AUTHORS: Yaccob Mesfun, Lorenzo Primiterra
 COURSE: COMP2659-002
 INSTRUCTOR: Steve Kalmar
 DATE: October 30, 2025

 FILE: input.c
 SUMMARY: Handles the logic for checking if there is key input, and if there is;
 saving it accordingly.
*******************************************************************************/

#include <osbind.h>
#include "constant.h"

/*******************************************************************************
    PURPOSE: Checks if there is any key input.
    INPUT:   - N/A
    OUTPUT:  - returns true if there is key input otherwise, returns false.
*******************************************************************************/
bool input_available(){
    if (Cconis()) { 
        return true;
    }
    return false;
}
/*******************************************************************************
    PURPOSE: reads and stores key input.
    INPUT:   - N/A
    OUTPUT:  - returns ch which is a char storing the key input -- 
    otherwise returns '\0'.
*******************************************************************************/
char input_read(){
     char ch = '\0';
    if (input_available()) { /* checks if there is any keyboard input*/
    char ch = (char) Cnecin() ; /*if there is input, record the input via Cnecin casting it as char type and saving it to char ch*/
    return ch;
    }
     return ch;
}

