add_sources(PLF_2400_SRCS
${CMAKE_CURRENT_SOURCE_DIR}/patch.c
)

target_include_directories(inc_2400
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)  