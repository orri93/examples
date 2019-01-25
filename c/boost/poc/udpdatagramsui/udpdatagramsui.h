#pragma once

#include <vector>
#include <string>

#include "resource.h"

namespace gos {
namespace ex {
namespace udpdpoc {

typedef std::vector<std::string> CmdLineVector;
typedef CmdLineVector::iterator CmdLineVectorIterator;

enum class InitializeResult {
  Ok
};

enum class TimerResult {
  Ok,
  Failed
};

enum class ParseOptionResult {
  Ok,
  OpenConfigurationFileFailed,
  OpenDefaultConfigurationFileFailed
};

enum class PaintResult {
  Ok,
  FailTextMetric,
  FailTextOut,
  FailSelectFont
};

enum class TextStyle {
  General,
  Title,
  Configuration
};

ParseOptionResult ParseOptions(const LPTSTR& lpCmdLine);

PaintResult PaintWindow(HWND& hWnd, PAINTSTRUCT& ps);

PaintResult DrawText(
  const std::wstring& text,
  const int& x, int& y);

PaintResult DrawText(
  const std::wstring& text,
  const int& x, int& y,
  const TextStyle& style);

PaintResult DrawText(
  const wchar_t* text,
  const size_t& count,
  const int& x, int& y);

PaintResult DrawText(
  const wchar_t* text,
  const size_t& count,
  const int& x, int& y,
  const TextStyle& style);

void ProcessCmdLine(CmdLineVector& vector, const LPTSTR& lpCmdLine);

}
}
}