cmake_minimum_required(VERSION "3.16.4")

project("dggt")

# modules
set(DGGT_LIB ${PROJECT_NAME})
set(DGGT_MEM "${PROJECT_NAME}_mem")
set(DGGT_COLL "${PROJECT_NAME}_coll")
set(DGGT_DEBUG "${PROJECT_NAME}_debug")
set(DGGT_TEST "${DGGT_LIB}_test")

# include dir
set(DGGT_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src")

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++2a -g -DDEBUG -O0") #generalize this

include_directories("${DGGT_INCLUDE_DIRS}")
#add_library("${DGGT_MEM}" SHARED "src/mem/dggt_mem.c++" "src/mem/dggt_mem_allocator.c++" "src/mem/dggt_mem_free_alloc.c++" "src/mem/dggt_mem_lin_alloc.c++" "src/mem/dggt_mem_pool_alloc.c++" "src/mem/dggt_mem_stack_alloc.c++" "src/mem/dggt_mem_store_alloc.c++" "src/mem/dggt_mem_utils_linux.c++")
add_library("${DGGT_MEM}" SHARED "src/mem/dggt_mem.c++" "src/mem/dggt_mem_allocator.c++" "src/mem/dggt_mem_buff_alloc.c++" "src/mem/dggt_mem_lin_alloc.c++" "src/mem/dggt_mem_free_alloc.c++" "src/mem/dggt_mem_pool_alloc.c++" "src/mem/dggt_mem_stack_alloc.c++" "src/mem/dggt_mem_store_alloc.c++" "src/mem/dggt_mem_utils_linux.c++")
#add_library("${DGGT_COLL}" SHARED "src/coll/dggt_coll_hash.c++")
add_executable("${DGGT_TEST}" "src/test/dggt_test_linux.c++")
#target_link_libraries("${DGGT_MEM}" PRIVATE "${DGGT_COLL}")
target_link_libraries("${DGGT_TEST}" PRIVATE "${DGGT_MEM}")
#target_link_libraries("${DGGT_TEST}" PRIVATE "${DGGT_COLL}")
