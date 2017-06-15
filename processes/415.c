#include <pthread.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0

int thread_flag;
pthread_mutex_t thread_flag_mutex;

void initialize_flag() {
 pthread_mutex_init(&thread_flag_mutex, NULL);
 thread_flag = 0;
}

void do_work()
{
 printf("Doing work\n");
 sleep(1);
}
/* Если флаг установлен, многократно вызывается функция do_work().
   В противном случае цикл работает вхолостую. */
void* thread_function(void* thread_arg) {
 while (1) {
  int flag_is_set;
  /* Защищаем флаг с помощью исключающего семафора. */
  pthread_mutex_lock(&thread_flag_mutex);
  flag_is_set = thread_flag;
  pthread_mutex_unlock(&thread_flag_mutex);
  if (flag_is_set)
   do_work();
  /* Если флаг не установлен, ничего не делаем. Просто переходим
     на следующую итерацию цикла. */
 }
 return NULL;
}

/* Задаем значение флага равным FLAG_VALUE. */
void set_thread_flag(int flag_value) {
 /* Защищаем флаг с помощью исключающего семафора. */
 pthread_mutex_lock(&thread_flag_mutex);
 thread_flag = flag_value;
 pthread_mutex_unlock(&thread_flag_mutex);
}
int main(int argc, char *argv[])
{
 initialize_flag();
 pthread_t thread;
 int status;
 status = pthread_create(&thread, NULL, thread_function, NULL);
 if (status)
     {
         printf("can not create a thread");
     }
 int tmp_val=rand()%2;
 set_thread_flag(tmp_val);
 printf("main\n");  
}
