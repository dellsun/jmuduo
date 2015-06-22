set(INSPECT_LIB_SRC 
	ProcessInspector.cc
	Inspector.cc)
add_library(jmuduo_inspect SHARED ${INSPECT_LIB_SRC})
target_link_libraries(jmuduo_inspect jmuduo_base)
add_subdirectory(tests)