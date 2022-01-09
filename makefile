CC = gcc
CFLAGS = -Wall

all: encrypt decrypt

encrypt: encrypt_src/main.c encrypt_src/encrypt.c encrypt_src/encrypt.h
	$(CC) $(CFLAGS) encrypt_src/main.c encrypt_src/encrypt.c -o encrypt

decrypt: decrypt_src/main.c decrypt_src/decrypt.c decrypt_src/decrypt.h
	$(CC) $(CFLAGS) decrypt_src/main.c decrypt_src/decrypt.c -o decrypt

clean:
	rm -rf encrypt decrypt
