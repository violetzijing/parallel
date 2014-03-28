#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define NUM_THREADS 8 //number of threads
#define TOT_COUNT 10000055 //total number of iterations

float randNumGen(){

   int random_value = rand(); //Generate a random number
   float unit_random = random_value / (float) RAND_MAX; //make it between 0 and 1
   return unit_random;
}

/**
The task allocated to a thread
**/
void *doCalcs(void *thread_id)
{
   long long_tid;
   long_tid = (long)thread_id;
   
   int tid = (int)long_tid; //obtain the integer value of thread id

   //using malloc for the return variable in order make
   //sure that it is not destroyed once the thread call is finished
   float *in_count = (float *)malloc(sizeof(float));
   *in_count = 0;
   
   //get the total number of iterations for a thread
   float tot_iterations = TOT_COUNT/NUM_THREADS;
   
   int counter = 0;
   
   //calculation
   for(counter = 0;counter<tot_iterations;counter++){
      float x = randNumGen();
      float y = randNumGen();
      
      float result = sqrt((x*x) + (y*y));
      
      if(result < 1){
         *in_count += 1; //check if the generated value is inside a unit circle
      }
      
   }
   
   //get the remaining iterations calculated by thread 0
   if(tid == 0){
      float remainder = TOT_COUNT%NUM_THREADS;
      
      for(counter = 0; counter < remainder; counter++){
      float x = randNumGen();
      float y = randNumGen();
      
      float result = sqrt((x*x) + (y*y));
      
      if(result<1){
         *in_count+=1; //check if the generated value is inside a unit circle
      }
      
   }
   }


   //printf("In count from #%d : %f\n",tid,*in_count);
   
   pthread_exit((void *)in_count); //return the in count
}

int main(int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   void *status;
   float tot_in=0;
   
   for(t = 0; t < NUM_THREADS; t++){
     rc = pthread_create(&threads[t], NULL, doCalcs, (void *)t);
     if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
       }
     }

   //join the threads
   for(t = 0; t < NUM_THREADS; t++){
           
      pthread_join(threads[t], &status);
      //printf("Return from thread %ld is : %f\n",t, *(float*)status);
      
      tot_in += *(float*)status; //keep track of the total in count
     
     }
     printf("Value for Pi is %f \n",1, 4*(tot_in/TOT_COUNT));
   
   /* Last thing that main() should do */
   pthread_exit(NULL);
}
