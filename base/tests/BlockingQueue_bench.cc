#include <jmuduo/base/BlockingQueue.h>
#include <jmuduo/base/CountDownLatch.h>
#include <jmuduo/base/Thread.h>
#include <jmuduo/base/Timestamp.h>

#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <map>
#include <string>
#include <stdio.h>

class Bench
{
 public:
  Bench(int numThreads)
    : latch_(numThreads),
      threads_(numThreads)
  {
    for (int i = 0; i < numThreads; ++i)
    {
      char name[32];
      snprintf(name, sizeof name, "work thread %d", i);
      threads_.push_back(new jmuduo::Thread(
            boost::bind(&Bench::threadFunc, this), jmuduo::string(name)));
    }
    for_each(threads_.begin(), threads_.end(), boost::bind(&jmuduo::Thread::start, _1));
  }

  void run(int times)
  {
    printf("waiting for count down latch\n");
    latch_.wait();
    printf("all threads started\n");
    for (int i = 0; i < times; ++i)
    {
      jmuduo::Timestamp now(jmuduo::Timestamp::now());
      queue_.put(now);
      usleep(1000);
    }
  }

  void joinAll()
  {
    for (size_t i = 0; i < threads_.size(); ++i)
    {
      queue_.put(jmuduo::Timestamp::invalid());
    }

    for_each(threads_.begin(), threads_.end(), boost::bind(&jmuduo::Thread::join, _1));
  }

 private:

  void threadFunc()
  {
    printf("tid=%d, %s started\n",
           jmuduo::CurrentThread::tid(),
           jmuduo::CurrentThread::name());

    std::map<int, int> delays;
    latch_.countDown();
    bool running = true;
    while (running)
    {
      jmuduo::Timestamp t(queue_.take());
      jmuduo::Timestamp now(jmuduo::Timestamp::now());
      if (t.valid())
      {
        int delay = static_cast<int>(timeDifference(now, t) * 1000000);
        // printf("tid=%d, latency = %d us\n",
        //        muduo::CurrentThread::tid(), delay);
        ++delays[delay];
      }
      running = t.valid();
    }

    printf("tid=%d, %s stopped\n",
           jmuduo::CurrentThread::tid(),
           jmuduo::CurrentThread::name());
    for (std::map<int, int>::iterator it = delays.begin();
        it != delays.end(); ++it)
    {
      printf("tid = %d, delay = %d, count = %d\n",
             jmuduo::CurrentThread::tid(),
             it->first, it->second);
    }
  }

  jmuduo::BlockingQueue<jmuduo::Timestamp> queue_;
  jmuduo::CountDownLatch latch_;
  boost::ptr_vector<jmuduo::Thread> threads_;
};

int main(int argc, char* argv[])
{
  int threads = argc > 1 ? atoi(argv[1]) : 1;

  Bench t(threads);
  t.run(10000);
  t.joinAll();
}
