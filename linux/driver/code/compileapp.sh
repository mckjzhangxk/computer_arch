#!/bin/bash
# 简单的多文件编译脚本

# 1️⃣ 设置编译器（可从外部环境传入）
CC=${CC:-gcc}   # 如果没设置CC，默认使用 gcc

# 2️⃣ 定义要编译的源文件名（不带扩展名）
items=("app_io_select" 
       "app_io_signal_app" 
       "error_code_test"
       "app_iopoll_retcode"
       "open_dev"
       "open_read_dev"
       "open_read_ioctl_dev"
       "open_timer"
       )

# 3️⃣ 遍历数组并编译
for item in "${items[@]}"; do
    src="${item}.c"
    out="${item}.app"

    if [ -f "$src" ]; then
        echo "==> 编译 $src -> $out"
        $CC "$src" -o "$out"
        if [ $? -ne 0 ]; then
            echo "❌ 编译失败: $src"
            exit 1
        fi
    else
        echo "⚠️  跳过: 找不到 $src"
    fi
done

echo "✅ 所有文件编译完成。"
