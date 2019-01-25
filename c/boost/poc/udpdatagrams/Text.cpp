#ifdef WIN32
#include <SDKDDKVer.h>
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// Windows Header Files:
#include <windows.h>
#endif

#include <memory>
#include <string>

#include <Text.h>

namespace gos {
namespace ex {
namespace udpdpoc {

std::wstring text2wtext(const std::string& text) {
  return text2wtext(text.c_str(), text.size());
}

std::wstring text2wtext(const char* text, const size_t& size) {
  std::unique_ptr<wchar_t[]> buffer = std::make_unique<wchar_t[]>(size + 1);
  ::mbstowcs(buffer.get(), text, size + 1);
  return std::wstring(buffer.get());
}

}
}
}
