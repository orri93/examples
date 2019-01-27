#ifndef _GOS_EXAMPLES_C_POC_UDP_COMMUNICATION_OPTIONS_H_
#define _GOS_EXAMPLES_C_POC_UDP_COMMUNICATION_OPTIONS_H_

#include <string>

#include <boost/program_options.hpp>

#include <DataStructures.h>

#define GOS_DEFAULT_BIND_ADDRESS "0.0.0.0"
#define GOS_DEFAULT_BIND_PORT 32001
#define GOS_DEFAULT_BROADCAST_ADDRESS "127.0.0.1"
#define GOS_DEFAULT_BROADCAST_PORT 32002
#define GOS_DEFAULT_OUTGOING_DATA_ID "a"
#define GOS_DEFAULT_INCOMING_DATA_ID "b"

namespace gos {
namespace ex {
namespace udpdpoc {

void setdefaults(
  struct ipconfiguration& binding,
  struct ipconfiguration& broadcasting,
  const char* outgoingdataid,
  const char* incomingdataid);
void options(boost::program_options::options_description& description);
void parsevalues();

std::wstring bindmessage();
std::wstring broadcastmessage();
std::wstring datamessage();

void getbindinginfo(struct ipconfiguration& ipconf);
void getbroadcastinfo(struct ipconfiguration& ipconf);
DataId getoutgoingdataid();
DataId getincomingdataid();

}
}
}

#endif