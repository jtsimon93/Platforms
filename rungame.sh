#!/bin/bash

# Stop on any error
set -e

# Script to build and run the Platforms game
SCRIPT_DIR=$(dirname "$0")
cd "$SCRIPT_DIR"

# Color definitions
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}Building Platforms game...${NC}"

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    echo -e "${GREEN}Creating build directory...${NC}"
    mkdir -p build
fi

# Navigate to build directory
cd build

# Run CMake if CMakeCache.txt doesn't exist
if [ ! -f "CMakeCache.txt" ]; then
    echo -e "${GREEN}Running CMake...${NC}"
    cmake .. -G Ninja
fi

# Build the project with make
echo -e "${GREEN}Compiling...${NC}"
cmake --build .

# Run the game
echo -e "${GREEN}Starting game...${NC}"
./Platforms

echo -e "${YELLOW}Game exited.${NC}"
