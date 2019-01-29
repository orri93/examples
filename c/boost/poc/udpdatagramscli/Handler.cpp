#include <iostream>

#include "Handler.h"

namespace gos {
namespace ex {
namespace udpdpoc {
std::atomic_bool rununtilbreak;
std::mutex breakstringmutex;
std::wstring breakingmessage;
}
}
}

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType) {
  try {
    std::lock_guard<std::mutex> guard(gos::ex::udpdpoc::breakstringmutex);
    switch (fdwCtrlType) {
    case CTRL_C_EVENT:
      gos::ex::udpdpoc::breakingmessage =
        L"Stoping the loop for Ctrl-C event";
      return TRUE;
    case CTRL_CLOSE_EVENT:
      gos::ex::udpdpoc::breakingmessage =
        L"Stoping the loop for close event";
      return TRUE;
    case CTRL_BREAK_EVENT:
      gos::ex::udpdpoc::breakingmessage =
        L"Stoping the loop for Ctrl-Break event";
      return TRUE;
    case CTRL_LOGOFF_EVENT:
      gos::ex::udpdpoc::breakingmessage =
        L"Stoping the loop for logoff event";
      return TRUE;
    case CTRL_SHUTDOWN_EVENT:
      gos::ex::udpdpoc::breakingmessage =
        L"Stoping the loop for shutdown event";
      return TRUE;
    default:
      return FALSE;
    }
  }
  catch (std::exception ex) {
    std::cerr << "Ctrl handling failed with an exception: "
      << ex.what() << std::endl;
  }
  catch (...) {
    std::cerr << "Ctrl handling failed with an exception!" << std::endl;
  }
  return FALSE;
}
