CC = clang
CFLAGS = -Wall -Wextra -Werror
SHELL = minhaMiniShell
CMDS = nem_eu_nem_de_ninguem soh_eumesmo rodaeolhe sohroda
DEBUG = 0

.if ${DEBUG} == 1
DEBUGFLAGS = -g -O0
.else
DEBUGFLAGS =
CFLAGS += -O2
.endif

all: build

build: shell cmds
	@echo "Built (${SHELL} ${CMDS}) on ${PWD}/build/"

install: build
.for cmd in ${CMDS}
	install -m 755 build/${cmd} /usr/local/bin/
.endfor
	install -m 755 build/${SHELL} /usr/local/bin/
	@echo "Installed (${SHELL} ${CMDS}) to /usr/local/bin/"

uninstall: clean
.for cmd in ${CMDS}
	rm -f /usr/local/bin/${cmd}
.endfor
	rm -f /usr/local/bin/minhaMiniShell

shell:
	@if [ ! -d build ]; then mkdir build; fi
	${CC} ${CFLAGS} -Wno-unused-parameter ${DEBUGFLAGS} -o build/minhaMiniShell ${SHELL}.c

cmds:
	@if [ ! -d build ]; then mkdir build; fi
.for cmd in ${CMDS}
	${CC} ${CFLAGS} ${DEBUGFLAGS} -o build/${cmd} ${cmd}.c
.endfor

clean:
.for cmd in ${CMDS}
	rm -f build/${cmd}
.endfor
	rm -f build/${SHELL}
