
// #include <iostream>
// #include <cstdlib>
// #include <pthread.h>
 
// using namespace std;
 
// #define NUM_THREADS     5
 
// struct thread_data{
//    int  thread_id;
//    char *message;
// };
 
// void *PrintHello(void *threadarg)
// {
//    struct thread_data *my_data;
 
//    my_data = (struct thread_data *) threadarg;
 
//    cout << "Thread ID : " << my_data->thread_id ;
//    cout << " Message : " << my_data->message << endl;
 
//    pthread_exit(NULL);
// }
 
// int main ()
// {
//    pthread_t threads[NUM_THREADS];
//    struct thread_data td[NUM_THREADS];
//    int rc;
//    int i;
 
//    for( i=0; i < NUM_THREADS; i++ ){
//       cout <<"main() : creating thread, " << i << endl;
//       td[i].thread_id = i;
//       td[i].message = (char*)"This is message";
//       rc = pthread_create(&threads[i], NULL,
//                           PrintHello, (void *)&td[i]);
//       if (rc){
//          cout << "Error:unable to create thread," << rc << endl;
//          exit(-1);
//       }
//    }
//    pthread_exit(NULL);
// }



#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
 
using namespace std;
 
#define NUM_THREADS     5
 
void *wait(void *t)
{
   int i;
   long tid;
 
   tid = (long)t;
 
   sleep(1);
   cout << "Sleeping in thread " << endl;
   cout << "Thread with id : " << tid << "  ...exiting " << endl;
   pthread_exit(NULL);
}
 
int main ()
{
   int rc;
   int i;
   pthread_t threads[NUM_THREADS];
   pthread_attr_t attr;
   void *status;
 
   // 初始化并设置线程为可连接的（joinable）
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
 
   for( i=0; i < NUM_THREADS; i++ ){
      cout << "main() : creating thread, " << i << endl;
      rc = pthread_create(&threads[i], NULL, wait, (void *)&i );
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
 
   // 删除属性，并等待其他线程
   pthread_attr_destroy(&attr);
   for( i=0; i < NUM_THREADS; i++ ){
      rc = pthread_join(threads[i], &status);
      if (rc){
         cout << "Error:unable to join," << rc << endl;
         exit(-1);
      }
      cout << "Main: completed thread id :" << i ;
      cout << "  exiting with status :" << status << endl;
   }
 
   cout << "Main: program exiting." << endl;
   pthread_exit(NULL);
}
