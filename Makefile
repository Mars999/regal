include config/version

SHELL = /bin/sh
SYSTEM ?= $(shell config/config.guess | cut -d - -f 3 | sed -e 's/[0-9\.]//g;')
SYSTEM.SUPPORTED = $(shell test -f config/Makefile.$(SYSTEM) && echo 1)

ifeq ($(SYSTEM.SUPPORTED), 1)
include config/Makefile.$(SYSTEM)
else
$(error "Platform '$(SYSTEM)' not supported")
endif

REGAL_DEST ?= /usr
BINDIR     ?= $(REGAL_DEST)/bin
LIBDIR     ?= $(REGAL_DEST)/lib

# To disable stripping of binaries either:
#   - use STRIP= on gmake command-line
#   - edit this makefile to set STRIP to the empty string
#
# To disable symlinks:
#   - use LN= on gmake command-line

AR      ?= ar
INSTALL ?= install
STRIP   ?= strip
RM      ?= rm -f
LN      ?= ln -sf

ifeq ($(MAKECMDGOALS), debug)
OPT = -g
STRIP :=
else
OPT = $(POPT)
endif
INCLUDE = -Iinclude
CFLAGS = $(OPT) $(WARN) $(INCLUDE) $(CFLAGS.EXTRA)

all debug: regal.lib glew.lib glut.lib regal.bin

# REGAL shared and static libraries

export:
	scripts/Export.py --api gl 4.2 --api wgl 4.0 --api glx 4.0 --api cgl 1.4 --api egl 1.0 --outdir src/regal

LIB.LDFLAGS        := $(LDFLAGS.EXTRA) $(LDFLAGS.GL) -lstdc++ -lpthread
LIB.LIBS           := $(GL_LDFLAGS)

LIB.SRCS           :=
LIB.SRCS           += src/regal/RegalIff.cpp
LIB.SRCS           += src/regal/Regal.cpp
LIB.SRCS           += src/regal/RegalToken.cpp
LIB.SRCS           += src/regal/RegalLog.cpp
LIB.SRCS           += src/regal/RegalLookup.cpp
LIB.SRCS           += src/regal/RegalContext.cpp
LIB.SRCS           += src/regal/RegalContextInfo.cpp
LIB.SRCS           += src/regal/RegalEmuDispatch.cpp
LIB.SRCS           += src/regal/RegalDebugDispatch.cpp
LIB.SRCS           += src/regal/RegalErrorDispatch.cpp
LIB.SRCS           += src/regal/RegalLoaderDispatch.cpp

LIB.SRCS.NAMES     := $(notdir $(LIB.SRCS))

LIB.INCLUDE        := -Isrc/boost

LIB.DEPS           :=
LIB.DEPS           += include/GL/Regal.h
LIB.DEPS           += src/regal/RegalPrivate.h

LIB.OBJS           := $(addprefix tmp/$(SYSTEM)/regal/static/,$(LIB.SRCS.NAMES))
LIB.OBJS           := $(LIB.OBJS:.cpp=.o)
LIB.SOBJS          := $(addprefix tmp/$(SYSTEM)/regal/shared/,$(LIB.SRCS.NAMES))
LIB.SOBJS          := $(LIB.SOBJS:.cpp=.o)

regal.lib: lib lib/$(LIB.SHARED) lib/$(LIB.STATIC)

lib:
	mkdir lib

lib/$(LIB.STATIC): $(LIB.OBJS)
	$(AR) cr $@ $^
ifneq ($(STRIP),)
	$(STRIP) -x $@
endif

lib/$(LIB.SHARED): $(LIB.SOBJS)
	$(LD) $(LDFLAGS.SO) -o $@ $^ $(LIB.LDFLAGS) $(LIB.LIBS)
ifneq ($(LN),)
	$(LN) $(LIB.SHARED) lib/$(LIB.SONAME)
	$(LN) $(LIB.SHARED) lib/$(LIB.DEVLNK)
ifneq ($(LIB.FRAMEWORK),)
	$(LN) $(LIB.SHARED) lib/$(LIB.FRAMEWORK)
endif
endif
ifneq ($(STRIP),)
	$(STRIP) -x $@
endif

tmp/$(SYSTEM)/regal/static/%.o: src/regal/%.cpp $(LIB.DEPS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CFLAGS.SO) $(LIB.INCLUDE) -o $@ -c $<

