file(STRINGS sources.mk SRCS)
file(GLOB_RECURSE INCLUDE include/*.hpp)

include_directories(include)

add_executable(graph ${SRCS} ${INCLUDE})

target_include_directories(graph PRIVATE include)