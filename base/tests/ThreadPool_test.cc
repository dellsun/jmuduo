#include <jmuduo/base/ThreadPool.h>
#include <jmuduo/base/CountDownLatch.h>
#include <jmuduo/base/Thread.h>

#include <boost/bind.hpp>
#include <stdio.h>

void print()
{
  printf("tid=%d\n", jmuduo::CurrentThread::tid());
}

void printString(const std::string& str)
{
  printf("tid=%d, str=%s\n", jmuduo::CurrentThread::tid(), str.c_str());
}

int main()
{
  jmuduo::ThreadPool pool("MainThreadPool");
  pool.start(5);

  pool.run(print);
  pool.run(print);
  for (int i = 0; i < 100; ++i)
  {
    char buf[32];
    snprintf(buf, sizeof buf, "task %d", i);
    pool.run(boost::bind(printString, std::string(buf)));
  }

  jmuduo::CountDownLatch latch(1);
  pool.run(boost::bind(&jmuduo::CountDownLatch::countDown, &latch));
  latch.wait();
  pool.stop();
}