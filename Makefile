CC=${CONDA_PREFIX}/bin/clang
CXX=${CONDA_PREFIX}/bin/clang++


.PHONY: all
all: clean format test build run build-and-run debug-and-run


.PHONY: clean
clean:
	rm -rf build/*


.PHONY: format
format:
	clang-format src/* include/* -i


.PHONY: build
build:
	mkdir -p build && \
	cd build && \
	cmake .. && \
	make


.PHONY: debug
debug: clean
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=Debug .. && \
	make


.PHONY: clean
clean:
	rm -rf build


.PHONY: run
run:
	cd build && \
	./monitor


.PHONY: build-and-run
build-and-run: build run


.PHONY: debug-and-run
debug-and-run: build
	cd build && \
	gdb ./monitor
