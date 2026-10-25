## Build and install Python bindings

Create a virtual environment:

```bash
python -m venv .venv --prompt gc
. .venv/bin/activate
pip install nanobind pytest torch torch-mlir \
  --extra-index-url https://download.pytorch.org/whl/xpu \
  --find-links https://github.com/llvm/torch-mlir-release/releases/expanded_assets/dev-wheels
```

Build the project and install the Python bindings in editable mode:

```bash
pip install -v -e python/
```

## Run Python examples

```bash
python python/example/matmul.py
```

## Run Python unit tests

```bash
pytest python/test/test_torch.py -v -s
```

## Run gc-opt

```bash
./build/bin/gc-opt --gpu-dev-props='arch=pvc' --gc-gpu-pipeline='dump' linalg_on_tensors.mlir
```

## Portable OpenCL backend

Set `-DGC_ENABLE_IGC=OFF` to build the OpenCL C source backend without XeGPU, XeVM, or
SPIR-V code generation. When IGC is enabled, non-Intel OpenCL devices use the source
backend by vendor ID. With IGC disabled, all devices use it. IGC defaults to OFF on macOS,
where its dependencies are unavailable. Static kernels are built by the platform OpenCL C
compiler. Attention materializes its score matrix.

With `GC_ENABLE_TEST=ON`, run `ctest --test-dir <build> -R gc-ocl-source --output-on-failure`
to check source execution on an available OpenCL GPU.
