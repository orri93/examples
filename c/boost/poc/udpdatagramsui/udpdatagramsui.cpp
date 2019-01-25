// udpdatagramsui.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "udpdatagramsui.h"

#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>

#include <shellapi.h>

#include <boost/algorithm/string.hpp>

#include <CommunicationOptions.h>
#include <UdpDatagrams.h>

namespace po = boost::program_options;

#define MAX_LOADSTRING 100

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

static UINT_PTR timerid;

static InitializeResult initresult;
static ParseOptionResult optionparseresult;
static CommunicationResult comminitresult;
static PaintResult paintresult;

static std::string configuration_file_name;

static HBRUSH backgrbrush;
static COLORREF backgrcol;
static COLORREF textcol;

static HWND* hwp = nullptr;
static PAINTSTRUCT* psp = nullptr;

static int linespace = 10;

InitializeResult Initialize(const LPTSTR& lpCmdLine) {
  optionparseresult = ParseOptions(lpCmdLine);

  comminitresult = initialize();

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

}

TimerResult CreateTimer(HWND& hWnd) {
  UINT_PTR timerresult = ::SetTimer(
    hWnd,
    timerid,
    GOS_TIMER_INTERVAL,
    (TIMERPROC)TimerProcessor);
}

ParseOptionResult ParseOptions(const LPTSTR& lpCmdLine) {
  const char* DefaultConfigurationFile = "udpdatagrams.cfg";

  ParseOptionResult result = ParseOptionResult::Ok;

  CmdLineVector cmdlineargs;
  ProcessCmdLine(cmdlineargs, lpCmdLine);

  po::options_description genoptdesc("Generic options");
  genoptdesc.add_options()
    ("version,v", "print version string")
    ("help,h", "show help message")
    ("config,c", po::value<std::string>(&configuration_file_name)->
      default_value(DefaultConfigurationFile),
      "name of a file of a configuration");
  po::options_description confoptdesc("Configuration");
  gos::ex::udpdpoc::options(confoptdesc); // Creaet UDP options
  po::options_description cmdloptdesc;
  cmdloptdesc.add(genoptdesc).add(confoptdesc);
  po::options_description conffiloptdesc;
  conffiloptdesc.add(confoptdesc);
  po::variables_map varmap;
  po::command_line_parser cmdlinparser(cmdlineargs);
  po::parsed_options parseopt = cmdlinparser.options(genoptdesc)
    .style(po::command_line_style::default_style).run();
  po::store(parseopt, varmap);
  po::notify(varmap);

  std::ifstream conffilestream(configuration_file_name.c_str());
  if (conffilestream) {
    auto parsedfile = po::parse_config_file(conffilestream, conffiloptdesc);
    po::store(parsedfile, varmap);
    po::notify(varmap);
  } else {
    result = configuration_file_name == DefaultConfigurationFile ?
      ParseOptionResult::OpenDefaultConfigurationFileFailed :
      ParseOptionResult::OpenConfigurationFileFailed;
  }

  parsevalues();

  return result;
}

PaintResult PaintWindow(HWND& hWnd, PAINTSTRUCT& ps) {
  /* For helper functions */
  hwp = &hWnd;
  psp = &ps;

  const wchar_t WelcomeMessage[] = L"Welcome to the UDP Datagram UI";

  const int x = 10;
  const int configx = 60;

  int y = 10;

  std::wstringstream wstrstr;
  std::wstring wmsg;
  
  RECT rect;

  ::GetClientRect(hWnd, &rect);
  ::SetTextColor(ps.hdc, textcol);
  ::SetBkMode(ps.hdc, TRANSPARENT);

  DrawText(WelcomeMessage, GOSWCC(WelcomeMessage), x, y, TextStyle::Title);

  switch (optionparseresult) {
  case ParseOptionResult::Ok:
    wstrstr << L"Successfully processed the configuration file "
      << text2wtext(configuration_file_name);
    DrawText(wstrstr.str(), x, y);
    wstrstr.clear();
    break;
  case ParseOptionResult::OpenConfigurationFileFailed:
    wstrstr << L"Failed to open configuration file "
      << text2wtext(configuration_file_name);
    DrawText(wstrstr.str(), x, y);
    wstrstr.clear();
    break;
  }

  wmsg = bindmessage();
  DrawText(wmsg, configx, y, TextStyle::Configuration);
  wmsg = broadcastmessage();
  DrawText(wmsg, configx, y, TextStyle::Configuration);
  wmsg = datamessage();
  DrawText(wmsg, configx, y, TextStyle::Configuration);

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

void ProcessCmdLine(CmdLineVector& vector, const LPTSTR& lpCmdLine) {
  std::string trimed, cmdlinestr = std::string((const char*)lpCmdLine);
  if (cmdlinestr.size() > 0) {
    CmdLineVector temporaryvector;
    boost::split(temporaryvector, cmdlinestr, [](char c){
      return c == ' ' || c == '\t'; });
    CmdLineVectorIterator i, e = temporaryvector.end();
    for (i = temporaryvector.begin(); i != e; i++) {
      trimed = ::boost::algorithm::trim_copy(*i);
      if (trimed.size() > 0) {
        vector.push_back(trimed);
      }
    }
  }
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
