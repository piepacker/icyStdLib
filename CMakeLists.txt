file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "src/*.cpp"
    "src/*.h"
    "inc/*.h"
)

add_library(icystdlib ${SOURCES})
target_include_directories(icystdlib PRIVATE   "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(icystdlib PUBLIC    "${CMAKE_CURRENT_SOURCE_DIR}/inc")

# if ("CMAKE_CXX_COMPILER_ID" STREQUAL "MSVC")
#     add_definitions(/FI"fi-projdir-BuildConfig.h")
# else
#     add_definitions(-include fi-projdir-BuildConfig.h)
# endif()
# 
# 
# if ("CMAKE_CXX_COMPILER_ID" STREQUAL "MSVC")
#     add_definitions(/FI"fi-projdir-BuildConfig.h")
# else
#     add_definitions(-include fi-projdir-BuildConfig.h)
# endif()
