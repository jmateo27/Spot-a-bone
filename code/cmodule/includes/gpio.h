#ifndef _GPIO_H_
#define _GPIO_H_

#define D4_GPIO_NUMBER 115
#define D5_GPIO_NUMBER 113
#define D6_GPIO_NUMBER 111
#define D7_GPIO_NUMBER 112
#define RS_GPIO_NUMBER 117
#define E_GPIO_NUMBER  15

// Write the provided string "in"/"out" to the given GPIO's direction
void GPIO_writeDirection(int, char*);
// Write the provided string "1"/"0" to the given GPIO's value
void GPIO_writeValue(int, char*);

#endif