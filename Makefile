# Top-level Makefile (basic)

.PHONY: all iso clean

all: image

image:
	@echo "Use build/scripts/build.sh to build the project (customize the toolchain and paths)."

iso:
	bash build/scripts/build.sh

clean:
	rm -rf build/output || true
