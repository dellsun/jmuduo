set(HTTP_LIB_SRC 
	HttpResponse.cc
	HttpServer.cc)
add_library(jmuduo_http SHARED ${HTTP_LIB_SRC})
target_link_libraries(jmuduo_http jmuduo_base)
add_subdirectory(tests)