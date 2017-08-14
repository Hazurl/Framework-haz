##############################################
#                     SRC                    #
##############################################
# All directories to build (inside src/)
DIR := Interface
DIR += Benchmark
DIR += Tools 
DIR += GameObject GameObject/2D GameObject/Component GameObject/Component/2D
DIR += Geometry Geometry/2D
DIR += Serialization
# Directories with src/ prefix
SRC_DIR := $(addprefix src/,$(DIR))
# All .cpp files
SRC := $(foreach d,$(SRC_DIR),$(wildcard $(d)/*.cpp))

##############################################
#                    MAIN                    #
##############################################
# Main directories
MAIN_DIR := src/
# Main file 
# Pick one : main_go.cpp, main_benchmark.cpp, main_serialization.cpp
MAIN := main_go.cpp
# Main path
MAIN_PATH := $(MAIN_DIR)/$(MAIN)
# Main .o
MAIN_OBJ := $(patsubst %.cpp,build/main/%.o,$(MAIN))

##############################################
#                  BUILD/.o                  #
##############################################
# Name of the executable
DEST := build/main_app
# Build Directories
BUILD_DIR := build build/main build/src $(addprefix build/src/,$(SRC_DIR)) build/lib build/shared $(addprefix build/shared/,$(SRC_DIR))
# .o files
OBJ := $(patsubst %.cpp,build/src/%.o,$(SRC))
# Shared files
SHARED_OBJ := $(patsubst %.cpp,build/shared/%.o,$(SRC))
# Lib destination
DEST_LIB := build/lib/libframeworkHaz.so
# Include folders
INCLUDE_FOLDER := include/

##############################################
#                    FLAGS                   #
##############################################
# C++ optimsation level
OPTIM := -O2
# C++ flags
FLAGS := -std=c++17 -g3 -Wall -Wextra -Wno-pmf-conversions
# C++ librairie
LIBS := 
# Header include folder
INCLUDE := -I ./include
# Makefile flags
MAKEFLAGS += --no-print-directory

all: $(DEST)

# Main build task
# Compile each file and link them
$(DEST): $(BUILD_DIR) $(OBJ) $(MAIN_OBJ)
	@echo "\033[32m\033[1m:: Linking of all objects\033[0m"
	@g++ $(INCLUDE) $(FLAGS) $(OBJ) $(MAIN_OBJ) -o $(DEST) $(LIBS)
	@echo -n "\033[34m"
	@echo "---------------"
	@echo "Build finished!"
	@echo "---------------"
	@echo -n "\033[0m"

# Compile a file into a object
build/src/%.o: %.cpp
	@echo "\033[1m:: Building" "$<" "\033[0m"
	@g++ -c $(INCLUDE) $(OPTIM) $(FLAGS) -o "$@" "$<"

# Compile a file into a object
$(MAIN_OBJ): $(MAIN_PATH)
	@echo "\033[1m:: Building Main" "\033[0m"
	@g++ -c $(INCLUDE) $(OPTIM) $(FLAGS) -o "$@" "$<"

# Make build folders
$(BUILD_DIR):
	@mkdir -p $@

# Clean every build files by destroying the build/ folder.
clean:
	@echo "Removing build folder..."
	@rm -rf build
	@echo -n "\033[34m"
	@echo "----------------"
	@echo "Project  Cleaned"
	@echo "----------------"
	@echo -n "\033[0m"

# Run the program
run: $(DEST)
	@echo -n "\033[34m"
	@echo "----------------"
	@echo "      Run       "
	@echo "----------------"
	@echo -n "\033[0m"
	@$(DEST)
	@echo -n "\033[34m"
	@echo "----------------"
	@echo "      Stop      "
	@echo "----------------"
	@echo -n "\033[0m"

# Equivalent of make clean and make run
again:
	@make clean
	@make run

# Use fgen
file:
	fgen -p=include/$(dir)/$(name).hpp -t=fgenTemplate/hppTemplate.hpp class=$(name) define=$(name)
	fgen -p=src/$(dir)/$(name).cpp -t=fgenTemplate/cppTemplate.cpp class=$(name) include=$(dir)/$(name).hpp

# Compile to shared objects
build/shared/%.o: %.cpp
	@echo "\033[1m:: Building shared" "$<" "\033[0m"
	@g++ $(INCLUDE) $(OPTIM) $(FLAGS) -c -fPIC -o "$@" "$<"

# Compile librairy
$(DEST_LIB): $(BUILD_DIR) $(SHARED_OBJ)
	@echo "\033[32m\033[1m:: Linking of all objects into librairy\033[0m"
	@g++ $(INCLUDE) $(FLAGS) -shared -o $(DEST_LIB) $(SHARED_OBJ) $(LIBS)
	@echo -n "\033[34m"
	@echo "-----------------------"
	@echo "Library build finished!"
	@echo "-----------------------"
	@echo -n "\033[0m"

# Mak thie librairy
lib: $(DEST_LIB)

# Install the framework into /usr
install: lib
	@echo "Copy lib to /usr/lib ..."
	@cp $(DEST_LIB) /usr/lib/
	@mkdir /usr/include/frameworkHaz
	@echo "Copy includes files to /usr/include/frameworkHaz ..."
	@cp -a $(INCLUDE_FOLDER)/. /usr/include/frameworkHaz/
	@echo -n "\033[34m"
	@echo "------------------"
	@echo "Library installed!"
	@echo "------------------"
	@echo -n "\033[0m"

clean-lib:
	rm /usr/lib/libframeworkHaz.so
	rm -rf /usr/include/frameworkHaz