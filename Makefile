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
	cmake -DCMAKE_BUILD_TYPE=Release -GNinja .. && \
	ninja


.PHONY: rebuild
rebuild: clean build


.PHONY: debug
debug:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=Debug -GNinja .. && \
	ninja


.PHONY: clean
clean:
	rm -rf build


.PHONY: run
run:
	cd build && \
	./monitor


.PHONY: build-and-run
build-and-run: build run


.PHONY: rebuild-and-run
rebuild-and-run: rebuild run


.PHONY: rebuild-and-debug
rebuild-and-debug: clean debug
	cd build && \
	gdb ./monitor
