CC=/usr/bin/g++
MCC=/usr/bin/x86_64-w64-mingw32-g++
CFLAGS=-Wall -static

all: 2048_Linux_amd64 2048_windows_terminal_with_ANSI_amd64
  
2048_Linux_amd64: 2048.cpp
	$(CC) $(CFLAGS) $< -o $@  

2048_windows_terminal_with_ANSI_amd64: 2048.cpp  
	$(MCC) $(CFLAGS) $< -o $@  

clean:  
	rm -f 2048_*