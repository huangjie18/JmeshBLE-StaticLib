set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/main/arch_main.c
${CMAKE_CURRENT_SOURCE_DIR}/boot/${CMAKE_C_COMPILER_ID}/startup_bx2400.s
)
add_sources(PLF_2400_SRCS ${SRC})

set(INC
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/boot/${CMAKE_C_COMPILER_ID}
${CMAKE_CURRENT_SOURCE_DIR}/compiler/${CMAKE_C_COMPILER_ID}
${CMAKE_CURRENT_SOURCE_DIR}/ll/
)
target_include_directories(inc_2400
INTERFACE ${INC}
)
