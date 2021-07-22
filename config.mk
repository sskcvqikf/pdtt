CXX = g++

INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build

VPATH=$(shell find $(SRC_DIR) -type d -print | tr '\012' ':' | sed 's/:$$//')

ifeq (${DEBUG}, gdb)
MODE = -ggdb
endif
ifeq (${DEBUG}, lldb)
MODE = -g
endif
ifndef DEBUG
MODE = -o2 -flto
endif

LIBS = -lncurses -lpanel

CXXFLAGS = -std=c++17 -Wall -Werror -Wextra ${LIBS} ${MODE} -I${INCLUDE_DIR}

BUILD_DIR_GUARD = @mkdir -p $(BUILD_DIR)

GOAL = main

FILES = main dictionary window stdscr_window pdtt \
        statistics_mode default_mode random_letters_mode \

OBJS = $(FILES:%=$(BUILD_DIR)/%.cc.o)
