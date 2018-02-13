##
## CMAKE file for neam projects
##

function(set_compile_flags target level)
  # general flags
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${target} ${level} "-O0")
    target_compile_options(${target} ${level} "-g3")
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${target} ${level} "-DNDEBUG")
  elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    target_compile_options(${target} ${level} "-DNDEBUG")
  endif()

  # some gcc/clang flags
  if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(${target} ${level} "-std=c++1z")
    target_compile_options(${target} ${level} "-Wall")
    target_compile_options(${target} ${level} "-Wextra")
    target_compile_options(${target} ${level} "-Wno-unused-function")
    target_compile_options(${target} ${level} "-Wno-multichar")

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
      target_compile_options(${target} ${level} "-Og")
      target_compile_options(${target} ${level} "-fno-inline")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
      target_compile_options(${target} ${level} "-O3")
      target_compile_options(${target} ${level} "-finline-limit=100")
    elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
      target_compile_options(${target} ${level} "-Os")
    endif()

  elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    target_compile_options(${target} ${level} "-std=c++1z")
    target_compile_options(${target} ${level} "-Wall")
    target_compile_options(${target} ${level} "-Wextra")
    target_compile_options(${target} ${level} "-Wno-unused-function")
    target_compile_options(${target} ${level} "-Wno-multichar")

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
      target_compile_options(${target} ${level} "-O3")
    elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
      target_compile_options(${target} ${level} "-Oz")
    endif()

  elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    target_compile_options(${target} ${level} "/std:c++latest")
  endif()
endfunction()
