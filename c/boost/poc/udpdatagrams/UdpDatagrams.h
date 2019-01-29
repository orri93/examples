#ifndef _GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_H_
#define _GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_H_

#define GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_SOCKET_LIVE_TIME_MIN 1
#define GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_SHARE_SOCKET

#include <string>
#include <sstream>

#include <DataStructures.h>

namespace gos {
namespace ex {
namespace udpdpoc {

enum class CommunicationResult {
  /* Successfull */
  Ok,
  NoMoreBuffered,
  BufferConsumed,

  /* Errors */
  IncomingZeroSize,
  IncomingIncorrectSize,
  AvailableIncorrectSize,
  BindEndpointUndefined,
  MemoryBindEndpoint,
  MemoryResolver,
  MemoryContext,
  MemorySocket,
  MemoryBuffer,
  FailOpen,
  FailBind,
  FailSend,
  FailResolve,
  FailAvailable,
  FailConsuming,
  FailBindAddress,
  FailBindSocket,
  IncomingDataSize
};

CommunicationResult initialize();
CommunicationResult initialize(const int& intervalinmillis);
CommunicationResult registerbroadcasting(const IpInformation& endpoint);
CommunicationResult loop(
  std::wstringstream& wstrstr,
  const unsigned long long& incremental);
bool istimeforloop();
bool iscommunicationresulterror(const CommunicationResult& result);
void cleanup();

std::string communicationresult2str(const CommunicationResult& result);
std::wstring communicationresult2wstr(const CommunicationResult& result);

}
}
}

#endif