
#include "kernel/types.h"
#include "user/user.h"

//了解操作系统的运行原理，系统调用函数的依赖关系，系统调用函数的语法
int main(int argc, char *argv[]) {
  if (argc != 2) {

    //argc表示参数的数量，argv表示控制台输入的字符串数组
    //如果用户忘记了输入，报错并返回

    fprintf(2, "用户没有输入睡眠的时间!\n");
    exit(1);

  }//0是标准输入，1是标准输出，2是错误输出
  
  //atoi函数是将输入的argv字符串转换成整数
  //argv={"program","argv"}
  //这里是argv={"sleep","3"}
  int ticks = atoi(argv[1]);

  int ret = sleep(ticks);//睡眠的系统调用
 //在kernel/sysproc.c里定义的


  exit(ret);//结束进程的系统调用

}