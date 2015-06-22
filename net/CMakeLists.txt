set(NET_LIB_SRC 
	Timer.cc
	TimerQueue.cc
	SocketsOps.cc
	Buffer.cc
	InetAddress.cc
	Socket.cc
	Boilerplate.cc
	Channel.cc
	EventLoop.cc
	EventLoopThread.cc
	EventLoopThreadPool.cc
	Poller.cc
	poller/DefaultPoller.cc
	poller/PollPoller.cc
	poller/EPollPoller.cc
	Acceptor.cc
	Connector.cc
	TcpConnection.cc
	TcpServer.cc
	TcpClient.cc)
add_library(jmuduo_net SHARED ${NET_LIB_SRC})
target_link_libraries(jmuduo_net jmuduo_base)
add_subdirectory(tests)
add_subdirectory(http)
add_subdirectory(inspect)