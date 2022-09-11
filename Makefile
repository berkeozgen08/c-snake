CC=gcc
CFLAGS=-W -Wextra -Wall
LFLAGS=
LIBS=SDL2 SDL2main

SRC=src
OBJ=obj
BIN=bin
INC=inc
LIB=lib/SDL2

DIRS:=$(OBJ) $(BIN)
SRCS:=$(wildcard $(SRC)/*.c)
OBJS:=$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
OUTPUT:=$(BIN)/snake

COPY_FROM=lib/SDL2/SDL2.dll
COPY_TO=$(BIN)/$(notdir $(COPY_FROM))

ifeq ($(OS),Windows_NT)
  RM=del /Q
  FixPath=$(subst /,\,$1)
  CP=copy
  OUTPUT:=$(OUTPUT).exe
else
  RM=rm -f
  FixPath=$1
  CP=cp
endif

.PHONY: all
all: $(DIRS) $(OUTPUT) $(COPY_TO)

$(OBJ)/%.o: $(SRC)/%.c $(INC)/*.h
	$(CC) -c -o $@ $(CFLAGS) $< $(patsubst %,-I%,$(INC))

$(OUTPUT): $(OBJS)
	$(CC) -o $@ $(LFLAGS) $^ -L$(LIB) $(patsubst %,-l%,$(LIBS))

$(DIRS): $@
	@mkdir $@

.PHONY: debug
debug: CFLAGS+=-g
debug: clean $(OUTPUT) $(COPY_TO)

.PHONY: clean
clean:
	$(RM) $(call FixPath,$(BIN)/* $(OBJ)/*)

$(COPY_TO):
	$(patsubst %,$(CP) % $(call FixPath,$@),$(call FixPath,$(COPY_FROM)))
