#ifdef WIN32
#include <SDKDDKVer.h>
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// Windows Header Files:
#include <windows.h>
#endif

#include <DataStructures.h>

namespace gos {
namespace ex {
namespace udpdpoc {

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

}
}
}
