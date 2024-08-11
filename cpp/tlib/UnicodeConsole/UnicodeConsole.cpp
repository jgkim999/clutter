﻿#include "stdafx.h"
#include "UnicodeConsole.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp theApp;

using namespace std;

HANDLE std_out;

int main()
{
  int nRetCode = 0;

  HMODULE hModule = ::GetModuleHandle(nullptr);

  if (hModule != nullptr)
  {
    // MFC를 초기화합니다. 초기화하지 못한 경우 오류를 인쇄합니다.
    if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
    {
      // TODO: 오류 코드를 필요에 따라 수정합니다.
      wprintf(L"심각한 오류: MFC를 초기화하지 못했습니다.\n");
      nRetCode = 1;
    }
    else
    {
      // TODO: 응용 프로그램의 동작은 여기에서 코딩합니다.
      std_out = ::GetStdHandle(STD_OUTPUT_HANDLE);
      if (std_out == INVALID_HANDLE_VALUE)
        return 1;
      std::wstring test(L"유니코드, unicode, 1234, ひらがな or 平仮名.");
      WriteConsoleW(std_out, test.c_str(), static_cast<DWORD>(test.length()), NULL, NULL);
      WriteConsoleW(std_out, test.c_str(), static_cast<DWORD>(test.length()), NULL, NULL);

    }
  }
  else
  {
    // TODO: 오류 코드를 필요에 따라 수정합니다.
    wprintf(L"심각한 오류: GetModuleHandle 실패\n");
    nRetCode = 1;
  }

  return nRetCode;
}