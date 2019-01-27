#ifdef WIN32
#include <SDKDDKVer.h>
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// Windows Header Files:
#include <windows.h>
#endif

#include <sstream>
#include <string>

#include <CommunicationOptions.h>
#include <DataStructures.h>
#include <Text.h>

namespace gos {
namespace ex {
namespace udpdpoc {

static struct ipconfiguration default_binding = {
  GOS_DEFAULT_BIND_ADDRESS,
  GOS_DEFAULT_BIND_PORT
};
static struct ipconfiguration default_broadcasting = {
  GOS_DEFAULT_BROADCAST_ADDRESS,
  GOS_DEFAULT_BROADCAST_PORT
};

static std::string default_outgoingdata_id = GOS_DEFAULT_OUTGOING_DATA_ID;
static std::string default_incomingdata_id = GOS_DEFAULT_INCOMING_DATA_ID;

static std::string binding_address = GOS_DEFAULT_BIND_ADDRESS;
static short binding_port = GOS_DEFAULT_BIND_PORT;
static std::string broadcast_address = GOS_DEFAULT_BROADCAST_ADDRESS;
static short broadcast_port = GOS_DEFAULT_BROADCAST_PORT;

static std::string outgoing_data_id = GOS_DEFAULT_OUTGOING_DATA_ID;
static std::string incoming_data_id = GOS_DEFAULT_INCOMING_DATA_ID;

static DataId outgoingdata = DataId::Undefined;
static DataId incomingdata = DataId::Undefined;

static std::wstring dataid2wstr(DataId id);
static void assigndefault(
  struct ipconfiguration& destination,
  const struct ipconfiguration& source);

void setdefaults(
  struct ipconfiguration& binding,
  struct ipconfiguration& broadcasting,
  const char* outgoingdataid,
  const char* incomingdataid) {
  assigndefault(default_binding, binding);
  assigndefault(default_broadcasting, broadcasting);
  default_outgoingdata_id = outgoingdataid;
  default_incomingdata_id = incomingdataid;
}

void options(boost::program_options::options_description& description) {
  binding_address = default_binding.address;
  binding_port = default_binding.port;
  broadcast_address = default_broadcasting.address;
  broadcast_port = default_broadcasting.port;
  outgoing_data_id = default_outgoingdata_id;
  incoming_data_id = default_incomingdata_id;
  auto strval = [&](std::string* strp) {
    return boost::program_options::value<std::string>(strp); };
  auto shoval = [&](short* shop) {
    return boost::program_options::value<short>(shop); };
  description.add_options()
    ("binding-address,i",
    strval(&binding_address)->default_value(default_binding.address),
    "The address to bind to")
    ("binding-port,n",
    shoval(&binding_port)->default_value(default_binding.port),
    "The port to bind to")
    ("broadcast-address,r",
    strval(&broadcast_address)->default_value(default_broadcasting.address),
    "The address to broadcast to")
    ("broadcast-port,o",
    shoval(&broadcast_port)->default_value(default_broadcasting.port),
    "The port to broadcast to")
    ("outgoing-data,d",
    strval(&outgoing_data_id)->default_value(default_outgoingdata_id),
    "The id for the outgoing data (a or b)")
    ("incoming-data,d",
    strval(&incoming_data_id)->default_value(default_incomingdata_id),
    "The id for the incoming data (a or b)");
}

void parsevalues() {
  outgoingdata = outgoing_data_id == "a" ? DataId::A : DataId::B;
  incomingdata = incoming_data_id == "a" ? DataId::A : DataId::B;
}

std::wstring bindmessage() {
  std::wstringstream wss;
  wss
    << L"Binding to " << text2wtext(binding_address)
    << L" through port " << binding_port;
  return wss.str();
}

std::wstring broadcastmessage() {
  std::wstringstream wss;
  wss
    << L"Broadcasting to " << text2wtext(broadcast_address)
    << L" through port " << broadcast_port;
  return wss.str();
}
std::wstring datamessage() {
  std::wstringstream wss;
  wss
    << L"Producing data " << dataid2wstr(outgoingdata)
    << L" and consuming data " << dataid2wstr(incomingdata);
  return wss.str();
}

void getbindinginfo(struct ipconfiguration& ipconf) {
  ipconf.address = binding_address;
  ipconf.port = binding_port;
}

void getbroadcastinfo(struct ipconfiguration& ipconf) {
  ipconf.address = broadcast_address;
  ipconf.port = broadcast_port;
}

DataId getoutgoingdataid() {
  return outgoingdata;
}

DataId getincomingdataid() {
  return incomingdata;
}

std::wstring dataid2wstr(DataId id) {
  switch (id) {
  case DataId::A:
    return L"A";
  case DataId::B:
    return L"B";
  case DataId::Undefined:
    return L"Undefined";
  default:
    return L"Unknown";
  }
}
static void assigndefault(
  struct ipconfiguration& destination,
  const struct ipconfiguration& source) {
  destination.address = source.address;
  destination.port = source.port;
}


}
}
}
