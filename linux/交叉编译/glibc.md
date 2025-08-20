```sh
wget https://ftp.gnu.org/gnu/glibc/glibc-2.3.5.tar.gz
tar -xvf glibc-2.3.5.tar.gz
cd glibc-2.3.5
mkdir build
mkdir install

cd build
CC=arm-linux-gnueabi-gcc ../configure --prefix=$(pwd)/build --host=arm-linux-gnueabi --enable-kernel=3.2.0 --enable-stack-protector=yes


CC=arm-linux-gnueabi-gcc ../configure --prefix=$(pwd)/build --host=arm-linux-gnueabi --enable-kernel=3.0.0 --enable-stackguard-randomization=yes

make -j4
make install


# --host 的查看方法,对应三元组<cpu>--<os>--<vendor>
arm-linux-gnueabi-gcc -dumpmachine
```

