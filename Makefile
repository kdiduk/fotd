PROJECT=vagabond

CC = zcc +zx
LD = zcc +zx
AR = appmake +zx

# Origin of the game binary. Default value is 32768.
ZORG=32768

CFLAGS = -Wall -clib=sdcc_iy -zorg=${ZORG} \
	-pragma-include:zpragma.inc -preserve

LDFLAGS = -Wall -clib=sdcc_iy -zorg=${ZORG} \
	-pragma-include:zpragma.inc

ARFLAGS = --blockname $(PROJECT) --org $(ZORG)

# additional rule to make loadable tape-file
APPMAKE = $(AR) $(ARFLAGS) -b $(BINDIR)/$(PROJECT)_CODE.bin \
	-o $(BINDIR)/$(PROJECT).tap

VPATH = src
OBJDIR = obj
BINDIR = bin
INCLUDE = -Iinclude
OBJECTS = $(addprefix $(OBJDIR)/, \
	main.o \
	)

$(PROJECT): prebuild $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(BINDIR)/$(PROJECT)
	$(APPMAKE)

$(OBJECTS): $(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

prebuild:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

.PHONY: clean
clean:
	rm $(OBJECTS)

# EOF
