#ifndef _GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_DATA_STRUCTURES_H_
#define _GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_DATA_STRUCTURES_H_

#include <cinttypes>
#include <string>

#define GOS_UDP_DATAGRAMS_TEXT_SIZE 64

namespace gos {
namespace ex {
namespace udpdpoc {

enum class DataId { Undefined, A, B };

struct ipconfiguration {
  std::string address;
  int port;
};

struct data_a {
  char text[GOS_UDP_DATAGRAMS_TEXT_SIZE];
  float f;
  int i;
  unsigned char b;
};

struct data_b {
  char text[GOS_UDP_DATAGRAMS_TEXT_SIZE];
  unsigned long long l;
  uint16_t ui16;
  int64_t i64;
};

size_t sizeofdata(const DataId& id);

}
}
}

#endif