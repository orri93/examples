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

#define GOS_DEFAULT_BIND_ADDRESS "0.0.0.0"
#define GOS_DEFAULT_BIND_PORT 32001
#define GOS_DEFAULT_BROADCAST_ADDRESS "127.0.0.1"
#define GOS_DEFAULT_BROADCAST_PORT 32002
#define GOS_DEFAULT_OUTGOING_DATA_ID "a"
#define GOS_DEFAULT_INCOMING_DATA_ID "b"

namespace gos {
namespace ex {
namespace udpdpoc {

static std::string binding_address = GOS_DEFAULT_BIND_ADDRESS;
static short binding_port = GOS_DEFAULT_BIND_PORT;
static std::string broadcast_address = GOS_DEFAULT_BROADCAST_ADDRESS;
static short broadcast_port = GOS_DEFAULT_BROADCAST_PORT;

static std::string outgoing_data_id = GOS_DEFAULT_OUTGOING_DATA_ID;
static std::string incoming_data_id = GOS_DEFAULT_INCOMING_DATA_ID;

static DataId outgoingdata = DataId::Undefined;
static DataId incomingdata = DataId::Undefined;

static std::wstring dataid2wstr(DataId id);

void options(boost::program_options::options_description& description) {
  auto strval = [&](std::string* strp) {
    return boost::program_options::value<std::string>(strp); };
  auto shoval = [&](short* shop) {
    return boost::program_options::value<short>(shop); };
  description.add_options()
    ("binding-address,i",
    strval(&binding_address)->default_value(GOS_DEFAULT_BIND_ADDRESS),
    "The address to bind to")
    ("binding-port,n",
    shoval(&binding_port)->default_value(GOS_DEFAULT_BIND_PORT),
    "The port to bind to")
    ("broadcast-address,r",
    strval(&broadcast_address)->default_value(GOS_DEFAULT_BROADCAST_ADDRESS),
    "The address to broadcast to")
    ("broadcast-port,o",
    shoval(&broadcast_port)->default_value(GOS_DEFAULT_BROADCAST_PORT),
    "The port to broadcast to")
    ("outgoing-data,d",
    strval(&outgoing_data_id)->default_value(GOS_DEFAULT_OUTGOING_DATA_ID),
    "The id for the outgoing data (a or b)")
    ("incoming-data,d",
    strval(&incoming_data_id)->default_value(GOS_DEFAULT_INCOMING_DATA_ID),
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

}
}
}
