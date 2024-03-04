cmake_minimum_required(VERSION 3.16)

# Set the name of the project here
project(dump LANGUAGES C)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON CACHE BOOL "Prevents cmake -S. -B.")
set(CMAKE_DISABLE_SOURCE_CHANGES ON CACHE BOOL "Prevent writing files to CMAKE_SOURCE_DIR under configure")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/core/")

# Add each prog within the `prog/` folder
file(GLOB progs LIST_DIRECTORIES true 
  "${CMAKE_CURRENT_SOURCE_DIR}/prog/*")

foreach(prog IN LISTS progs)
  get_filename_component(name "${prog}" NAME_WLE)
  file(GLOB prog_src LIST_FILES ON "${CMAKE_CURRENT_SOURCE_DIR}/prog/${name}/*.c")
  
  set(BUILD_SHARED_LIBS OFF)

  add_executable(${name})
  target_sources(${name} PRIVATE ${prog_src}) 

  # Add flags to the compiler here (these are pedantic flags)
  target_compile_options(${name} PUBLIC
      $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic>
      $<$<C_COMPILER_ID:MSVC>:/WX /W4>)

  target_link_libraries(${name}
        PRIVATE
          core)
endforeach()
