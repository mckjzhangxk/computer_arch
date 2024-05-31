#include <stdio.h>
#include "include//vector.h"

/*本程序演示如何 调用静态库，并且在clion中单步调试静态库
 *
 *
 * 如果使用命令行编译，可是使用命令
 * clang build/libvector.a link_call_static.c -o link_call_static
 *
 * 查看是否引用其他函数库
 * otool -L link_call_static
 * 查看程序的符号表
 * nm link_call_static
 *
 *
 * 如果想要调试源代码，需要注意以下2个步骤
 *
 * 1.lib库的源代码必须在工程内部
 * 2.vector库编译必须加入-g
 *
 *  注意 使用以下命令，如果build下 同时有static,shared库，
 *  会优先使用shared
 *  clang -L build  -lvector link_call_static.c  -o link_call_static
 * */

int main(){
    int x[2] = {1, 2};
    int y[2] = {3, 4};
    int z[2];

    addvec(x, y, z, 2);
    multvec(x, y, z, 2);
    printf("z = [%d %d]\n", z[0], z[1]);
    return 0;
}