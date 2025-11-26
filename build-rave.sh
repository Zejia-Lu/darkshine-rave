#!/bin/bash
set -e

# Check for argument
if [ -z "$1" ]; then
    echo "Error: Missing argument. Usage: ./build-rave.sh <path/to/install>"
    exit 1
fi

# Check gcc version
gcc_version=$(gcc -dumpversion | cut -d. -f1)

if ! [[ "$gcc_version" =~ ^[0-9]+$ ]]; then
    echo "Error: Unable to detect GCC version."
    exit 1
fi

if [ "$gcc_version" -lt 5 ]; then
    echo "Error: GCC version $gcc_version detected, but >= 5 is required."
    exit 1
fi

echo "GCC version check passed. Current version: $gcc_version"

#########################################

install_dir=$1
current_dir=$PWD

# Build CLHEP
echo "Start building CLHEP..."
cd ${current_dir}/clhep-2.0.4.4
export CXXFLAGS="-std=c++03 -g -O2"
./configure --prefix=${install_dir}
make -j4
make install

# Build RAVE
echo "Start building Rave..."
cd ${current_dir}/rave-0.6.9
export CXXFLAGS="-std=c++03 -g -O2"
./configure --with-clhep=${install_dir} --with-clhep_vector-libpath=${install_dir}/lib --with-clhep_matrix-libpath=${install_dir}/lib --prefix=${install_dir} --disable-java
make -j4
make install
