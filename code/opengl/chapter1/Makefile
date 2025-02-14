INCLUDES = -I /opt/homebrew/include
LIBPATHS = -L /opt/homebrew/lib

CFLAGS = -Wall -Wextra $(INCLUDES)

LIBS = $(LIBPATHS) -lGLEW -lglfw -framework OpenGL

SRCS = main.c

TARGET = openglstarter

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

clean:
	rm -f $(TARGET)
