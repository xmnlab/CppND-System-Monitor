CC=${CONDA_PREFIX}/bin/x86_64-conda_cos6-linux-gnu-gcc
CXX=${CONDA_PREFIX}/bin/x86_64-conda_cos6-linux-gnu-g++

.PHONY: all
all: format test build run

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
debug:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make

.PHONY: clean
clean:
	rm -rf build

.PHONY: run
run:
	cd build && \
	./monitor
