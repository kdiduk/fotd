PROJECT=vagabond

CC = zcc +zx
LD = zcc +zx
AR = appmake +zx

# Origin of the game binary. Default value is 32768.
ZORG=32768

CFLAGS = -Wall -startup=1 -clib=sdcc_iy -zorg=$(ZORG) -preserve

ARFLAGS = --blockname $(PROJECT) --org $(ZORG)

# additional rule to make loadable tape-file
APPMAKE = $(AR) $(ARFLAGS) -b $(BINDIR)/$(PROJECT)_CODE.bin \
	-o $(BINDIR)/$(PROJECT).tap

VPATH = src
OBJDIR = obj
BINDIR = bin
INCLUDE = -Isrc
OBJECTS = $(addprefix $(OBJDIR)/, \
	forest.o \
	game.o \
	generator.o \
	level.o \
	main.o \
	player.o \
	titlescreen.o \
	)

$(PROJECT): prebuild $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(BINDIR)/$(PROJECT)
	$(APPMAKE)

$(OBJECTS): $(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

prebuild:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

.PHONY: clean
clean:
	$(RM) $(OBJECTS)
	$(RM) -rf $(BINDIR)

# EOF
