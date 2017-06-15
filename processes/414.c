#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
int thread_flag;
pthread_cond_t thread_flag_cv;
pthread_mutex_t thread_flag_mutex;
int value;

void initialize_flag()
{
 pthread_mutex_init(&thread_flag_mutex, NULL);
 pthread_cond_init(&thread_flag_cv, NULL);
 thread_flag = 0;
}

void do_work()
{
 value++;
 printf("+1: %d\n", value);
 sleep(1);
}

void* thread_function(void* thread_arg) {
 while (1) {
     pthread_mutex_lock(&thread_flag_mutex);
     while(!thread_flag)
     {
         value--;
         printf("-1: %d\n", value);
         pthread_cond_wait(&thread_flag_cv, &thread_flag_mutex);
     }
     pthread_mutex_unlock(&thread_flag_mutex); 
     do_work();	 
 }
 return NULL;
}

void set_thread_flag(int flag_value) {
 pthread_mutex_lock(&thread_flag_mutex);
 thread_flag = flag_value;
 pthread_cond_signal(&thread_flag_cv);
 pthread_mutex_unlock(&thread_flag_mutex);
}

int main(int argc, char* argv[])
{
 pthread_t thread;
 int status;	
 initialize_flag();
 status=pthread_create(&thread, NULL, &thread_function, NULL);
 if(!status)
 {
      printf("Success\n");
 }
 while(1)
 {   
     value=value*2;
     printf("x2: %d\n", value);
     thread_flag=rand()%2;
     pthread_cond_broadcast(&thread_flag_cv); // cv vs broadcast
     sleep(1);
 }

 status=pthread_join(thread, NULL);
 if (!status)
 {
     printf("joined");
 }
 return 0;
}
