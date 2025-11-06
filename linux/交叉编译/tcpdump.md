```sh
# 先安装 libpcap
git clone https://github.com/the-tcpdump-group/libpcap
CC=aarch64-buildroot-linux-uclibc-gcc  ./configure --prefix=$(pwd)/myinstall --host=aarch64-buildroot-linux-uclibc —disable-shared
make install



# 安装 tcpdump, PKG_CONFIG_LIBDIR来自 libpcap 目录
git clone https://github.com/the-tcpdump-group/tcpdump
CC=aarch64-buildroot-linux-uclibc-gcc CFLAGS=-static PKG_CONFIG_LIBDIR=/home/hack520/project/libpcap/myinstall/lib/pkgconfig ./configure --prefix=$(pwd)/myinstall --host=aarch64-buildroot-linux-uclibc --disable-local-libpcap
make install
```