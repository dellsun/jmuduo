#include <jmuduo/net/inspect/Inspector.h>
#include <jmuduo/net/EventLoop.h>
#include <jmuduo/net/EventLoopThread.h>

using namespace jmuduo;
using namespace jmuduo::net;

int main()
{
  EventLoop loop;
  EventLoopThread t;
  Inspector ins(t.startLoop(), InetAddress(12345), "test");
  loop.loop();
}