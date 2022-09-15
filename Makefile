#UNAME_S := $(shell uname -s)
#ifeq ($(UNAME_S),Darwin)
#
#	BIN = .bin
##	LIBGLEW = -lGLEW
#	LIBGLEW = -lGLEW
#	LIBGL = -framework OpenGL -framework Cocoa -framework IOKit
#	# LIBSDL = -lSDL2
#	LIBGLFW = -lglfw3
##	LIBGLFW = -lglfw3
#else
#	BIN = .bin
#	LIBGLEW := $(shell pkg-config --libs --cflags glew)
#	LIBGL := $(shell pkg-config --libs --cflags gl)
##	LIBSDL := $(shell pkg-config --libs --cflags sdl2)
##	LIBGLFW := $(shell pkg-config --libs --cflags glfw3)
#	LIBGLFW := -lglfw3
#
#	MAKE_XLIB = $(UNAME_S)
#endif

GLFWBASE = -DNKCD=NKC_GLFW -DNK_GLFW_GL3_MOUSE_GRABBING

#---------------
SOURCES = main.c
#---------------

CFLAGS = -Wall #-Wextra -Werror# -O2
LDFLAGS = -s -lm
GLEWFLAGS =  -I./glew-2.2.0/include
GLFWFLAGS =  -I./glfw-3.3.8/include -framework OpenGL -framework Cocoa -framework IOKit
LIBFLAGS = $(GLEWFLAGS) $(GLFWFLAGS)
STATICS = ./glew-*/lib/*.a ./glfw-*/build/src/*.a
STRICTFLAGS = -std=c11

COMP = gcc $(SOURCES) $(LIBFLAGS) $(CFLAGS) $(LDFLAGS) $(STRICTFLAGS)

all: nuklear

nuklear: glew glfw main.c
	$(COMP) $(STATICS) $(GLFWBASE) -DNKC_USE_OPENGL=3 $(LIBGL) $(LIBGLEW) -o easy_nuk.mac

glew:
	cd glew-* && $(MAKE)

glfw:
	cd glfw-* && cmake -S . -B ./build && cd ./build && $(MAKE)

clean:
	-cd glew-* && $(MAKE) clean
	-cd glfw-*/build/ && $(MAKE) clean
	rm  easy_nuk.mac


