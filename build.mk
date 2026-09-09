.RECIPEPREFIX = >

EXE := cc

ifneq ($(IS_CALLED_FROM_MAKEFILE),1)
$(error This file should not be called directly, and instead should be called from Makefile)
endif

CXX := clang++

ifneq ($(CXX),clang++)
$(info CXX is set to $(CXX), but some features may require clang++)
endif

CPPFLAGS ?=

CXXFLAGS ?= \
	-std=c++26 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	-Wconversion \
	-Wsign-conversion \
	-Wshadow \
	-Wnull-dereference \
	-Wdouble-promotion \
	-Wformat=2 \
	-MP \
	-MMD

ifeq ($(BUILD_TYPE),release)
CXXFLAGS += -O3 -DNDEBUG
BUILD_DIR := build/release
endif

ifeq ($(BUILD_TYPE),debug)
CXXFLAGS += -g -O0
BUILD_DIR := build/debug
endif

SRCS := \
	src/lexer/lexer.cpp \
	src/lexer/token.cpp \
	src/util/string.cpp \
	src/main.cpp
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

$(EXE): $(OBJS)
> $(CXX) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp
> @mkdir -p $(dir $@)
> $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

-include $(OBJS:.o=.d)