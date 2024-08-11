// WindowsThreadPool.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "WindowsThreadPool.h"
#include "../jturbo/Task.h"
#include "../jturbo/TaskManager.h"
#include "../jturbo/StopWatch.h"

#ifndef _DEBUG
#include <tbb/tbbmalloc_proxy.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp theApp;

using namespace std;

void myPurecallHandler(void)
{
  printf("In _purecall_handler.");
  int* a = 0;
  *a = 1; // ũ���� ����. ���� ���� �ý������� ��ȸ��Ű��.
}

void Test();

int main()
{
  int nRetCode = 0;

  HMODULE hModule = ::GetModuleHandle(nullptr);

  if (hModule != nullptr)
  {
    // MFC�� �ʱ�ȭ�մϴ�. �ʱ�ȭ���� ���� ��� ������ �μ��մϴ�.
    if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
    {
      // TODO: ���� �ڵ带 �ʿ信 ���� �����մϴ�.
      wprintf(L"�ɰ��� ����: MFC�� �ʱ�ȭ���� ���߽��ϴ�.\n");
      nRetCode = 1;
    }
    else
    {
      // TODO: ���� ���α׷��� ������ ���⿡�� �ڵ��մϴ�.
      _set_purecall_handler(myPurecallHandler);
      Test();
    }
  }
  else
  {
    // TODO: ���� �ڵ带 �ʿ信 ���� �����մϴ�.
    wprintf(L"�ɰ��� ����: GetModuleHandle ����\n");
    nRetCode = 1;
  }
  getchar();
  return nRetCode;
}

using namespace jturbo;

class LongTask : public Task
{
public:
  LongTask(int taskNum)
    : m_TaskNum(taskNum)
  {
  }
  virtual ~LongTask() {}
  virtual void run() override
  {
    // 		std::cout << m_TaskNum << "LongTask run." << std::endl;
    // 		std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
private:
  int m_TaskNum;
};

class ShortTask : public Task
{
public:
  ShortTask(int taskNum)
    : m_TaskNum(taskNum)
  {
  }
  virtual ~ShortTask() {}
  virtual void run() override
  {
    // 		std::cout << m_TaskNum << "ShortTask run." << std::endl;
    // 		std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
private:
  int m_TaskNum;
};

void Test()
{
  std::unique_ptr<TaskManager> pTaskManager(std::make_unique<TaskManager>(200));
  StopWatch<> stopWatch;
  for (int i = 0; i < 100000; ++i)
  {
    std::shared_ptr<Task> pTask;
    int j = i % 2;
    if (j == 0)
      pTask = std::make_shared<LongTask>(i);
    else
      pTask = std::make_shared<ShortTask>(i);
    pTaskManager->push(pTask);
  }

  while (pTaskManager->remainSize() != 0)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  std::cout << "Elsp " << stopWatch.GetMilliseconds() << "msec" << std::endl;
}