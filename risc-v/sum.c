//riscv64-unknown-elf-gcc -S -Og  sum.c

// demo1 
// 函数的调用与返回
// 临时寄存器的保存

// int sum(int n){
//     int s=0;
//     for (int i=0;i<n;i++){
//         s+=i;
//     }
//     return s;
// }

// int sum_and_double(int n){
//     int r= sum(n);
//     return r*2;
// }

//demo2
// int dummymain(int argc,char ** argv){
//    int total_sum=0;
//    for (int i = 0; i < argc; ++i) {
//         // total_sum+=strlen(argv[i]);
//         printf("%s\n",argv[i]);
//    }
//    return total_sum;
// }
//demo3
// int dummyexec(){
//    int argc=3;
//    char * argv[]={
//            [0]="ls",
//            [1]="-p",
//            [2]="-a"
//    };
//    return dummymain(argc,argv);

// }

struct Entity
{
    int a;
    long b;
    short c;
};


int EntityParam(struct Entity x){
    printf("%d %d %d\n",x.a,x.b,x.c);
    return 0;
}

int EntityParamCaller(){
    struct Entity x;
    x.a=100;
    x.b=10;
    x.c=1;
    EntityParam(x);
}
//
//int fib(int n){
//    if(n<=2)
//        return 1;
//    return fib(n-1)+ fib(n-2);
//}