set(BASE_LIB_SRC 
	Timestamp.cc
	Exception.cc
	Date.cc
	TimeZone.cc
	Thread.cc
	LogStream.cc
	Logging.cc
	Condition.cc
	CountDownLatch.cc
	ThreadPool.cc
	FileUtil.cc
	ProcessInfo.cc
	LogFile.cc
	AsyncLogging.cc)
add_library(jmuduo_base SHARED ${BASE_LIB_SRC})
target_link_libraries(jmuduo_base pthread)
add_subdirectory(tests)