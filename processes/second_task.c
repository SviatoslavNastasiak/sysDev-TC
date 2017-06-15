#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//#include <conio.h>

#define SUCCESS 0
#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD -12
#define BAD_INPUT -13

typedef struct data_struct
{
 int id;
 int input;
 int output;
} data_struct_t;

void* sum(void* args);
int ch_attr(pthread_attr_t* attr);

int main()
{
 pthread_attr_t tattr;
 int size;
 int val;
 pthread_t thread;
 int status;
 int status_addr;
 data_struct_t arg;
 printf("please, enter a value:\n");
 scanf("%d", &(arg.input));

 status = ch_attr(&tattr);
 status = pthread_create(&thread, &tattr, sum, (void*) &arg);
 if (status != 0)
     {
      printf("Main error: can't create a thread\n");
      exit(ERROR_CREATE_THREAD);
     }
 printf("Main thread!\n");
 status = pthread_join(thread, (void**)&status_addr);
 if (status!=SUCCESS)
     {
      printf("main error: can't join a thread\n");
      exit(ERROR_JOIN_THREAD);
     }
 printf("Joined!\n");
 printf("out output is %d\n", arg.output);
// system("pause");
 return 0;
}

void* sum(void* args)
{
 data_struct_t* arg = (data_struct_t* ) args;
 int rt;
 if (arg->input == 0)
     {
      return NULL;
     }
 rt=((1+arg->input)*((arg->input))/2);
 arg->output = rt;

 return SUCCESS;
}

int ch_attr(pthread_attr_t* attr)
{
 //pthread_attr_t *arg = (p_thread_attr_t*) attr
 int rv;
 int value;
 int size;
 void* stackbase;
 printf("please, enter a value: size of stack\n");
 scanf("%d", &(size));
 printf("bla");
 size = value;
 stackbase = (void*) malloc(size);
 rv = pthread_attr_init(attr); // firstly set the default values
 rv = pthread_attr_setstack(attr,malloc(size), size);
 return SUCCESS;
}
