
```sh
# 先编译 libuv
git clone https://github.com/libuv/libuv.git
mkdir build
CC=arm-linux-gnueabi-gcc ./configure --prefix=$(pwd)/build --host=arm-linux-gnueabi --enable-static


make -j4
make install


# 安装openssl

wget https://github.com/openssl/openssl/releases/download/openssl-3.4.2/openssl-3.4.2.tar.gz

tar -xvf openssl-3.4.2.tar.gz
mkdir build

./Configure linux-armv4 --cross-compile-prefix=arm-linux-gnueabi- --prefix=$(pwd)/build 

make -j
make install
```

```sh
wget https://downloads.isc.org/isc/bind9/9.18.24/bind-9.18.24.tar.xz
tar -xvf bind-9.18.24.tar.xz
mkdir build


export PKG_CONFIG_PATH=/home/hack520/project/libuv/build/lib/pkgconfig:/home/hack520/project/openssl-3.4.2/build/lib/pkgconfig

CC=arm-linux-gnueabi-gcc ./configure --prefix=$(pwd)/build --host=arm-linux-gnueabi --disable-doh --disable-linux-caps --with-libxml2=no --with-zlib=no --enable-static 



make -j4
make install


# --host 的查看方法,对应三元组<cpu>--<os>--<vendor>
arm-linux-gnueabi-gcc -dumpmachine
```
