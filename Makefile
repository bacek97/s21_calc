UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	BIN = .bin
	LIBGLEW = -lGLEW
	LIBGL = -framework OpenGL -framework Cocoa -framework IOKit
	# LIBSDL = -lSDL2
	LIBGLFW = -lglfw3
else
	BIN = .bin
	LIBGLEW := $(shell pkg-config --libs --cflags glew)
	LIBGL := $(shell pkg-config --libs --cflags gl)
	# LIBSDL := $(shell pkg-config --libs --cflags sdl2)
	LIBGLFW := $(shell pkg-config --libs --cflags glfw3)
	MAKE_XLIB = $(UNAME_S)
endif

GLFWBASE = -DNKCD=NKC_GLFW $(LIBGLFW)

#---------------
SOURCES = main.c
#---------------

CFLAGS = -Wall # -O2
LDFLAGS = -s -lm
STRICTFLAGS = -std=c89

COMP = $(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) $(STRICTFLAGS)

all: nuklear

nuklear:
	$(COMP) $(GLFWBASE) -DNKC_USE_OPENGL=3 $(LIBGL) $(LIBGLEW) -o easy_nuk