install_dir=$1

current_dir=$PWD
export CXXFLAGS="-std=c++03 -g -O2"

# Build CLHEP
cd ${current_dir}/clhep-2.0.4.4
./configure --prefix=${install_dir}
make -j4 && make install

# Build RAVE
cd ${current_dir}/rave-0.9.6
./configure --with-clhep=../clhep-2.0.4.4/ --with-clhep_vector-libpath=../clhep-2.0.4.4/lib --with-clhep_matrix-libpath=../clhep-2.0.4.4/lib --prefix=${install_dir} --disable-java
make -j4 && make install