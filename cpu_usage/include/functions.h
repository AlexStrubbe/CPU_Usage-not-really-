#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <pthread.h>  // Include pthread header for mutex types

extern pthread_mutex_t mutex;  ///< Mutex for thread synchronization
extern pthread_cond_t
    wait_cond;  ///< Condition variable for signaling between threads

/**
 * @brief Thread function to ask the user for a floating-point number.
 *
 * This function prompts the user for input and stores the number. It will
 * notify the other thread when a valid number is provided.
 *
 * @param param Pointer to any parameters needed (not used in this function).
 * @return void* Pointer to any return value (not used).
 */
void *Asker(void *param);

/**
 * @brief Thread function to calculate the arcsine of a floating-point number.
 *
 * This function waits for a valid number (between 0 and 1) from the user.
 * If the input number is valid, it calculates the arcsine and displays the
 * result on the screen. If the number is greater than 100, it terminates
 * the program.
 *
 * @param param Pointer to any parameters needed (not used in this function).
 * @return void* Pointer to any return value (not used).
 */

void *Sinner(void *param);

#endif  // FUNCTIONS_H
