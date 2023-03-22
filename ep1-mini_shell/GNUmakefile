CC = clang
CFLAGS = -Wall -Wextra -Werror
MAIN = minhaMiniShell
CMDS = nem_eu_nem_de_ninguem soh_eumesmo rodaeolhe sohroda
DEBUG = 0

ifeq ($(DEBUG), 1)
DEBUGFLAGS = -g -O0
else
DEBUGFLAGS =
CFLAGS += -O2
endif

.PHONY: all build install uninstall shell cmds clean

all: build

build: shell cmds
	@echo "Built ($(MAIN) $(CMDS)) on $(PWD)/build/"

install: build
	for cmd in $(CMDS); do \
		install -m 755 build/$$cmd /usr/local/bin/; \
	done
	install -m 755 build/$(MAIN) /usr/local/bin/
	@echo "Installed ($(MAIN) $(CMDS)) to /usr/local/bin/"

uninstall: clean
	for cmd in $(CMDS); do \
		rm -f /usr/local/bin/$$cmd; \
	done
	rm -f /usr/local/bin/$(MAIN)

shell:
	@if [ ! -d build ]; then mkdir build; fi
	$(CC) $(CFLAGS) -Wno-unused-parameter $(DEBUGFLAGS) -o build/$(MAIN) $(MAIN).c

cmds:
	@if [ ! -d build ]; then mkdir build; fi
	for cmd in $(CMDS); do \
		$(CC) $(CFLAGS) $(DEBUGFLAGS) -o build/$$cmd $$cmd.c; \
	done

clean:
	for cmd in $(CMDS); do \
		rm -f build/$$cmd; \
	done
	rm -f build/$(MAIN)
