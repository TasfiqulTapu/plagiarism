# Define the target executable
TARGET = main

# Define the source files
SRCS = main.c deque.c argparse.c preprocessor.c

# Default target: builds the executable
all: $(TARGET)

# Rule to build the executable using the single gcc command
$(TARGET): $(SRCS)
	gcc $(SRCS) -o $(TARGET)

# --- Clean target ---
clean:
	rm -f $(TARGET)