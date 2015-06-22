#include <jmuduo/base/LogFile.h>
#include <jmuduo/base/Logging.h>

boost::scoped_ptr<jmuduo::LogFile> g_logFile;

void outputFunc(const char* msg, int len)
{
  g_logFile->append(msg, len);
}

void flushFunc()
{
  g_logFile->flush();
}

int main(int argc, char* argv[])
{
  char name[256];
  strncpy(name, argv[0], 256);
  g_logFile.reset(new jmuduo::LogFile(::basename(name), 200*1000));
  jmuduo::Logger::setOutput(outputFunc);
  jmuduo::Logger::setFlush(flushFunc);

  jmuduo::string line = "1234567890 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

  for (int i = 0; i < 10000; ++i)
  {
    LOG_INFO << line << i;

    usleep(1000);
  }
}
