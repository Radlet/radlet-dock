apt-get -qy install autoconf automake libtool curl make g++ unzip git
git clone https://github.com/protocolbuffers/protobuf.git
cd protobuf
git submodule update --init --recursive
./autogen.sh
./configure
make
make check
make install
ldconfig
rm -rf protobuf
