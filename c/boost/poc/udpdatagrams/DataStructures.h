#ifndef _GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_DATA_STRUCTURES_H_
#define _GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_DATA_STRUCTURES_H_

#include <cinttypes>
#include <string>

#define GOS_UDP_DATAGRAMS_TEXT_SIZE 64

namespace gos {
namespace ex {
namespace udpdpoc {

typedef void* DataPointer;

enum class DataId { Undefined, A, B };

struct ipconfiguration {
  std::string address;
  int port;
};

typedef struct ipconfiguration IpInformation;

size_t sizeofdata(const DataId& id);

void createdataa(const unsigned long long& incremental);
void createdatab(const unsigned long long& incremental);

void accessdata(const DataId& id, DataPointer& pointer, size_t& size);
void parsedata(
  const DataId& id,
  const DataPointer& pointer,
  const size_t& size);

void dumpdata(std::wstringstream& wstrstr, const DataId& id);

void cloneipinformation(
  IpInformation& destination,
  const IpInformation& source);

}
}
}

#endif