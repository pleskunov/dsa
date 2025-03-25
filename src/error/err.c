#include <stdio.h>
#include <stdlib.h>

#include "err.h"

/* Global variables to hold the callback functions */
static error_callback_t error_callback = NULL;
static error_callback_t unrecoverable_error_callback = NULL;

/* Error handling module functions */
static void fallback_error_handler(const char *message, callback_type_t type) {
  if (type == UNRECOVERABLE) {
    fprintf(stdout, "Unrecoverable Error: %s\n", message);

    exit(EXIT_FAILURE);
  } else {
    fprintf(stdout, "Error: %s\n", message);

    return;
  }
}

void set_error_callback(error_callback_t callback, callback_type_t type) {
  switch (type) {
    case RECOVERABLE:
      error_callback = callback;
      break;
    case UNRECOVERABLE:
      unrecoverable_error_callback = callback;
      break;
    default:
      /* NO-OP */
      break;
  }
}

void reset_error_callback(callback_type_t type) {
  switch (type) {
    case RECOVERABLE:
      error_callback = NULL;
      break;
    case UNRECOVERABLE:
      unrecoverable_error_callback = NULL;
      break;
    default:
      /* NO-OP */
      break;
  }
}

void report_unrecoverable_error(const char *message) {
  if (unrecoverable_error_callback) {
    unrecoverable_error_callback(message); // Call the user-defined callback (must be div!)
  } else {
    fallback_error_handler(message, UNRECOVERABLE);
  }

  /* This function should never return */
  exit(EXIT_FAILURE);
}

void report_error(const char *message) {
  if (error_callback) {
    error_callback(message);
  } else {
    fallback_error_handler(message, RECOVERABLE);
  }
}
