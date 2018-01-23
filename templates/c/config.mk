# config.mk - Makefile configuration variables
#
# AUTHOR: Joey Pabalinas <alyptik@protonmail.com>
# See LICENSE.md file for copyright and license details.

# optional
DESTDIR ?=
PREFIX ?= /usr/local
CC ?= gcc
OLVL ?= -O2

# mandatory
LD = $(CC)
DEBUG_CFLAGS = $(CFLAGS) $(DEBUG)
DEBUG_LDFLAGS = $(LDFLAGS) $(DEBUG)
MKALL = $(MKCFG) $(DEP)
OBJ = $(SRC:.c=.o)
TOBJ = $(TSRC:.c=.o)
DEP = $(SRC:.c=.d) $(TSRC:.c=.d)
TEST = $(filter-out $(TAP),$(TSRC:.c=))
UTEST = $(filter-out src/$(TARGET).o,$(SRC:.c=.o))
SRC := $(wildcard src/*.c)
TSRC := $(wildcard t/*.c)
HDR := $(wildcard src/*.h) $(wildcard t/*.h)
DEBUG := $(shell gcc -v 2>&1 | awk '/version/ { if (substr($$3, 1, 1) == 7) { print "-Wrestrict" } }')
ASAN := -fsanitize=address,alignment,leak,undefined
CPPFLAGS := -D_FORTIFY_SOURCE=2 -D_GNU_SOURCE -MMD -MP
LIBS := -lelf -lhistory -lreadline
TARGET := template
MANPAGE := template.1
COMPLETION := _template
TAP := t/tap
BINDIR := bin
MANDIR := share/man/man1
COMPDIR := share/zsh/site-functions
MKALL += Makefile asan.mk
DEBUG += -Wshadow -Wfloat-equal
DEBUG += -Og -ggdb3 -no-pie -D_DEBUG
DEBUG += -fno-inline -fno-builtin -fno-common -fverbose-asm
CFLAGS += -std=c11 -pedantic -errors-Wall -Wextra
CFLAGS += -Wstrict-overflow -Wno-unused-variable
CFLAGS += -Wno-implicit-fallthrough -Wno-missing-field-initializers
CFLAGS += -fPIC -fuse-ld=gold -flto -fuse-linker-plugin -fno-strict-aliasing
LDFLAGS += -Wl,-O2,-z,relro,-z,now,--sort-common,--as-needed
LDFLAGS += -fPIC -fuse-ld=gold -flto -fuse-linker-plugin -fno-strict-aliasing

# vi:ft=make:
