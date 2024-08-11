#pragma once

#include <future>
#include <mutex>
#include <queue>

class ITask;
class IResultContext;
/// <summary>
/// https://modoocode.com/285
/// </summary>
class ThreadPool
{
public:
  /// <summary>
  /// ThreadPool ������.
  /// </summary>
  /// <param name="num_threads">�۾� thread ����</param>
  ThreadPool(size_t num_threads);
  ~ThreadPool();
  void WorkerThread();
  /// <summary>
  /// �۾��� ����Ѵ�.
  /// </summary>
  /// <param name="task">����� �۾�</param>
  /// <returns>�۾� ����� ���� future</returns>
  std::future<std::shared_ptr<IResultContext>> EnqueueJob(std::shared_ptr<ITask> task);
private:
  /// <summary>
  /// ������ work thread ����.
  /// </summary>
  size_t num_threads_;
  bool stop_all_;
  std::vector<std::thread> worker_threads_;
  std::queue<std::shared_ptr<ITask>> jobs_;
  std::condition_variable job_cv_;
  std::mutex job_mutex_;
};