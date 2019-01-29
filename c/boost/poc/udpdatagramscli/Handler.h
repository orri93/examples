#ifndef _GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_CLI_HANDLER_H_
#define _GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_CLI_HANDLER_H_

#include <Windows.h>

#include <string>
#include <atomic>
#include <mutex>

namespace gos {
namespace ex {
namespace udpdpoc {
extern std::atomic_bool rununtilbreak;
extern std::mutex breakstringmutex;
extern std::wstring breakingmessage;
}
}
}

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType);

#endif