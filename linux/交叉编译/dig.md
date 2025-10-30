
```sh
# 先编译 libuv
git clone https://github.com/libuv/libuv.git
mkdir build
CC=arm-linux-gnueabi-gcc ./configure --prefix=$(pwd)/build --host=arm-linux-gnueabi --enable-static --enable-shared=no

make -j4
make install


# 安装openssl

# 从下面网站下载 1.1.1t 版本
https://openssl-library.org/source/old/1.1.1/


tar -xvf openssl-3.4.2.tar.gz
mkdir build

./Configure linux-armv4 --cross-compile-prefix=arm-linux-gnueabi- --prefix=$(pwd)/build no-shared no-static-engine

make -j4
make install
```

```sh
wget https://downloads.isc.org/isc/bind9/9.18.24/bind-9.18.24.tar.xz
tar -xvf bind-9.18.24.tar.xz
mkdir build

# 配置 libuv,libopenssl 库， 让 配置通过
export PKG_CONFIG_PATH=/home/hack520/project/libuv/build/lib/pkgconfig:/home/hack520/project/openssl-3.4.2/build/lib/pkgconfig

# 配置

# LDFLAGS：指定的原因是 编译 dig 的时候， dig依赖 isc.so,iso.so 依赖 openssl,这样默认没有设置 SSL 路径
# LIBS 设置的 原因同上
CC=arm-linux-gnueabi-gcc \
LDFLAGS=-L/home/hack520/project/openssl-3.4.2/build/lib LIBS="-lssl -lcrypto -ldl -latomic" \
./configure --prefix=$(pwd)/build \
            --host=arm-linux-gnueabi \
            --disable-doh --disable-linux-caps \
            --with-libxml2=no --with-zlib=no

#  bin/dig/Makefile

# dig$(EXEEXT): $(dig_OBJECTS) $(dig_DEPENDENCIES) $(EXTRA_dig_DEPENDENCIES)
#         @rm -f dig$(EXEEXT)
#         $(AM_V_CCLD)$(LINK) $(dig_OBJECTS) $(dig_LDADD) $(LIBS)

make -j4
make install


# --host 的查看方法,对应三元组<cpu>--<os>--<vendor>
arm-linux-gnueabi-gcc -dumpmachine
```
