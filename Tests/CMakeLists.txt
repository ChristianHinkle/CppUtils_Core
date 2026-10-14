# Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

cmake_minimum_required(VERSION 4.0)

# Write out the main project name here, in one place, to make renaming easier. This is mainly used by our
# boilerplate code. There may be other mentions of the project's name mixed in certain places of this file, so
# don't rely on these variables alone for renaming.
set(my_project_name "CppUtils_Core")
set(my_project_name_target_alias_format "CppUtils::Core")
set(my_project_name_test_format "CppUtils.Core")

project(${my_project_name}_Tests
  VERSION 0.1.0
  LANGUAGES CXX
  )

# Note that we do not "find package" for our parent project. We don't need to since we are built in the same
# cmake invocation as the it. That means we're being processed during the same configuration step as them, which
# means we'll have all their targets. Also, the targets that we reference in `target_link_libraries` commands don't
# even need to exist yet because CMake only validates the existence of targets at the end of the entire
# configuration process.

add_library(${my_project_name}_NonLvalueReference STATIC EXCLUDE_FROM_ALL)
target_compile_features(${my_project_name}_NonLvalueReference PUBLIC cxx_std_20)
target_sources(${my_project_name}_NonLvalueReference PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source/NonLvalueReference.cpp")
target_link_libraries(${my_project_name}_NonLvalueReference
  PRIVATE
    ${my_project_name_target_alias_format}::Include
  )

add_test(
  NAME ${my_project_name_test_format}.NonLvalueReference
  COMMAND ${CMAKE_COMMAND}
    --build ${CMAKE_CURRENT_BINARY_DIR}
    --target ${my_project_name}_NonLvalueReference
  )

add_library(${my_project_name}_CharLike STATIC EXCLUDE_FROM_ALL)
target_compile_features(${my_project_name}_CharLike PUBLIC cxx_std_20)
target_sources(${my_project_name}_CharLike PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source/CharLike.cpp")
target_link_libraries(${my_project_name}_CharLike
  PRIVATE
    ${my_project_name_target_alias_format}::Include
  )

add_test(
  NAME ${my_project_name_test_format}.CharLike
  COMMAND ${CMAKE_COMMAND}
    --build ${CMAKE_CURRENT_BINARY_DIR}
    --target ${my_project_name}_CharLike
  )

add_executable(${my_project_name}_Filesystem_MakeAbsoluteUsingBase)
target_compile_features(${my_project_name}_Filesystem_MakeAbsoluteUsingBase PUBLIC cxx_std_20)
target_sources(${my_project_name}_Filesystem_MakeAbsoluteUsingBase PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source/Filesystem_MakeAbsoluteUsingBase.cpp")
target_link_libraries(${my_project_name}_Filesystem_MakeAbsoluteUsingBase
  PRIVATE
    ${my_project_name_target_alias_format}::Static
  )

add_test(
  NAME ${my_project_name_test_format}.Filesystem.MakeAbsoluteUsingBase
  COMMAND ${my_project_name}_Filesystem_MakeAbsoluteUsingBase
  )

add_executable(${my_project_name}_Filesystem_IsRootPath)
target_compile_features(${my_project_name}_Filesystem_IsRootPath PUBLIC cxx_std_20)
target_sources(${my_project_name}_Filesystem_IsRootPath PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source/Filesystem_IsRootPath.cpp")
target_link_libraries(${my_project_name}_Filesystem_IsRootPath
  PRIVATE
    ${my_project_name_target_alias_format}::Static
  )

add_test(
  NAME ${my_project_name_test_format}.Filesystem.IsRootPath
  COMMAND ${my_project_name}_Filesystem_IsRootPath
  )
