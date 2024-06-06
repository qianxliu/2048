CC=/usr/bin/g++
MCC=/usr/bin/x86_64-w64-mingw32-g++
CFLAGS=-Wall  

all: 2048_linux 2048_windows
  
2048_linux: 2048.cpp
	$(CC) $(CFLAGS) $< -o $@  

2048_windows: 2048.cpp  
	$(MCC) $(CFLAGS) $< -o $@  

clean:  
	rm -f 2048_linux 2048_windows