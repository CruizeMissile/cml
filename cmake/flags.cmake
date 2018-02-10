##
## CMAKE file for neam projects
##

function(set_compile_flags target)
  # general flags
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${target} INTERFACE "-O0")
    target_compile_options(${target} INTERFACE "-g3")
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${target} INTERFACE "-DNDEBUG")
  elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    target_compile_options(${target} INTERFACE "-DNDEBUG")
  endif()

  # some gcc/clang flags
  if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(${target} INTERFACE "-std=c++1z")
    target_compile_options(${target} INTERFACE "-Wall")
    target_compile_options(${target} INTERFACE "-Wextra")
    target_compile_options(${target} INTERFACE "-Wno-unused-function")
    target_compile_options(${target} INTERFACE "-Wno-multichar")

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
      target_compile_options(${target} INTERFACE "-Og")
      target_compile_options(${target} INTERFACE "-fno-inline")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
      target_compile_options(${target} INTERFACE "-O3")
      target_compile_options(${target} INTERFACE "-finline-limit=100")
    elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
      target_compile_options(${target} INTERFACE "-Os")
    endif()

  elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    target_compile_options(${target} INTERFACE "-std=c++1z")
    target_compile_options(${target} INTERFACE "-Wall")
    target_compile_options(${target} INTERFACE "-Wextra")
    target_compile_options(${target} INTERFACE "-Wno-unused-function")
    target_compile_options(${target} INTERFACE "-Wno-multichar")

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
      target_compile_options(${target} INTERFACE "-O3")
    elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
      target_compile_options(${target} INTERFACE "-Oz")
    endif()

  elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    target_compile_options(${target} INTERFACE "/std:c++latest")
  endif()
endfunction()
