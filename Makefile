NPROCS ?= $(shell nproc)
CLANG_FORMAT ?= clang-format

# Debug cmake configuration
build_debug/Makefile:
	@mkdir -p build_debug
	@cd build_debug && \
      cmake -DCMAKE_BUILD_TYPE=Debug ..
# cmake --trace-expand -DCMAKE_BUILD_TYPE=Debug ..

# # Release cmake configuration
# build_release/Makefile:
# 	@mkdir -p build_release
# 	@cd build_release && \
#       cmake -DCMAKE_BUILD_TYPE=Release ..

# Run cmake
.PHONY: cmake-debug cmake-release
cmake-debug cmake-release: cmake-%: build_%/Makefile

# Build using cmake
.PHONY: build-debug build-release
build-debug build-release: build-%: cmake-%
	@cmake --build build_debug -j $(NPROCS)

# Run after build-debug
.PHONY: run
run: build-debug
	./build_debug/KRPG

# Cleanup data
.PHONY: dist-clean
dist-clean:
	@rm -rf build_*

# Format the sources
.PHONY: format
format:
	@find src -name '*pp' -type f | xargs $(CLANG_FORMAT) -i

# # Test
# .PHONY: test-debug test-release
# test-debug test-release: test-%: build-%
# 	@cmake --build build_$* -j $(NPROCS) --target ink_unittest
# 	@cmake --build build_$* -j $(NPROCS) --target ink_benchmark
# 	@cd build_$* && ((test -t 1 && GTEST_COLOR=1 PYTEST_ADDOPTS="--color=yes" ctest -V) || ctest -V)
