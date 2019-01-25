#ifndef _GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_H_
#define _GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_H_

#include <string>

namespace gos {
namespace ex {
namespace udpdpoc {

enum class CommunicationResult {
  Ok,
  FailBindAddress,
  FailBindEndpoint,
  FailBindSocket
};

CommunicationResult initialize();
CommunicationResult createbindsocket();

}
}
}

#endif