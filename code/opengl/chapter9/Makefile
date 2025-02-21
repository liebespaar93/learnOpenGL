CC = g++ -std=c++17
INCLUDES = -I /opt/homebrew/include $(shell find include -type d | sed 's/^/-I /')
LIBPATHS = -L /opt/homebrew/lib
CFLAGS = -Wall -Wextra $(INCLUDES)
LIBS = $(LIBPATHS) -lGLEW -lglfw -framework OpenGL

ROOTDIR = $(abspath $(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))))
SRCDIR = $(ROOTDIR)/src
BUILDDIR = $(ROOTDIR)/build
BINDIR = $(ROOTDIR)/bin
SHADERDIR = $(ROOTDIR)/glsl
GLSLDIR = $(BINDIR)/glsl

SRCS = $(wildcard $(SRCDIR)/**/*.cpp) main.cpp
OBJS = $(SRCS:%.cpp=$(BUILDDIR)/%.o)
TARGET = $(BINDIR)/openglstarter

# 셰이더 파일 목록 가져오기
SHADERS = $(wildcard $(SHADERDIR)/*.frag $(SHADERDIR)/*.vert)

all: $(TARGET) copy_shaders

$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


copy_shaders:
	mkdir -p $(GLSLDIR)
	cp $(SHADERS) $(GLSLDIR)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(GLSLDIR):
	mkdir -p $(GLSLDIR)

clean:
	rm -rf $(BUILDDIR) $(BINDIR)

re: clean all