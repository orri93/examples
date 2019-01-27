#pragma once

#include <vector>
#include <string>

#include "resource.h"

#include <UdpDatagrams.h>

namespace gos {
namespace ex {
namespace udpdpoc {

typedef std::vector<std::wstring> EventVector;
typedef EventVector::iterator EventVectorIterator;

enum class InitializeResult {
  Ok,
  FailCommunicationIntializing
};

enum class TimerResult {
  Ok,
  Failed
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

void AddEvent(const std::wstring e);

void CommunicationErrorMessageBox(
  const CommunicationResult& result,
  LPCWSTR lpCaption);

}
}
}