export CXXFLAGS="-std=c++03 -g -O2"
cd rave-0.6.9
./configure --with-clhep=../clhep-2.0.4.4/ --with-clhep_vector-libpath=../clhep-2.0.4.4/lib --with-clhep_matrix-libpath=../clhep-2.0.4.4/lib --prefix=../install --disable-java
