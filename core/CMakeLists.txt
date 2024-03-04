file(GLOB sources CONFIGURE_DEPENDS ON "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

add_library(core)

set_target_properties(core PROPERTIES LINKER_LANGUAGE C)

target_include_directories(core
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

target_compile_definitions(core
  PUBLIC
    $<$<BOOL:${DUMP_DEBUG_OUTPUT}>:SOL_DEBUG_OUTPUT>
    $<$<PLATFORM_ID:Windows>:PLATFORM_WINDOWS>
    $<$<PLATFORM_ID:Linux>:PLATFORM_LINUX>
    $<$<PLATFORM_ID:FreeBSD>:PLATFORM_BSD>
    $<$<PLATFORM_ID:OpenBSD>:PLATFORM_BSD>
    $<$<PLATFORM_ID:NetBSD>:PLATFORM_BSD>
    $<$<PLATFORM_ID:Darwin>:PLATFORM_MAC>)

target_link_libraries(core
  PUBLIC
    $<$<NOT:$<PLATFORM_ID:Windows>>:m>)

target_sources(core PRIVATE ${sources})

set_property(TARGET core PROPERTY C_VISIBILITY_PRESET "hidden")

install(TARGETS core
  EXPORT core-targets
  INCLUDES DESTINATION "${CMAKE_INCLUDE_INSTALLDIR}")
