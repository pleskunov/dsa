#include "err.h"

#include <stdio.h>
#include <stdlib.h>

/* Global variable to hold the callback function */
static error_callback_t error_callback = NULL;

_Noreturn static void fallback_unrecoverable_error_handler(const char *message) {
  fprintf(stdout, "Unrecoverable Error: %s\n", message);
  exit(EXIT_FAILURE);
}

static void fallback_error_handler(const char *message) {
  fprintf(stdout, "Error: %s\n", message);
}

void set_error_callback(error_callback_t callback) {
  error_callback = callback;
}

void reset_error_callback(void) {
  error_callback = NULL;
}

void report_unrecoverable_error(const char *message) {
  if (error_callback) {
    error_callback(message); // Call the user-defined callback (must be div!)
  } else {
    fallback_unrecoverable_error_handler(message);
  }

  /* This function should never return */
  exit(EXIT_FAILURE);
}

void report_error(const char *message) {
  if (error_callback) {
    error_callback(message);
  } else {
    fallback_error_handler(message);
  }
}
