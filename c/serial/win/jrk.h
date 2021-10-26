// Uses Windows API serial port functions to send and receive data from a
// Jrk G2.
// NOTE: The Jrk's input mode must be "Serial / I2C / USB".
// NOTE: The Jrk's serial mode must be set to "USB dual port" if you are
//   connecting to it directly via USB.
// NODE: The Jrk's serial mode must be set to "UART" if you are connecting to
//   it via is TX and RX lines.
// NOTE: You need to change the 'const char * device' line below to
//   specify the correct serial port.

#include <stdint.h>

#include <windows.h>

// Sets the target, returning 0 on success and -1 on failure.
//
// For more information about what this command does, see the "Set Target"
// command in the "Command reference" section of the Jrk G2 user's guide.
int jrk_set_target(HANDLE port, uint16_t target);

// Gets one or more variables from the Jrk (without clearing them).
// Returns 0 for success, -1 for failure.
int jrk_get_variable(HANDLE port, uint8_t offset, uint8_t* buffer, uint8_t length);

// Gets the Target variable from the jrk or returns -1 on failure.
int jrk_get_target(HANDLE port);

// Gets the Feedback variable from the jrk or returns -1 on failure.
int jrk_get_feedback(HANDLE port);
