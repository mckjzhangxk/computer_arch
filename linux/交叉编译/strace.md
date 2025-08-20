```sh
wget https://github.com/strace/strace/releases/download/v5.19/strace-5.19.tar.xz
tar -xvf strace-5.19.tar.xz
cd strace-5.19.tar.xz
mkdir build

# aarch64-none-linux-gnu-gcc不会引用 pthread,所以要加上 LIBS=lpthread
LIBS="-lpthread" LDFLAGS="-static" CC=aarch64-none-linux-gnu-gcc ./configure --prefix=$(pwd)/build --host=aarch64-linux-gnu
make -j4
make install


# --host 的查看方法,对应三元组<cpu>--<os>--<vendor>
aarch64-none-linux-gnu-gcc -dumpmachine


arm-linux-gnueabi-gcc -dumpspecs
# 使用自己编译的 glibc 来编译 gcc

LIBS="-lpthread" LDFLAGS="-static -L /home/hack520/project/glibc-2.35/build/build/lib" CC=arm-linux-gnueabi-gcc CFLAGS="-specs=/home/hack520/strace-5.19_arm/my.spec -I /home/hack520/project/glibc-2.35/build/build/include" ./configure --disable-gcc-Werror --prefix=$(pwd)/build --host=arm-linux-gnueabi




LIBS="-lpthread" LDFLAGS="-static -L /home/hack520/project/glibc-2.20/build/build/lib" CC=arm-linux-gnueabi-gcc CFLAGS="-specs=/home/hack520/strace-5.19_arm/my.spec -I /home/hack520/project/glibc-2.20/build/build/include" ./configure --disable-gcc-Werror --prefix=$(pwd)/build --host=arm-linux-gnueabi
```

