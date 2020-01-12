ACLOCAL_AMFLAGS = -I m4
lib_LTLIBRARIES = libdggtmem.la
include_HEADERS = src/dggt.h \
				  src/math/dggt_math_mat2.inl \
				  src/math/dggt_math_mat3.inl \
				  src/math/dggt_math_mat4.inl \
				  src/math/dggt_math_mat.inl \
				  src/math/dggt_math_matn.inl \
				  src/math/dggt_math_vec1.inl \
				  src/math/dggt_math_vec2.inl \
				  src/math/dggt_math_vec3.inl \
				  src/math/dggt_math_vec4.inl \
				  src/math/dggt_math_vec.inl \
				  src/math/dggt_math_utils.h \
				  src/math/dggt_math_vec.h \
				  src/math/dggt_math_vec1.h \
				  src/math/dggt_math_vec2.h \
				  src/math/dggt_math_vec3.h \
				  src/math/dggt_math_vec4.h \
				  src/math/dggt_math_mat.h \
				  src/math/dggt_math_matn.h \
				  src/math/dggt_math_mat2.h \
				  src/math/dggt_math_mat3.h \
				  src/math/dggt_math_mat4.h \
				  src/math/dggt_math.h \
				  src/coll/dggt_coll_linked_list.h \
				  src/coll/dggt_coll_linked_list.inl
libdggtmem_la_SOURCES = src/mem/dggt_mem.h \
						src/mem/dggt_mem_defines.h \
						src/mem/dggt_mem.cpp \
						src/mem/dggt_mem.inl \
						src/mem/dggt_mem_mem.h \
						src/mem/dggt_mem_mem_linux.cpp \
						src/mem/dggt_mem_blk.h \
						src/mem/dggt_mem_blk.inl \
						src/mem/dggt_mem_blk.cpp \
						src/mem/dggt_mem_alloc.h \
						src/mem/dggt_mem_alloc.inl \
						src/mem/dggt_mem_linear_alloc.h \
						src/mem/dggt_mem_linear_alloc.inl \
						src/mem/dggt_mem_linear_alloc.cpp \
						src/mem/dggt_mem_stack_alloc.h \
						src/mem/dggt_mem_stack_alloc.inl \
						src/mem/dggt_mem_stack_alloc.cpp \
						src/mem/dggt_mem_pool_alloc.h \
						src/mem/dggt_mem_pool_alloc.inl \
						src/mem/dggt_mem_pool_alloc.cpp \
						src/mem/dggt_mem_free_list_alloc.h \
						src/mem/dggt_mem_free_list_alloc.inl \
						src/mem/dggt_mem_free_list_alloc.cpp \
						src/mem/dggt_mem_free_store.h
libdggtmem_la_CPPFLAGS = -O0 -g -DDEBUG
libdggtmem_la_CXXFLAGS = -std=c++17 -I$(top_srcdir)/src
check_PROGRAMS = dggt_test_linux
dggt_test_linux_SOURCES = src/test/dggt_test_linux.cpp
dggt_test_linux_CPPFLAGS = -O0 -g -DDEBUG
dggt_test_linux_CXXFLAGS = -std=c++17 -I$(top_srcdir)/src
#dggt_test_linux_LIBADD = libdggtmem.la
dggt_test_linux_LDADD = -ldggtmem
dggt_test_linux_LDFLAGS = -Wl,-rpath=. -Wl,-rpath=./.libs -L$(libdir)
