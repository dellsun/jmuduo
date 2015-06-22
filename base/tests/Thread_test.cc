#include <jmuduo/base/CurrentThread.h>
#include <jmuduo/base/Thread.h>

#include <string>
#include <boost/bind.hpp>
#include <stdio.h>

void threadFunc()
{
  printf("tid=%d\n", jmuduo::CurrentThread::tid());
}

void threadFunc2(int x)
{
  printf("tid=%d, x=%d\n", jmuduo::CurrentThread::tid(), x);
}

class Foo
{
 public:
  explicit Foo(double x)
    : x_(x)
  {
  }

  void memberFunc()
  {
    printf("tid=%d, Foo::x_=%f\n", jmuduo::CurrentThread::tid(), x_);
  }

  void memberFunc2(const std::string& text)
  {
    printf("tid=%d, Foo::x_=%f, text=%s\n", jmuduo::CurrentThread::tid(), x_, text.c_str());
  }

 private:
  double x_;
};

int main()
{
  printf("pid=%d, tid=%d\n", ::getpid(), jmuduo::CurrentThread::tid());

  jmuduo::Thread t1(threadFunc);
  t1.start();
  t1.join();

  jmuduo::Thread t2(boost::bind(threadFunc2, 42),
                   "thread for free function with argument");
  t2.start();
  t2.join();

  Foo foo(87.53);
  jmuduo::Thread t3(boost::bind(&Foo::memberFunc, &foo),
                   "thread for member function without argument");
  t3.start();
  t3.join();

  jmuduo::Thread t4(boost::bind(&Foo::memberFunc2, boost::ref(foo), std::string("Shuo Chen")));
  t4.start();
  t4.join();

  printf("number of created threads %d\n", jmuduo::Thread::numCreated());
}
