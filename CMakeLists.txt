cmake_minimum_required(VERSION 3.26)
project(cs15213)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)




############################第七节 linking##########################################
add_library(ll SHARED  link/lib/addvec.c link/lib/multvec.c)


#########调用静态库#########

add_library(vector_static STATIC IMPORTED )
set_target_properties(vector_static
        PROPERTIES IMPORTED_LOCATION
        /Users/zhanggxk/project/cs15213/link/build/libvector.a)
add_executable(link_call_static link/link_call_static.c)
target_link_libraries(link_call_static vector_static)


#########调用动态库#########

add_library(vector_shared SHARED IMPORTED )
set_target_properties(vector_shared
        PROPERTIES IMPORTED_LOCATION
        /Users/zhanggxk/project/cs15213/link/build/libvector.dylib)
add_executable(link_call_shared link/link_call_shared.c)
target_link_libraries(link_call_shared vector_shared)


#########级联调用动态库#########

add_library(linear_shared SHARED IMPORTED )
set_target_properties(linear_shared
        PROPERTIES IMPORTED_LOCATION
        /Users/zhanggxk/project/cs15213/link/build/liblinear.dylib)
add_executable(link_call_linear link/link_call_linear.c)
target_link_libraries(link_call_linear linear_shared)



add_executable(xargs linux_cli/xags.c)
add_executable(prime linux_cli/prime.c)