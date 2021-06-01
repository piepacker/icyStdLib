file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "src/*.cpp"
    "src/*.h"
    "inc/*.h"
)

add_library(icystdlib ${SOURCES})
target_include_directories(icystdlib PRIVATE   "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(icystdlib PUBLIC    "${CMAKE_CURRENT_SOURCE_DIR}/inc")

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
    add_definitions(/FI"fi-platform-defines.h" /FI"fi-printf-redirect.h")
else()
    add_definitions(-include fi-platform-defines.h -include fi-printf-redirect.h)
endif()
