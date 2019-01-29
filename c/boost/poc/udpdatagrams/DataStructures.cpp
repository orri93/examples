#ifdef WIN32
#include <SDKDDKVer.h>
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// Windows Header Files:
#include <windows.h>
#endif

#include <string>
#include <sstream>
#include <cassert>

#include <DataStructures.h>

namespace gos {
namespace ex {
namespace udpdpoc {

#ifdef WIN32
#pragma pack(push, 1)
#endif
struct data_a {
  char text[GOS_UDP_DATAGRAMS_TEXT_SIZE];
  float f;
  int i;
  unsigned char b;
#ifdef WIN32
};
#pragma pack(pop)
#else
} __attribute__((packed));
#endif

#ifdef WIN32
#pragma pack(push, 1)
#endif
struct data_b {
  char text[GOS_UDP_DATAGRAMS_TEXT_SIZE];
  unsigned long long l;
  uint16_t ui16;
  int64_t i64;
#ifdef WIN32
};
#pragma pack(pop)
#else
} __attribute__((packed));
#endif

struct data_a dataa;
struct data_b datab;

static uint16_t databui16 = 11;
static int64_t databi64 = INT64_MIN;

/*
void setdataa(
  const char* text, const size_t& size,
  const float& f,
  const int& i,
  const unsigned char& b);

void setdatab(
  const char* text, const size_t& size,
  const unsigned long long& l,
  const uint16_t& ui16,
  const int64_t& i64);
  */

size_t sizeofdata(const DataId& id) {
  switch (id) {
  case DataId::A:
    return sizeof(struct data_a);
  case DataId::B:
    return sizeof(struct data_b);
  default:
    return 0;
  }
}

static void createdatatext(
  char* pointer,
  const unsigned long long& incremental,
  const DataId& id);

void createdataa(const unsigned long long& incremental) {
  createdatatext(dataa.text, incremental, DataId::A);
  if (incremental > 0) {
    dataa.f = 1.0F / ((float)incremental);
    dataa.i = 1 % incremental;
  } else {
    dataa.f = 0.0F;
    dataa.i = 0;
  }
  dataa.b = *((unsigned char*)(&incremental) +
    (sizeof(unsigned long long) - 1));
}

void createdatab(const unsigned long long& incremental) {
  createdatatext(datab.text, incremental, DataId::B);
  datab.l = incremental;
  datab.ui16 = databui16++;
  datab.i64 = databi64++;
}

void accessdata(const DataId& id, DataPointer& pointer, size_t& size) {
  size = sizeofdata(id);
  switch (id) {
  case DataId::A:
    pointer = (void*)(&dataa);
    break;
  case DataId::B:
    pointer = (void*)(&datab);
    break;
  default:
    pointer = nullptr;
  }
}

void parsedata(
  const DataId& id,
  const DataPointer& pointer,
  const size_t& size) {
  assert(size == sizeofdata(id));
  switch (id) {
  case DataId::A:
    memcpy((void*)(&dataa), pointer, size);
    break;
  case DataId::B:
    memcpy((void*)(&datab), pointer, size);
    break;
  default:
    /* Do nothing*/
    break;
  }
}

void dumpdata(std::wstringstream& wstrstr, const DataId& id) {
  switch (id) {
  case DataId::A:
    wstrstr << "text is '" << dataa.text
      << "', f is " << dataa.f
      << ", i is " << dataa.i
      << " and b is " << dataa.b;
    break;
  case DataId::B:
    wstrstr << "text is '" << datab.text
      << "', l is " << datab.l
      << ", ui16 is " << datab.ui16
      << " and i64 is " << datab.i64;
    break;
  }
}

/*
void setdataa(
  const char* text, const size_t& size,
  const float& f,
  const int& i,
  const unsigned char& b) {
  if (size <= GOS_UDP_DATAGRAMS_TEXT_SIZE) {
    memcpy(dataa.text, text, size);
  }
  dataa.f = f;
  dataa.i = i;
  dataa.b = b;
}

void setdatab(
  const char* text, const size_t& size,
  const unsigned long long& l,
  const uint16_t& ui16,
  const int64_t& i64) {
  if (size <= GOS_UDP_DATAGRAMS_TEXT_SIZE) {
    memcpy(datab.text, text, size);
  }
  datab.l = l;
  datab.ui16 = ui16;
  datab.i64 = i64;
}
*/

void createdatatext(
  char* pointer,
  const unsigned long long& incremental,
  const DataId& id) {
  char indicator = '\0';
  switch (id) {
  case DataId::A:
    indicator = 'A';
    break;
  case DataId::B:
    indicator = 'B';
    break;
  default:
    indicator = 'U';
  }
  std::stringstream stream;
  stream << "The incremental is " << incremental << " for data " << indicator;
  std::string str = stream.str();
  size_t size = str.size();
  if (size < GOS_UDP_DATAGRAMS_TEXT_SIZE - 1) {
    memcpy(pointer, str.c_str(), size + 1);
  }
  else {
    memcpy(pointer, str.c_str(), GOS_UDP_DATAGRAMS_TEXT_SIZE - 1);
    dataa.text[GOS_UDP_DATAGRAMS_TEXT_SIZE - 1] = '\0';
  }
}

void cloneipinformation(
  IpInformation& destination,
  const IpInformation& source) {
  destination.address = source.address;
  destination.port = source.port;
}

}
}
}
