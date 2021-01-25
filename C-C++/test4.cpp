// #include <iostream>
// #include <cstdlib>
// #include <pthread.h>

// using namespace std;

// #define NUM_THREADS     5

// void *PrintHello(void *threadid)
// {
//    // 对传入的参数进行强制类型转换，由无类型指针变为整形数指针，然后再读取
//    int tid = *((int*)threadid);
//    cout << "Hello Runoob! 线程 ID, " << tid << endl;
//    pthread_exit(NULL);
// }

// int main()
// {
//    pthread_t threads[NUM_THREADS];
//    int indexes[NUM_THREADS];// 用数组来保存i的值
//    int rc;
//    int i;
//    for( i=0; i < NUM_THREADS; i++ ){
//       cout << "main() : 创建线程, " << i << endl;
//       indexes[i] = i; //先保存i的值
//       // 传入的时候必须强制转换为void* 类型，即无类型指针        
//       rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&(indexes[i]));
//       if (rc){
//          cout << "Error:无法创建线程," << rc << endl;
//          exit(-1);
//       }
//    }
//    pthread_exit(NULL);
// }


#include "stdafx.h"
#include <windows.h>
#include <iostream>
 
using namespace std;
 
//线程函数
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    for (int i = 0; i < 5; ++ i)
    {
        cout << "子线程:i = " << i << endl;
        Sleep(100);
    }
    return 0L;
}
 
int main()
{
    //创建一个线程
    HANDLE thread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
    //关闭线程
    CloseHandle(thread);
 
    //主线程的执行路径
    for (int i = 0; i < 5; ++ i)
    {
        cout << "主线程:i = " << i << endl;
        Sleep(100);
    }
 
    return 0;
}
