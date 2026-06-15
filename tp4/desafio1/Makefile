# Variables
CC = gcc
CFLAGS = -Wall -Werror
TARGET = helloworld
PREFIX = /usr/local

# Regla por defecto: Compilar el binario
all: $(TARGET)

$(TARGET): helloworld.c
	$(CC) $(CFLAGS) -o $(TARGET) helloworld.c

# Regla de instalación: Indica dónde se copiará el binario en el sistema
install: $(TARGET)
	install -D -m 755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

# Regla de limpieza2
clean:
	rm -f $(TARGET)