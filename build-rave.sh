install_dir=$1

current_dir=$PWD
export CXXFLAGS="-std=c++03 -g -O2"

# Build CLHEP
cd ${current_dir}/clhep-2.0.4.4
./configure --prefix=${install_dir}
make -j4 && make install

# Build RAVE
cd ${current_dir}/rave-0.6.9
./configure --with-clhep=${install_dir} --with-clhep_vector-libpath=${install_dir}/lib --with-clhep_matrix-libpath=${install_dir}/lib --prefix=${install_dir} --disable-java
make -j4 && make install