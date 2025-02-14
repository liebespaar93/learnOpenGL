INCLUDES = -I /opt/homebrew/include
LIBPATHS = -L /opt/homebrew/lib

CFLAGS = -Wall -Wextra $(INCLUDES)

LIBS = $(LIBPATHS) -lGLEW -lglfw -framework OpenGL

SRCS = main.c shader.c

TARGET = openglstarter

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)