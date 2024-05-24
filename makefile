# Nom de l'exécutable
TARGET = gestion_sport

# Compilateur et options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Liste des fichiers objets
OBJ = main.o athlete.o performance.o file_utils.o stats.o

# Règle par défaut
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Règle pour compiler main.c
main.o: main.c 
	$(CC) $(CFLAGS) -c main.c

# Règle pour compiler athlete.c
athlete.o: athlete.c header.h
	$(CC) $(CFLAGS) -c athlete.c

# Règle pour compiler performance.c
performance.o: performance.c header.h
	$(CC) $(CFLAGS) -c performance.c

# Règle pour compiler file_utils.c
file_utils.o: file_utils.c header.h
	$(CC) $(CFLAGS) -c file_utils.c

# Règle pour compiler stats.c
stats.o: stats.c stats.h performance.h
	$(CC) $(CFLAGS) -c stats.c

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(TARGET) $(OBJ)

# Règle pour nettoyer seulement les fichiers objets
clean_obj:
	rm -f $(OBJ)
