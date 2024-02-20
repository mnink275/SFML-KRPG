# ==================== Game ==================== #
# Debug cmake configuration
build_debug/Makefile:
	@mkdir -p build_debug
	@cd build_debug && \
      cmake -DCMAKE_BUILD_TYPE=Debug ..
# cmake --trace-expand -DCMAKE_BUILD_TYPE=Debug ..

# Release cmake configuration
build_release/Makefile:
	@mkdir -p build_release
	@cd build_release && \
      cmake -DCMAKE_BUILD_TYPE=Release ..

# Run cmake
.PHONY: cmake-debug cmake-release
cmake-debug cmake-release: cmake-%: build_%/Makefile

# Build using cmake
.PHONY: build-debug build-release
build-debug build-release: build-%: cmake-%
	@cmake --build build_$* -j $(shell nproc) --target=KRPG

# Run after build-debug
.PHONY: run-debug run-release
run-debug run-release: run-%: build-%
	@./build_$*/KRPG

# ==================== Editor ==================== #
# Debug cmake configuration
editor-build_debug/Makefile:
	@mkdir -p build_debug
	@cd build_debug && \
      cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release cmake configuration
editor-build_release/Makefile:
	@mkdir -p build_release
	@cd build_release && \
      cmake -DCMAKE_BUILD_TYPE=Release ..

# Run cmake
.PHONY: editor-cmake-debug editor-cmake-release
editor-cmake-debug editor-cmake-release: editor-cmake-%: editor-build_%/Makefile

# Build using cmake
.PHONY: editor-build-debug editor-build-release
editor-build-debug editor-build-release: editor-build-%: editor-cmake-%
	@cmake --build build_debug -j $(shell nproc) --target=KRPG_editor

# Run after build-debug
.PHONY: editor
editor: editor-build-debug
	./build_debug/editor/KRPG_editor

# Cleanup data
.PHONY: clean
clean:
	@rm -rf build_*

# Format the sources
.PHONY: format
format:
	@find core -name '*pp' -type f | xargs clang-format -i
	@find editor -name '*pp' -type f | xargs clang-format -i
