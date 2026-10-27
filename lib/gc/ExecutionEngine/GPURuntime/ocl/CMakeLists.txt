find_package(OpenCL REQUIRED)

if(GC_ENABLE_IGC)
  gc_add_mlir_library(
    GcGpuOclRuntime
    PARTIAL_SOURCES_INTENDED
    GpuOclRuntime.cpp
    LINK_LIBS
    PUBLIC
    GcInterface
    GcGpuPasses
    GcJitEngine)
  target_include_directories(GcGpuOclRuntime PUBLIC $<BUILD_INTERFACE:${OpenCL_INCLUDE_DIRS}>)
  target_link_libraries(GcGpuOclRuntime PUBLIC ${OpenCL_LIBRARIES}
                                               ${MLIR_EXECUTION_ENGINE})
endif()

gc_add_mlir_library(
  GcGpuOclSourceRuntime
  PARTIAL_SOURCES_INTENDED
  OclSourceModule.cpp
  LINK_LIBS PUBLIC GcInterface GcGpuCommonPasses)
target_include_directories(GcGpuOclSourceRuntime PUBLIC $<BUILD_INTERFACE:${OpenCL_INCLUDE_DIRS}>)
target_link_libraries(GcGpuOclSourceRuntime PUBLIC ${OpenCL_LIBRARIES})

target_include_directories(GcInterface INTERFACE $<BUILD_INTERFACE:${OpenCL_INCLUDE_DIRS}>)
target_link_libraries(GcInterface INTERFACE ${OpenCL_LIBRARIES})
