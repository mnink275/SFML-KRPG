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
	@cmake --build build_debug -j $(shell nproc)

# Run after build-debug
.PHONY: run
run: build-debug
	./build_debug/KRPG

# Run editor after build-debug
.PHONY: run-editor
run-editor: build-debug
	./build_debug/editor/KRPG_editor

# Cleanup data
.PHONY: dist-clean
dist-clean:
	@rm -rf build_*

# Format the sources
.PHONY: format
format:
	@find core -name '*pp' -type f | xargs clang-format -i
	@find editor -name '*pp' -type f | xargs clang-format -i
