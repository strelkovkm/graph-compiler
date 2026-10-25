if(GC_ENABLE_IGC)
  gc_add_mlir_library(
    GcJitEngine
    Cache.cpp
    JitEngine.cpp
    LINK_LIBS
    PUBLIC
    GcInterface
    ${MLIR_EXECUTION_ENGINE}
    LLVMOrcJIT
    LLVMOrcTargetProcess)
endif()

add_subdirectory(GPURuntime)