tmp/$(SYSTEM)/regal/shared/%.o: src/regal/%.cpp $(LIB.DEPS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PICFLAG) $(CFLAGS.SO) $(LIB.INCLUDE) -o $@ -c $<

#
# RegalGLEW
#

GLEW.SRCS        += src/glew/src/glew.c
GLEW.SRCS.NAMES := $(notdir $(GLEW.SRCS))
GLEW.OBJS       := $(addprefix tmp/$(SYSTEM)/glew/shared/,$(GLEW.SRCS.NAMES))
GLEW.OBJS       := $(GLEW.OBJS:.c=.o)
GLEW.CFLAGS     := -Isrc/glew/include -DGLEW_EXPORTS -DGLEW_BUILD
GLEW.SHARED     := libRegalGLEW.$(EXT.DYNAMIC)
GLEW.STATIC     := libRegalGLEW.a

glew.lib: lib lib/$(GLEW.SHARED)

tmp/$(SYSTEM)/glew/shared/%.o: src/glew/src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PICFLAG) $(GLEW.CFLAGS) $(CFLAGS.SO) -o $@ -c $<

lib/$(GLEW.SHARED): $(GLEW.OBJS)
	$(LD) $(LDFLAGS.DYNAMIC) -o $@ $^ $(LIB.LDFLAGS) $(GLEW.LIBS)  -lpthread
ifneq ($(STRIP),)
	$(STRIP) -x $@
endif

ifneq ($(filter darwin%,$(SYSTEM)),)
glut.lib:

else

#
# RegalGLUT
#

# NOT for windows...

GLUT.SRCS        += src/glut/src/capturexfont.c
GLUT.SRCS        += src/glut/src/glut_glxext.c
GLUT.SRCS        += src/glut/src/glut_menu.c
GLUT.SRCS        += src/glut/src/glut_menu2.c
GLUT.SRCS        += src/glut/src/layerutil.c

# Windows and Linux...

GLUT.SRCS        += src/glut/src/glut_8x13.c
GLUT.SRCS        += src/glut/src/glut_9x15.c
GLUT.SRCS        += src/glut/src/glut_bitmap.c
GLUT.SRCS        += src/glut/src/glut_bwidth.c
GLUT.SRCS        += src/glut/src/glut_cindex.c
GLUT.SRCS        += src/glut/src/glut_cmap.c
GLUT.SRCS        += src/glut/src/glut_cursor.c
GLUT.SRCS        += src/glut/src/glut_dials.c
GLUT.SRCS        += src/glut/src/glut_dstr.c
GLUT.SRCS        += src/glut/src/glut_event.c
GLUT.SRCS        += src/glut/src/glut_ext.c
GLUT.SRCS        += src/glut/src/glut_fcb.c
GLUT.SRCS        += src/glut/src/glut_fullscrn.c
GLUT.SRCS        += src/glut/src/glut_gamemode.c
GLUT.SRCS        += src/glut/src/glut_get.c
GLUT.SRCS        += src/glut/src/glut_hel10.c
GLUT.SRCS        += src/glut/src/glut_hel12.c
GLUT.SRCS        += src/glut/src/glut_hel18.c
GLUT.SRCS        += src/glut/src/glut_init.c
GLUT.SRCS        += src/glut/src/glut_input.c
GLUT.SRCS        += src/glut/src/glut_joy.c
GLUT.SRCS        += src/glut/src/glut_key.c
GLUT.SRCS        += src/glut/src/glut_keyctrl.c
GLUT.SRCS        += src/glut/src/glut_keyup.c
GLUT.SRCS        += src/glut/src/glut_mesa.c
GLUT.SRCS        += src/glut/src/glut_modifier.c
GLUT.SRCS        += src/glut/src/glut_mroman.c
GLUT.SRCS        += src/glut/src/glut_overlay.c
GLUT.SRCS        += src/glut/src/glut_roman.c
GLUT.SRCS        += src/glut/src/glut_shapes.c
GLUT.SRCS        += src/glut/src/glut_space.c
GLUT.SRCS        += src/glut/src/glut_stroke.c
GLUT.SRCS        += src/glut/src/glut_swap.c
GLUT.SRCS        += src/glut/src/glut_swidth.c
GLUT.SRCS        += src/glut/src/glut_tablet.c
GLUT.SRCS        += src/glut/src/glut_teapot.c
GLUT.SRCS        += src/glut/src/glut_tr10.c
GLUT.SRCS        += src/glut/src/glut_tr24.c
GLUT.SRCS        += src/glut/src/glut_util.c
GLUT.SRCS        += src/glut/src/glut_vidresize.c
GLUT.SRCS        += src/glut/src/glut_warp.c
GLUT.SRCS        += src/glut/src/glut_win.c
GLUT.SRCS        += src/glut/src/glut_winmisc.c
GLUT.SRCS        += src/glut/src/glut_ppm.c
GLUT.SRCS.NAMES := $(notdir $(GLUT.SRCS))
GLUT.OBJS       := $(addprefix tmp/$(SYSTEM)/glut/shared/,$(GLUT.SRCS.NAMES))
GLUT.OBJS       := $(GLUT.OBJS:.c=.o)
GLUT.CFLAGS     := -Isrc/glut/include -DBUILD_GLUT32 -DGLUT_BUILDING_LIB -DGLUT_STATIC
GLUT.SHARED     := libRegalGLUT.$(EXT.DYNAMIC)
GLUT.STATIC     := libRegalGLUT.a

