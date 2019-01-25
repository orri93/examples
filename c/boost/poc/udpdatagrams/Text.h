#ifndef _GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_TEXT_H_
#define _GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_TEXT_H_

#include <string>

namespace gos {
namespace ex {
namespace udpdpoc {

std::wstring text2wtext(const std::string& text);
std::wstring text2wtext(const char* text, const size_t& size);

}
}
}

#endif