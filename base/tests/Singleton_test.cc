#include <jmuduo/base/Singleton.h>
#include <jmuduo/base/Thread.h>
#include <jmuduo/base/CurrentThread.h>

#include <boost/noncopyable.hpp>
#include <stdio.h>

class Test : boost::noncopyable
{
 public:
  Test()
  {
    printf("tid=%d, constructing %p\n", jmuduo::CurrentThread::tid(), this);
  }

  ~Test()
  {
    printf("tid=%d, destructing %p %s\n", jmuduo::CurrentThread::tid(), this, name_.c_str());
  }

  const jmuduo::string& name() const { return name_; }
  void setName(const jmuduo::string& n) { name_ = n; }

 private:
  jmuduo::string name_;
};

void threadFunc()
{
  printf("tid=%d, %p name=%s\n",
         jmuduo::CurrentThread::tid(),
         &jmuduo::Singleton<Test>::instance(),
         jmuduo::Singleton<Test>::instance().name().c_str());
  jmuduo::Singleton<Test>::instance().setName("only one, changed");
}

int main()
{
  jmuduo::Singleton<Test>::instance().setName("only one");
  jmuduo::Thread t1(threadFunc);
  t1.start();
  t1.join();
  printf("tid=%d, %p name=%s\n",
         jmuduo::CurrentThread::tid(),
         &jmuduo::Singleton<Test>::instance(),
         jmuduo::Singleton<Test>::instance().name().c_str());
}
