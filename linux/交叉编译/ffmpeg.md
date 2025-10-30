```sh


./configure --prefix=$(pwd)/myinstall  --enable-cross-compile --arch=arm --target-os=linux --cross-prefix=arm-linux-gnueabi- --disable-doc --enable-static --disable-shared --extra-cflags="-static" --extra-ldflags="-static"
```

