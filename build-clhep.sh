#!/bin/bash
set -e

# Check for argument
if [ -z "$1" ]; then
    echo "Error: Missing argument. Usage: ./build-clhep.sh <path/to/install>"
    exit 1
fi

# Check gcc version
gcc_major=$(gcc -dumpversion | cut -d. -f1)

if ! [[ "$gcc_major" =~ ^[0-9]+$ ]]; then
    echo "Error: Unable to detect GCC version."
    exit 1
fi

if [ "$gcc_major" -ge 5 ]; then
    echo "Error: GCC version $gcc_major detected, but < 5 is required for CLHEP."
    exit 1
fi

echo "GCC version check passed for CLHEP. Current version: $gcc_major"

#########################################

install_dir=$1
current_dir=$PWD

# Build CLHEP
echo "Start building CLHEP..."
cd "${current_dir}/clhep-2.0.4.4"
export CXXFLAGS="-std=c++03 -g -O2"
./configure --prefix="${install_dir}"
make -j4
make install
