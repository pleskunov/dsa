#pragma once

/* An error callback function type */
typedef void (*error_callback_t)(const char *message);

typedef enum {
  RECOVERABLE,
  UNRECOVERABLE
} callback_type_t; 

void set_error_callback(error_callback_t callback, callback_type_t type);
void reset_error_callback(callback_type_t type);
// _Noreturn void report_error(const char *message); // C11
void report_unrecoverable_error(const char *message) __attribute__((noreturn));
void report_error(const char *message);
