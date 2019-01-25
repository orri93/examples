#ifndef _GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_H_
#define _GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_H_

#include <string>

namespace gos {
namespace ex {
namespace udpdpoc {

enum class CommunicationResult {
  /* Successfull */
  Ok,
  NoMoreBuffered,
  BufferConsumed,

  /* Errors */
  IncomingIncorrectSize,
  BindEndpointUndefined,
  MemoryBindEndpoint,
  MemoryContext,
  FailConsuming,
  FailBindAddress,
  FailBindSocket,
  IncomingDataSize
};

CommunicationResult initialize();
CommunicationResult isready();
CommunicationResult createbindsocket();
CommunicationResult consume(std::string& address, int& port);

bool iscommunicationresulterror(const CommunicationResult& result);

std::string communicationresult2str(const CommunicationResult& result);
std::wstring communicationresult2wstr(const CommunicationResult& result);

}
}
}

#endif