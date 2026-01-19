CC ?= gcc
LDFLAGS_COMMON := -lm
CFLAGS_COMMON := -std=c11 -Iinclude -Wall -Wextra -Wpedantic

# Base build (fast-ish, no instrumentation)
CFLAGS_RELEASE := $(CFLAGS_COMMON) -O2

# Debug build for GDB
CFLAGS_DEBUG := $(CFLAGS_COMMON) -O0 -g

# ASAN build for memory bugs/leaks
CFLAGS_ASAN := $(CFLAGS_COMMON) -O0 -g -fsanitize=address -fno-omit-frame-pointer

# gprof build
CFLAGS_GPROF := $(CFLAGS_COMMON) -O0 -g -pg
LDFLAGS_GPROF := $(LDFLAGS_COMMON) -pg

SRC := src/main.c src/dataset.c src/metrics.c

.PHONY: all clean debug asan gprof profile run_dbg run_asan run_gprof

all:
	@echo "Targets: debug | asan | gprof | profile | clean"

clean:
	rm -rf build bin gmon.out

debug: bin/buglab_dbg
asan: bin/buglab_asan
gprof: bin/buglab_gprof

build/debug/%.o: src/%.c
	mkdir -p build/debug
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@

build/asan/%.o: src/%.c
	mkdir -p build/asan
	$(CC) $(CFLAGS_ASAN) -c $< -o $@

build/gprof/%.o: src/%.c
	mkdir -p build/gprof
	$(CC) $(CFLAGS_GPROF) -c $< -o $@

bin/buglab_dbg: $(patsubst src/%.c,build/debug/%.o,$(SRC))
	mkdir -p bin
	$(CC) $^ -o $@ $(LDFLAGS_COMMON)

bin/buglab_asan: $(patsubst src/%.c,build/asan/%.o,$(SRC))
	mkdir -p bin
	$(CC) $^ -o $@ $(LDFLAGS_COMMON) -fsanitize=address

bin/buglab_gprof: $(patsubst src/%.c,build/gprof/%.o,$(SRC))
	mkdir -p bin
	$(CC) $^ -o $@ $(LDFLAGS_GPROF)

profile:
	@gprof ./bin/buglab_gprof gmon.out | less

run_dbg:
	./bin/buglab_dbg 2000 3

run_asan:
	ASAN_OPTIONS=detect_leaks=1 ./bin/buglab_asan 2000 3

run_gprof:
	./bin/buglab_gprof 4000 3
