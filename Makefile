# Define the C++ compiler
CXX = g++
# Define compilation flags
CXXFLAGS = -std=c++17 -g -Wall -I. -Isrc/app/encryptDecrypt -Isrc/app/fileHandling -Isrc/app/processes

# Define targets
MAIN_TARGET = encrypt_decrypt
CRYPTION_TARGET = cryption

# List of source files for the main target
MAIN_SRC = main.cpp \
           src/app/processes/ProcessManagement.cpp \
           src/app/fileHandling/IO.cpp \
           src/app/fileHandling/ReadEnv.cpp \
           src/app/encryptDecrypt/Cryption.cpp

# List of source files for the cryption target
CRYPTION_SRC = src/app/encryptDecrypt/CryptionMain.cpp \
               src/app/encryptDecrypt/Cryption.cpp \
               src/app/fileHandling/IO.cpp \
               src/app/fileHandling/ReadEnv.cpp

# Object files are derived from source files
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
CRYPTION_OBJ = $(CRYPTION_SRC:.cpp=.o)

# Default target: build both main and cryption targets
all: $(MAIN_TARGET) $(CRYPTION_TARGET)

# Rule to build the main target executable
$(MAIN_TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to build the cryption target executable
$(CRYPTION_TARGET): $(CRYPTION_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Pattern rule to compile .cpp files to .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up: remove object files and executables
clean:
	rm -f $(MAIN_OBJ) $(CRYPTION_OBJ) $(MAIN_TARGET) $(CRYPTION_TARGET)

# .PHONY targets are not actual files
.PHONY: clean all
