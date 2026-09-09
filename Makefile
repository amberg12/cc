.RECIPEPREFIX = >

.PHONY: all
all: release

.PHONY: release
release:
> $(MAKE) -f build.mk BUILD_TYPE=$@ IS_CALLED_FROM_MAKEFILE=1

.PHONY: debug
debug:
> $(MAKE) -f build.mk BUILD_TYPE=$@ IS_CALLED_FROM_MAKEFILE=1

.PHONY: clean
clean:
> rm -f ./cc
> rm -rf build

.PHONY: format
format:
> clang-format -i $$(find src -name '*.cpp' -o -name '*.hpp')