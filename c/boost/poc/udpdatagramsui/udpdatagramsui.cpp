// udpdatagramsui.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "udpdatagramsui.h"

#include <algorithm>
#include <vector>
#include <string>

#include <shellapi.h>

#include <GeneralOptions.h>
#include <Text.h>

#define MAX_LOADSTRING 100

#define GOS_MAXIMUM_EVENTS  20
#define GOS_TIMER_INTERVAL 500
#define GOSWCC(x) sizeof(x) / sizeof(wchar_t) 

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

namespace gos {
namespace ex {
namespace udpdpoc {

static UINT_PTR timerid = 0;

static InitializeResult initresult;
static ParseOptionResult optionparseresult;
static CommunicationResult comminitresult;
static PaintResult paintresult;

static HBRUSH backgrbrush;
static COLORREF backgrcol;
static COLORREF textcol;

static HWND* hwp = nullptr;
static PAINTSTRUCT* psp = nullptr;

static int linespace = 10;

static EventVector events;

InitializeResult Initialize(const LPTSTR& lpCmdLine) {
  optionparseresult = parseoptions((const char*)lpCmdLine);

  comminitresult = initialize();
  if (comminitresult != CommunicationResult::Ok) {
    CommunicationErrorMessageBox(
      comminitresult,
      L"Communication initialization error");
    return InitializeResult::FailCommunicationIntializing;
  }

  backgrcol = RGB(0x1e, 0x1e, 0x1e);
  backgrbrush = CreateSolidBrush(backgrcol);

  textcol = RGB(0xf1, 0xf1, 0xf1);

  return InitializeResult::Ok;
}

/* See https://docs.microsoft.com/en-us/windows/desktop/winmsg/using-timers */
void TimerProcessor(
  HWND hWnd,
  UINT message,
  UINT_PTR idTimer,
  DWORD dwTime
  ) {
  CommunicationResult result = CommunicationResult::Ok;

  std::wstringstream wstrstr;
  wstrstr << clocktext();

  try {
    std::string senderaddress;
    int senderport;

    result = isready();
    if (result != CommunicationResult::Ok) {
      goto gos_ex_udpdpoc_timer_process_outputing_result_;
    }

    result = createbindsocket();
    if (result != CommunicationResult::Ok) {
      goto gos_ex_udpdpoc_timer_process_outputing_result_;
    }

    int firstcount = 0, secondcount = 0;
    while ((result = consume(senderaddress, senderport)) ==
      CommunicationResult::BufferConsumed) {
      firstcount++;
    }
    if (iscommunicationresulterror(result)) {
      goto gos_ex_udpdpoc_timer_process_outputing_result_;
    }
  }
  catch (std::exception ex) {
    wstrstr << " - exception: " << ex.what();
    goto gos_ex_udpdpoc_timer_process_adding_event_;
  }
  catch (...) {
    wstrstr << " - exception!!!";
    goto gos_ex_udpdpoc_timer_process_adding_event_;
  }

gos_ex_udpdpoc_timer_process_outputing_result_:
  wstrstr << " - " << communicationresult2wstr(result);

gos_ex_udpdpoc_timer_process_adding_event_:
  AddEvent(wstrstr.str());
  if (hWnd) {
    ::InvalidateRect(hWnd, NULL, TRUE);
  }
}

TimerResult CreateTimer(HWND& hWnd) {
  UINT_PTR timerresult = ::SetTimer(
    hWnd,
    timerid,
    GOS_TIMER_INTERVAL,
    (TIMERPROC)TimerProcessor);
  return TimerResult::Ok;
}

void DestroyTimer(HWND& hWnd, UINT_PTR timer) {
  ::KillTimer(hWnd, timer);
}

PaintResult PaintWindow(HWND& hWnd, PAINTSTRUCT& ps) {
  /* For helper functions */
  hwp = &hWnd;
  psp = &ps;

  const wchar_t WelcomeMessage[] = L"Welcome to the UDP Datagram UI";

  const int x = 10;
  const int configx = 60;
  const int spacetoevents = 10;

  int y = 10;

  std::wstring wmsg;
  
  RECT rect;

  ::GetClientRect(hWnd, &rect);
  ::SetTextColor(ps.hdc, textcol);
  ::SetBkMode(ps.hdc, TRANSPARENT);

  DrawText(WelcomeMessage, GOSWCC(WelcomeMessage), x, y, TextStyle::Title);

  if (displayoptionresult(optionparseresult)) {
    wmsg = optionresult2wstr(optionparseresult);
    DrawText(wmsg, x, y);
  }

  wmsg = bindmessage();
  DrawText(wmsg, configx, y, TextStyle::Configuration);
  wmsg = broadcastmessage();
  DrawText(wmsg, configx, y, TextStyle::Configuration);
  wmsg = datamessage();
  DrawText(wmsg, configx, y, TextStyle::Configuration);

  y += spacetoevents;

  for (EventVectorIterator i = events.begin(); i != events.end(); i++) {
    DrawText(*i, x, y);
  }

  return PaintResult::Ok;
}

PaintResult DrawText(
  const std::wstring& text,
  const int& x, int& y) {
  return DrawText(text.c_str(), text.size(), x, y, TextStyle::General);
}

PaintResult DrawText(
  const std::wstring& text,
  const int& x, int& y,
  const TextStyle& style) {
  return DrawText(text.c_str(), text.size(), x, y, style);
}

PaintResult DrawText(
  const wchar_t* text,
  const size_t& count,
  const int& x, int& y) {
  return DrawText(text, count, x, y, TextStyle::General);
}

PaintResult DrawText(
  const wchar_t* text,
  const size_t& count,
  const int& x, int& y,
  const TextStyle& style) {
  if (count > 0) {
    int innerlinespace = linespace;
    HFONT backupfont = 0, selected = 0;
    switch (style) {
    case TextStyle::Title:
      selected = (HFONT)::GetStockObject(DEVICE_DEFAULT_FONT);
      innerlinespace += 10;
      break;
    case TextStyle::Configuration:
      selected = (HFONT)::GetStockObject(ANSI_FIXED_FONT);
      break;
    default:
      innerlinespace += 2;
      break;
    }
    if (selected != 0) {
      backupfont = (HFONT)::SelectObject(psp->hdc, selected);
      if (backupfont == 0) {
        return PaintResult::FailSelectFont;
      }
    }
    TEXTMETRICW metric;
    if (!::GetTextMetricsW(psp->hdc, &metric)) {
      return PaintResult::FailTextMetric;
    }
    if (!::TextOutW(psp->hdc, x, y, text, count)) {
      return PaintResult::FailTextOut;
    }
    if (backupfont) {
      ::SelectObject(psp->hdc, backupfont);
    }
    y += metric.tmHeight + innerlinespace;
  }
  return PaintResult::Ok;
}

void AddEvent(const std::wstring e) {
  if (events.size() >= GOS_MAXIMUM_EVENTS) {
    events.erase(events.begin());
  }
  events.push_back(e);
}

void CommunicationErrorMessageBox(
  const CommunicationResult& result,
  LPCWSTR lpCaption) {
  std::wstring text = communicationresult2wstr(result);
  ::MessageBoxW(
    NULL,                     /* The window is not yet available */
    (LPCWSTR)(text.c_str()),  /* The error message */
    lpCaption,                /* The caption */
    MB_OK | MB_ICONERROR);    /* Only ok button and show error */
}

}
}
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

  gos::ex::udpdpoc::initresult =
    gos::ex::udpdpoc::Initialize(lpCmdLine);
  if (gos::ex::udpdpoc::initresult != gos::ex::udpdpoc::InitializeResult::Ok) {
    return FALSE;
  }

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_UDPDATAGRAMSUI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_UDPDATAGRAMSUI));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_UDPDATAGRAMSUI));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
  wcex.hbrBackground = gos::ex::udpdpoc::backgrbrush;
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_UDPDATAGRAMSUI);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   gos::ex::udpdpoc::TimerResult result = gos::ex::udpdpoc::CreateTimer(hWnd);
   if (result != gos::ex::udpdpoc::TimerResult::Ok) {
     return FALSE;
   }

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// Paint the window
    gos::ex::udpdpoc::paintresult = gos::ex::udpdpoc::PaintWindow(hWnd, ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
    if (gos::ex::udpdpoc::timerid) {
      gos::ex::udpdpoc::DestroyTimer(hWnd, gos::ex::udpdpoc::timerid);
      gos::ex::udpdpoc::timerid = 0;
    }
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
