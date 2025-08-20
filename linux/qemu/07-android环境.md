## 1.下载命令行工具
- 1 .[Android Studio 仅限命令行工具](https://developer.android.com/studio?gad_source=1&gclid=CjwKCAiA9bq6BhAKEiwAH6bqoBQ-9OuXCUudMkL75c3k0n9SYgX_lKM74Jm1dBQks7PEKW2g_NI_6BoCdZgQAvD_BwE&gclsrc=aw.ds&hl=zh-cn),sdkmanager,avdmanager
- 2 .解压收新建一个android_sdk,把命令行移动到 android/comm/latest/下面
```sh
mkdir android_sdk
mv commandlinetools-linux-11076708_latest.zip android_sdk/
cd android_sdk
unzip commandlinetools-linux-11076708_latest.zip
mkdir -p cmdline-tools/latest
cd cmdline-tools/
mv bin/ latest/
mv lib/ latest/
mv source.properties latest
mv NOTICE.txt latest/

export PATH=$PATH:/home/hack520/project/android_sdk/cmdline-tools/latest/bin
```

## 2.安装sdk,emulator,platform,ndk
```sh
#查看已经安装好的
sdkmanager --list_installed

# 模拟器
sdkmanager  "emulator"  "platforms;android-30" 

# adb
sdkmanager "platform-tools"

# 系统镜像,x86版本 API30表示 android 13?
sdkmanager  "system-images;android-30;google_apis;x86_64"
#sdkmanager "system-images;android-30;google_apis;arm64-v8a"

# 编译工具链
sdkmanager --list|grep ndk
sdkmanager "ndk;28.0.12674087"
sdkmanager --list_installed

# 设置adb,NDK,emulator环境变量
export PATH=$PATH:/home/hack520/project/android_sdk/platform-tools
export PATH=$PATH:/home/hack520/project/android_sdk/emulator
```

## 3.创建模拟器
```sh
# 支持的设备
avdmanager list
# 已经创建的 android virtual device
avdmanager list avd

# -n <name> -k <package_name> -d <device_name>
# 在~/.android/avd会创建一个  <name> 文件夹
avdmanager create avd -n pixel3 -k "system-images;android-30;google_apis;x86_64" -d "pixel_3"

# 启动模拟器
emulator -avd pixel3
```

## 3.1 android网络环境
-  [参考](04-qemu-network.md)创建bridge,tap0
```sh
# 非sudo是否可以？
sudo emulator -avd pixel3 -net-tap tap0
#还可以指定-qemu参数， 还么有尝试 

# 查看tap0的status，以确定模拟器是否使用tap0,或者抓包
ip l |grep tap0

adb root
adb shell
# 设置ip，有时候需要设置 netmask,broadcast
ifconfig eth0 192.168.33.17 netmask 255.255.255.0
ifconfig eth0 broadcast 192.163.33.255
# 或者使用以下命令
# ip addr add 192.168.33.17/24 broadcast 192.168.33.255 dev eth0

# android模拟器使用eth0表的规则
# 之前ip r a添加到main,所以好像ip命令没有生效
# 有什么办法可以让模拟器 使用main?
ip rule 
ip route add default via 192.168.33.145 table eth0
# 应该是这条rule决定使用的table
# 19000:	from all fwmark 0x64/0x1ffff iif lo lookup eth0
 ip rule del pro priority 19000
# 所有路由表存放在
/data/misc/net/rt_tables
```
## 4.adb命令
```sh
# 查看启动的设备
adb devices 
adb shell
adb push server /data/local/tmp/

# 安装相关
adb install <路径/到/apk文件>
adb uninstall <包名>
# 切换root
adb root

# 已经安装的包名 与对应apk的对应关系
pm list packages -f|grep com.google.android.apps.restore

# 动态查看活动应用的进程： 如果您需要实时查看正在运行的前台应用
dumpsys activity activities | grep ResumedActivity

# com.android.chrome/org.chromium.chrome.browser.firstrun.FirstRunActivity
dumpsys window | grep -E 'mCurrentFocus|mFocusedApp'
```