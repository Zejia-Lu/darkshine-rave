#!/bin/bash
set -e

# Check for argument
if [ -z "$1" ]; then
    echo "Error: Missing argument. Usage: ./build-rave.sh <path/to/install>"
    exit 1
fi

# Check gcc version
gcc_major=$(gcc -dumpversion | cut -d. -f1)

if ! [[ "$gcc_major" =~ ^[0-9]+$ ]]; then
    echo "Error: Unable to detect GCC version."
    exit 1
fi

if [ "$gcc_major" -lt 5 ]; then
    echo "Error: GCC version $gcc_major detected, but >= 5 is required for Rave."
    exit 1
fi

echo "GCC version check passed for Rave. Current version: $gcc_major"

#########################################

install_dir=$1
current_dir=$PWD

# Ensure CLHEP is available
if [ ! -d "${install_dir}/include/CLHEP" ] || [ ! -d "${install_dir}/lib" ]; then
    echo "Error: CLHEP installation not found in ${install_dir}. Please run build-clhep.sh first."
    exit 1
fi

# Build RAVE
echo "Start building Rave..."
cd "${current_dir}/rave-0.6.9"
export CXXFLAGS="-std=c++03 -g -O2"
./configure --with-clhep="${install_dir}" --with-clhep_vector-libpath="${install_dir}/lib" --with-clhep_matrix-libpath="${install_dir}/lib" --prefix="${install_dir}" --disable-java
make -j4
make install
