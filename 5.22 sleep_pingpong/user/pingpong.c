
#include "kernel/types.h"
#include "user/user.h"

char * fmtString(int pid,char* string){

  char p=pid+'0';

  char* result =malloc(sizeof(char)*(strlen(string)+2));//strlen不含\0

  memset(result,'\0',strlen(string)+2);//字符串用\0清空

  memmove(result+1,string,strlen(string));//左长右短复制字符串，从后向前复制固定长度

  result[0]=p;

  return result;
  
}



//了解操作系统的运行原理，系统调用函数的依赖关系，系统调用函数的语法
int main(int argc, char *argv[]) {

  if (argc != 1) {

    //argc表示参数的数量，argv表示控制台输入的字符串数组
    //pinpong要实现两个管道通信，打印出Pinpong
    //没有参数输入，只有一个参数arg =1
    fprintf(2, "输入指令的参数数量有误！\n");
    exit(-1);//0正常退出，-1不正常

  }//0是标准输入，1是标准输出，2是错误输出
  
  int p[2];//在pipe函数里会为p生成可用的文件描述符
  pipe(p);//基于两个整型端口，建立一个管道，是一个读写端都可以访问的缓冲区
  //p[0]是读端，p[1]是写端


  if (fork()==0){
    
    //fork创建子进程，内存地址与父不同，内容相同
    //调用fork之后，父子进程都会返回值
    //然后子进程会执行if内的代码，父进程会执行else内的代码

    //子进程返回0
    int pid = getpid();//获得子进程文件标识符
    char* s=fmtString(pid,": received pong\n");
    close(p[0]);//子进程不读，直接关闭读端
    write(p[1],s,strlen(s));//子进程向写端写字符串s
    close(p[1]);

  }else{

    //父进程返回子进程文件描述符

    close(p[1]);
    char c,buf[50];//建立一个缓冲区
    memset(buf,'\0',50);//缓冲区初始化
    int i=0;
    while(read(p[0],&c,sizeof(char))==sizeof(char)){
      buf[i++]=c;
      //当read会返回成功读取到的长度
    }

    printf("%s",fmtString(getpid(),": receive ping\n"));
    printf("%s\n",buf);//读字符串
    
    close(p[0]);
    wait(0);//等子进程执行结束

  }

  exit(0);

}