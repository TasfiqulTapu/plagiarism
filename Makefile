# Define the target executable
TARGET = main

# Define the source files
SRCS = main.c deque.c hashmap.c argparse.c preprocessor.c detection.c 

# Default target: builds the executable
all: $(TARGET)

# Rule to build the executable using the single gcc command
$(TARGET): $(SRCS)
	gcc $(SRCS) -o $(TARGET) -lm

# Other builds
# win: x86_64-w64-mingw32-gcc main.c deque.c hashmap.c argparse.c preprocessor.c detection.c  -o plagiarism_windows_x86_64
# linux: gcc main.c deque.c hashmap.c argparse.c preprocessor.c detection.c -lm -o plagiarism_ubuntu_x86_64

# --- Clean target ---
clean:
	rm -f $(TARGET)