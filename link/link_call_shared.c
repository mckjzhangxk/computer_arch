#include <stdio.h>
#include "include/vector.h"
#include "unistd.h"
/*
 * 如果使用命令行编译，可是使用命令
 *  clang build/libvector.dylib link_call_shared.c -o link_call_shared
 * 查看是否引用其他函数库
 * otool -L link_call_shared
 * 查看程序的符号表
 * nm link_call_shared
 *          和link_call_shared比较，可以看出link_call_shared完全不知道addcnt,multcnt两个变量的存在
 *
 * 如果想要调试源代码，需要注意以下2个步骤
 *
 * 1.lib库的源代码必须在工程内部
 * 2.vector库编译必须加入-g
 * 3.libvector.dylib.dSYM一定不要删除，这是动态库的符号表
 *
 *  注意 使用以下命令，如果build下 同时有static,shared库，
 *  会优先使用shared
 *  clang -L build -lvector link_call_shared.c -o link_call_shared
 * */
int main(){
    int x[2] = {1, 2};
    int y[2] = {3, 4};
    int z[2];

    addvec(x, y, z, 2);
    multvec(x, y, z, 2);
    printf("z = [%d %d]\n", z[0], z[1]);
    pause();
    return 0;
}