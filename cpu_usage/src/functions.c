#include "functions.h"

#include <curses.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex =
    PTHREAD_MUTEX_INITIALIZER;  ///< Mutex for thread synchronization
pthread_cond_t wait_cond =
    PTHREAD_COND_INITIALIZER;  ///< Condition variable for signaling between
                               ///< threads
float *floater =
    0;  ///< Pointer to store the floating-point number input by the user

/**
 * @brief Thread function to ask the user for a floating-point number.
 *
 * This function continuously prompts the user to enter a number between 0
 * and 1 for which the arcsine will be calculated. If the number is
 * greater than or equal to 100, it signals the other thread to terminate
 * and exits. If the input is invalid (not between 0 and 1), it prompts
 * the user to try again.
 *
 * @param param Pointer to a float variable to store the user's input.
 * @return void* Returns NULL upon completion.
 */
void *Asker(void *param) {
  floater = (float *)param;  ///< Cast the parameter to a float pointer
  while (1) {
    pthread_mutex_lock(&mutex);  // Lock the mutex to ensure exclusive access

    printf(
        "\nPlease insert a number between 0 and 1 you want to find the arcsine "
        "for (or >= 100 to exit): \n");

    scanf("%f", floater);  // Read the user's input
    if (*floater >= 100) {
      pthread_cond_wait(&wait_cond, &mutex);  // Wait if input is to exit
      pthread_mutex_unlock(&mutex);           // Unlock the mutex before exiting
      break;                                  // Exit the loop
    } else if ((*floater > 1 || *floater < 0)) {
      printf("try again \n\n");  // Prompt user to try again
      *floater = 0;              // Reset floater
    } else {
      pthread_cond_wait(&wait_cond,
                        &mutex);  // Wait for the other thread to signal
    }
    pthread_mutex_unlock(&mutex);  // Unlock the mutex
  }
  return NULL;  // Indicate completion
}

/**
 * @brief Thread function to calculate the arcsine of a floating-point number.
 *
 * This function waits for a valid number between 0 and 1 to be provided
 * by the user. If a valid number is received, it calculates the arcsine
 * and displays the result. If the number is greater than or equal to 100,
 * it exits the loop and terminates.
 *
 * @param param Pointer to a float variable containing the user's input.
 * @return void* Returns NULL upon completion.
 */
void *Sinner(void *param) {
  floater = (float *)param;  ///< Cast the parameter to a float pointer
  while (1) {
    pthread_mutex_lock(&mutex);  // Lock the mutex to ensure exclusive access

    pthread_cond_signal(&wait_cond);  // Signal the other thread to proceed

    if (*floater >= 100) {
      pthread_mutex_unlock(&mutex);  // Unlock the mutex before exiting
      break;                         // Exit if asked to stop
    }

    printf("\nThe arcsine of %f is : %.3f \n", *floater,
           asin(*floater));  // Calculate and display arcsine

    pthread_mutex_unlock(&mutex);  // Unlock the mutex

    usleep(100000);  // Sleep for a short duration to prevent busy waiting
  }
  return NULL;  // Indicate completion
}
