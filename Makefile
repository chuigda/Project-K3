ifndef CC
	CC = gcc
endif
ifndef AR
	AR = ar
endif
ifndef RANLIB
	RANLIB = ranlib
endif

ifndef CFLAGS
	CFLAGS = -Wall -Wextra \
		-Wno-pedantic \
		-Wno-cast-function-type \
		-Wno-char-subscripts \
		-g \
		$(EXTRA_CFLAGS)
endif

define LOG
	@printf '\t%s\t%s\n' $1 $2
endef

define COMPILE
	$(call LOG,CC,$1)
	@$(CC) $(CFLAGS) $1 \
		-Iconfig -Iinclude -Isrc/include \
		-fPIC -c -o $2
endef

HEADER_FILES = $(wildcard include/*.h) $(wildcard src/include/*.h)
SOURCE_FILES = $(wildcard src/*.c)
OBJECT_FILES := $(patsubst src/%.c,%.o,$(SOURCE_FILES))

k3.exe: main.o $(OBJECT_FILES)
	$(call LOG,LINK,K3.EXE)
	@$(CC) $(CFLAGS) $^ -o $@

main.o: main.c $(HEADER_FILES)
	$(call COMPILE,$<,$@)

%.o: src/%.c $(HEADER_FILES)
	$(call COMPILE,$<,$@)