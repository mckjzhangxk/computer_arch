```sh
git clone https://github.com/landley/toybox.git

CC=gcc LDFLAGS="--static" CROSS_COMPILE=aarch64-none-linux-gnu- PREFIX=$(pwd)/install make defconfig
CC=gcc LDFLAGS="--static" CROSS_COMPILE=aarch64-none-linux-gnu- PREFIX=$(pwd)/install make
CC=gcc LDFLAGS="--static" CROSS_COMPILE=aarch64-none-linux-gnu- PREFIX=$(pwd)/install make install

```