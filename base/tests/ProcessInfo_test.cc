#include <jmuduo/base/ProcessInfo.h>
#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

int main()
{
  printf("pid = %d\n", jmuduo::ProcessInfo::pid());
  printf("uid = %d\n", jmuduo::ProcessInfo::uid());
  printf("euid = %d\n", jmuduo::ProcessInfo::euid());
  printf("start time = %s\n", jmuduo::ProcessInfo::startTime().toFormattedString().c_str());
  printf("hostname = %s\n", jmuduo::ProcessInfo::hostname().c_str());
  printf("opened files = %d\n", jmuduo::ProcessInfo::openedFiles());
  printf("threads = %zd\n", jmuduo::ProcessInfo::threads().size());
  printf("num threads = %d\n", jmuduo::ProcessInfo::numThreads());
  printf("status = %s\n", jmuduo::ProcessInfo::procStatus().c_str());
}
