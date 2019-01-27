#ifndef FDS_MC_TYPES_H_
#define FDS_MC_TYPES_H_

#define DATA_STRUCT_B   128

#define EXPECTED_SIZE_A   7
#define EXPECTED_SIZE_B 129

struct datastructa {
  float f;      /* Expected to be four bytes or 32 bit */
  uint16_t i;   /* Expected to be two bytes or 16 bit  */
  uint8_t b;    /* Expected to be one byte or 8 bit    */
};
/* Expected total size is 7 bytes */

struct datastructb {
  char text[DATA_STRUCT_B]; /* Expected to be 128 bytes */
  uint16_t l;               /* Expected to be two bytes */
};
/* Expected total size is 129 bytes */

#endif /* FDS_MC_TYPES_H_ */
