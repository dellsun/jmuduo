add_executable(Buffer_unittest Buffer_unittest.cc)
target_link_libraries(Buffer_unittest jmuduo_net boost_unit_test_framework)

add_executable(InetAddress_unittest InetAddress_unittest.cc)
target_link_libraries(InetAddress_unittest jmuduo_net boost_unit_test_framework)

add_executable(EventLoop_unittest EventLoop_unittest.cc)
target_link_libraries(EventLoop_unittest jmuduo_net)

add_executable(EventLoopThreadPool_unittest EventLoopThreadPool_unittest.cc)
target_link_libraries(EventLoopThreadPool_unittest jmuduo_net)

add_executable(EchoServer_unittest EchoServer_unittest.cc)
target_link_libraries(EchoServer_unittest jmuduo_net)

add_executable(EchoClient_unittest EchoClient_unittest.cc)
target_link_libraries(EchoClient_unittest jmuduo_net)

add_executable(TimerQueue_unittest TimerQueue_unittest.cc)
target_link_libraries(TimerQueue_unittest jmuduo_net)