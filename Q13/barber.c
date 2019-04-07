#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define MAX 25// The maximum number of customer threads.

// Function definition
void *cust(void *n);// Functions
void *barb(void *);
void rwait(int sec);

//semaphores
sem_t wr; // limits maximum number of customers to wait
sem_t bchair;//mutually exclusive access
sem_t bp;//allows barber to sleep till customer arrives
sem_t wait2;//customer waits for his chance
int finish = 0;

void *cust(void *n) 
{
int num = *(int *)n;
printf("Customer No. %d leaving for barber shop.\n", num);
rwait(2);//takes random time to arrive
printf("Customer No. %d arrived at barber shop.\n", num);
sem_wait(&wr);//wait to enter
printf("Customer No. %d entering waiting room.\n", num);
sem_wait(&bchair);//wait to become free

sem_post(&wr);//waiting status
//wake the barber  
printf("Customer No. %d waking the barber.\n", num);
sem_post(&bp);

sem_wait(&wait2);//wait for the job to finish
sem_post(&bchair);//leave chair
printf("Customer %d leaving barber shop.\n", num);
}

void *barb(void *j) 
{
while (!finish) //condition provided that barber can tell if customers are on the way
{
printf("The barber is sleeping\n");//sleep till customer wakes up the barber
sem_wait(&bp);
if (!finish) 
{
printf("The barber is cutting hair\n");
rwait(2);//takes random time to cut
printf("The barber has finished cutting hair.\n");
sem_post(&wait2);// release cutomer thread
}
else {
printf("The barber has finished his job\n");
}
}
}
void rwait(int sec) 
{
int len;
len = (int) ((1 * sec) + 1);// random number…
sleep(len);
}

int main(int ar, char *arr[]) 
{
pthread_t bt;
pthread_t ti[MAX];
int i, ncu, nc;
int Num[MAX];

printf("Enter the number of Customers : "); 
scanf("%d",&ncu) ;
printf("Enter the number of Chairs : "); 
scanf("%d",&nc);

if (ncu > MAX) {
printf("The maximum number of Customers is %d.\n", MAX);
exit(-1);
}
for (i=0; i<MAX; i++) 
{
Num[i] = i;//initialise array
}
  
//initial values of semaphores 
sem_init(&wr, 0, nc);
sem_init(&bchair, 0, 1);
sem_init(&bp, 0, 0);
sem_init(&wait2, 0, 0);
pthread_create(&bt, NULL, barb, NULL);//barber

for (i=0; i<ncu; i++) 
{
pthread_create(&ti[i], NULL, cust, (void *)&Num[i]);//customers
sleep(1);
}

for (i=0; i<ncu; i++)
{
pthread_join(ti[i],NULL);//join threads
sleep(1);
}
//exit the barber thread when all customers have been serviced.
finish= 1;
sem_post(&bp); // Wake the barber
pthread_join(bt,NULL);
}



