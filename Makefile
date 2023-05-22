CMAKE_COMMON_FLAGS ?= -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
CMAKE_DEBUG_FLAGS ?= -DUSERVER_SANITIZE='addr ub'
NPROCS ?= $(shell nproc)
CLANG_FORMAT ?= clang-format

# Debug cmake configuration
build_debug/Makefile:
	@mkdir -p build
	@cd build && \
      cmake -DCMAKE_BUILD_TYPE=Debug $(CMAKE_COMMON_FLAGS) $(CMAKE_DEBUG_FLAGS) $(CMAKE_OPTIONS) ..

# # Release cmake configuration
# build_release/Makefile:
# 	@git submodule update --init
# 	@mkdir -p build_release
# 	@cd build_release && \
#       cmake -DCMAKE_BUILD_TYPE=Release $(CMAKE_COMMON_FLAGS) $(CMAKE_RELEASE_FLAGS) $(CMAKE_OS_FLAGS) $(CMAKE_OPTIONS) ..

# Run cmake
.PHONY: cmake-debug cmake-release
cmake-debug cmake-release: cmake-%: build_%/Makefile

# Build using cmake
.PHONY: build-debug build-release
build-debug build-release: build-%: cmake-%
	@cmake --build build -j $(NPROCS)

# Cleanup data
.PHONY: dist-clean
dist-clean:
	@rm -rf build_*

# Format the sources
.PHONY: format
format:
	@find src -name '*pp' -type f | xargs $(CLANG_FORMAT) -i

# # Install
# .PHONY: install-debug install-release
# install-debug install-release: install-%: build-%
# 	@cd build_$* && \
# 		cmake --install . -v --component ink

# .PHONY: install
# install: install-release

# # Test
# .PHONY: test-debug test-release
# test-debug test-release: test-%: build-%
# 	@cmake --build build_$* -j $(NPROCS) --target ink_unittest
# 	@cmake --build build_$* -j $(NPROCS) --target ink_benchmark
# 	@cd build_$* && ((test -t 1 && GTEST_COLOR=1 PYTEST_ADDOPTS="--color=yes" ctest -V) || ctest -V)
