# DarkSHINE-RAVE

This is the rave package along with the clhep package that is needed for the DarkSHINE vertexing.

## Usage
```
# Use gcc version < 5
./build-clhep.sh /path/to/install
# Switch to gcc version >= 5
./build-rave.sh /path/to/install
```

**Note**
1. The old clhep package seems not to compile with gcc version >= 5.
2. On the other hand, Rave needs to be compiled with gcc version >= 5, so that it can be used by the darkshine framework.
3. The two `/path/to/install` should be the same, or you should modify build-rave.sh by yourself.
