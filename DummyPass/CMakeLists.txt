cmake_minimum_required(VERSION 3.13)
project(DummyPass)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_library(DummyPass MODULE DummyPass.cpp)

set_target_properties(DummyPass PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)

target_compile_features(DummyPass PRIVATE cxx_std_17)

llvm_map_components_to_libnames(llvm_libs Support Core IRReader Passes)
target_link_libraries(DummyPass PRIVATE ${llvm_libs})


