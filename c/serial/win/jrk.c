#include <stdio.h>

#include <serial.h>
#include <jrk.h>

int jrk_set_target(HANDLE port, uint16_t target) {
  if (target > 4095) { target = 4095; }
  uint8_t command[2];
  command[0] = 0xC0 + (target & 0x1F);
  command[1] = (target >> 5) & 0x7F;
  return write_port(port, command, sizeof(command));
}

int jrk_get_variable(HANDLE port, uint8_t offset, uint8_t* buffer, uint8_t length) {
  uint8_t command[] = { 0xE5, offset, length };
  int result = write_port(port, command, sizeof(command));
  if (result) { return -1; }
  SSIZE_T received = read_port(port, buffer, length);
  if (received < 0) { return -1; }
  if (received != length) {
    fprintf(stderr, "read timeout: expected %u bytes, got %lld\n",
      length, (int64_t)received);
    return -1;
  }
  return 0;
}

int jrk_get_target(HANDLE port) {
  uint8_t buffer[2];
  int result = jrk_get_variable(port, 0x02, buffer, sizeof(buffer));
  if (result) { return -1; }
  return buffer[0] + 256 * buffer[1];
}

int jrk_get_feedback(HANDLE port) {
  // 0x04 is the offset of the feedback variable in the "Variable reference"
  // section of the Jrk user's guide.  The variable is two bytes long.
  uint8_t buffer[2];
  int result = jrk_get_variable(port, 0x04, buffer, sizeof(buffer));
  if (result) { return -1; }
  return buffer[0] + 256 * buffer[1];
}