glut.lib: lib lib/$(GLUT.SHARED)

tmp/$(SYSTEM)/glut/shared/%.o: src/glut/src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PICFLAG) $(GLUT.CFLAGS) $(CFLAGS.SO) -o $@ -c $<

lib/$(GLUT.SHARED): $(GLUT.OBJS)
	$(LD) $(LDFLAGS.DYNAMIC) -o $@ $^ -Llib -lRegal -lGLU -lX11 -lXmu -lXi -lpthread
ifneq ($(STRIP),)
	$(STRIP) -x $@
endif

endif

# Examples

regal.bin: bin bin/dreamtorus bin/tiger

bin:
	mkdir bin

#
# dreamtorus
#

DREAMTORUS.SRCS       += examples/dreamtorus/src/render.cpp
DREAMTORUS.SRCS       += examples/dreamtorus/glut/code/main.cpp
DREAMTORUS.SRCS.NAMES := $(notdir $(DREAMTORUS.SRCS))
DREAMTORUS.OBJS       := $(addprefix tmp/$(SYSTEM)/dreamtorus/static/,$(DREAMTORUS.SRCS.NAMES))
DREAMTORUS.OBJS       := $(DREAMTORUS.OBJS:.cpp=.o)
DREAMTORUS.CFLAGS     := -Iinclude -Iexamples/dreamtorus/src

tmp/$(SYSTEM)/dreamtorus/static/%.o: examples/dreamtorus/src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DREAMTORUS.CFLAGS) $(CFLAGS.SO) -o $@ -c $<

tmp/$(SYSTEM)/dreamtorus/static/%.o: examples/dreamtorus/glut/code/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DREAMTORUS.CFLAGS) $(CFLAGS.SO) -o $@ -c $<

bin/dreamtorus: $(DREAMTORUS.OBJS)
	$(LD) -o $@ $^ $(LIB.LDFLAGS) $(LIB.LIBS) $(LDFLAGS.GLUT) $(LDFLAGS.GL) -Llib -l$(NAME) -lm -lpthread
ifneq ($(STRIP),)
	$(STRIP) -x $@
endif

#
# tiger
#

TIGER.SRCS       += examples/tiger/nvpr_tiger.c
TIGER.SRCS       += examples/tiger/tiger.c
TIGER.SRCS       += examples/tiger/xform.c
TIGER.SRCS.NAMES := $(notdir $(TIGER.SRCS))
TIGER.OBJS       := $(addprefix tmp/$(SYSTEM)/tiger/static/,$(TIGER.SRCS.NAMES))
TIGER.OBJS       := $(TIGER.OBJS:.c=.o)
TIGER.CFLAGS     := -Iinclude

tmp/$(SYSTEM)/tiger/static/%.o: examples/tiger/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(TIGER.CFLAGS) $(CFLAGS.SO) -o $@ -c $<

bin/tiger: $(TIGER.OBJS)
	$(LD) -o $@ $^ -Llib -l$(NAME) -lRegalGLEW $(LDFLAGS.GLUT) -lm -lpthread
ifneq ($(STRIP),)
	$(STRIP) -x $@
endif

clean:
	$(RM) -r tmp/
	$(RM) -r lib/
	$(RM) -r bin/
	$(RM) glew.pc glewmx.pc


.PHONY: export
.PHONY: regal.lib regal.bin all debug
.PHONY: clean distclean tardist dist-win32 dist-src
