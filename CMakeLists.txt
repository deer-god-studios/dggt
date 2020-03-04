cmake_minimum_required(VERSION "3.16.4")

project("dggt")

include_directories("${PROJECT_SOURCE_DIR}/src")
add_library("${PROJECT_NAME}_mem" "src/mem/dggt_mem.c++" "src/mem/dggt_mem_free_alloc.c++" "src/mem/dggt_mem_lin_alloc.c++" "src/mem/dggt_mem_null_alloc.c++" "src/mem/dggt_mem_pool_alloc.c++" "src/mem/dggt_mem_stack_alloc.c++" "src/mem/dggt_mem_store_alloc.c++" "src/mem/dggt_mem_utils_linux.c++")
add_executable("${PROJECT_NAME}" "src/test/dggt_test_linux.c++")
target_link_libraries("${PROJECT_NAME}" "${PROJECT_NAME}_mem")
