#include <curses.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>

#include "functions.h"

/**
 * @brief Main function to start the threads for user input and arcsine
 * calculation.
 *
 * This function initializes two threads: one for asking the user for a
 * floating-point number (the Asker thread) and another for calculating
 * the arcsine of the number (the Sinner thread). The main function waits
 * for both threads to complete before cleaning up and exiting.
 *
 * @return int Returns 0 upon successful completion.
 */
int main() {
  pthread_t asker,
      sinner;          ///< Thread identifiers for the asker and sinner threads
  float *decimal = 0;  ///< Pointer to store the user's input number

  // Create threads for user input and arcsine calculation
  pthread_create(&asker, NULL, Asker, (void *)&decimal);
  pthread_create(&sinner, NULL, Sinner, (void *)&decimal);

  // Wait for both threads to complete
  pthread_join(asker, NULL);
  pthread_join(sinner, NULL);

  // Clean up mutex and condition variable resources
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&wait_cond);

  return 0;  // Indicate successful completion
}
