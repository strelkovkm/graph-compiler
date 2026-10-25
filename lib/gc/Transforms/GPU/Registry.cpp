// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#if !GC_ENABLE_IGC
#include "gc/Dialect/Linalgx/LinalgxDialect.h"
#include "gc/Transforms/Passes.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Arith/Transforms/BufferizableOpInterfaceImpl.h"
#include "mlir/Dialect/Bufferization/Extensions/AllExtensions.h"
#include "mlir/Dialect/Bufferization/IR/Bufferization.h"
#include "mlir/Dialect/Bufferization/Transforms/BufferizableOpInterfaceImpl.h"
#include "mlir/Dialect/Bufferization/Transforms/FuncBufferizableOpInterfaceImpl.h"
#include "mlir/Dialect/Func/Extensions/AllExtensions.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Linalg/Transforms/AllInterfaces.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/SCF/Transforms/BufferizableOpInterfaceImpl.h"
#include "mlir/Dialect/Shape/IR/Shape.h"
#include "mlir/Dialect/Tensor/Extensions/AllExtensions.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Tensor/Transforms/BufferizableOpInterfaceImpl.h"

namespace mlir::gc {
DialectRegistry &getDialectRegistry() {
  static DialectRegistry registry = [] {
    DialectRegistry registry;
    registry.insert<affine::AffineDialect, arith::ArithDialect,
                    bufferization::BufferizationDialect, func::FuncDialect,
                    linalg::LinalgDialect, linalgx::LinalgxDialect,
                    math::MathDialect, memref::MemRefDialect, scf::SCFDialect,
                    tensor::TensorDialect, shape::ShapeDialect>();
    arith::registerBufferizableOpInterfaceExternalModels(registry);
    bufferization::registerAllExtensions(registry);
    bufferization::registerBufferizableOpInterfaceExternalModels(registry);
    bufferization::func_ext::registerBufferizableOpInterfaceExternalModels(
        registry);
    func::registerAllExtensions(registry);
    tensor::registerAllExtensions(registry);
    tensor::registerBufferizableOpInterfaceExternalModels(registry);
    scf::registerBufferizableOpInterfaceExternalModels(registry);
    linalg::registerAllDialectInterfaceImplementations(registry);
    registerDecomposition();
    registerTensorConcatToLinalg();
    return registry;
  }();
  return registry;
}
} // namespace mlir::gc
#endif
