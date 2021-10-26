// Uses Windows API serial port functions to send and receive data from a Jrk G2.
//
// NOTE: The Jrk's input mode must be "Serial / I2C / USB".
// NOTE: The Jrk's serial mode must be set to "USB dual port" if you are
//   connecting to it directly via USB.
// NODE: The Jrk's serial mode must be set to "UART" if you are connecting to
//   it via is TX and RX lines.
// NOTE: You need to change the 'const char * device' line below to
//   specify the correct serial port.

// See https://www.pololu.com/docs/0J73/15.6

#include <stdio.h>
#include <stdint.h>

#include <windows.h>

#include <serial.h>
#include <jrk.h>

int main() {
  // Choose the serial port name.  If the Jrk is connected directly via USB,
  // you can run "jrk2cmd --cmd-port" to get the right name to use here.
  // COM ports higher than COM9 need the \\.\ prefix, which is written as
  // "\\\\.\\" in C because we need to escape the backslashes.
  const char* device = "\\\\.\\COM7";

  // Choose the baud rate (bits per second).  This does not matter if you are
  // connecting to the Jrk over USB.  If you are connecting via the TX and RX
  // lines, this should match the baud rate in the Jrk's serial settings.
  uint32_t baud_rate = 9600;

  HANDLE port = open_serial_port(device, baud_rate);
  if (port == INVALID_HANDLE_VALUE) { return 1; }

  int feedback = jrk_get_feedback(port);
  if (feedback < 0) { return 1; }

  printf("Feedback is %d.\n", feedback);

  int target = jrk_get_target(port);
  if (target < 0) { return 1; }
  printf("Target is %d.\n", target);

  int new_target = (target < 2048) ? 2248 : 1848;
  printf("Setting target to %d.\n", new_target);
  int result = jrk_set_target(port, new_target);
  if (result) { return 1; }

  CloseHandle(port);
  return 0;
}
