#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define MAX 25// The maximum number of customer threads.

// Function definition
void *cust(void *n);
void *barb(void *);

void rwait(int sec);

sem_t wr;// semaphores
sem_t bchair;
sem_t bp;
sem_t wait2;
int finish = 0;

void *cust(void *n) {
int num = *(int *)n;

printf("Customer %d leaving for barber shop.\n", num);
rwait(2);
printf("Customer %d arrived at barber shop.\n", num);
sem_wait(&wr);
printf("Customer %d entering waiting room.\n", num);
sem_wait(&bchair);

sem_post(&wr);
printf("Customer %d waking the barber.\n", num);
sem_post(&bp);
sem_wait(&wait2);
sem_post(&bchair);
printf("Customer %d leaving barber shop.\n", num);
}

void *barb(void *j) 
{
while (!finish) 
{
printf("The barber is sleeping\n");
sem_wait(&bp);
if (!finish) 
{
printf("The barber is cutting hair\n");
rwait(2);
printf("The barber has finished cutting hair.\n");
sem_post(&wait2);
}
else {
printf("The barber is going home for the day.\n");
}
}
}
void rwait(int sec) {
int len;
// Generate a random number…
len = (int) ((1 * sec) + 1);
sleep(len);
}

int main(int argc, char *argv[]) 
{
pthread_t btid;
pthread_t tid[MAX];
int i, ncu, nc;
int Number[MAX];

printf("Enter the number of Customers : "); 
scanf("%d",&ncu) ;
printf("Enter the number of Charis : "); scanf("%d",&nc);

if (ncu > MAX) {
printf("The maximum number of Customers is %d.\n", MAX);
exit(-1);
}
for (i=0; i<MAX; i++) {
Number[i] = i;
}
  
sem_init(&wr, 0, nc);
sem_init(&bchair, 0, 1);
sem_init(&bp, 0, 0);
sem_init(&wait2, 0, 0);

pthread_create(&btid, NULL, barb, NULL);

for (i=0; i<ncu; i++) {
pthread_create(&tid[i], NULL, cust, (void *)&Number[i]);
sleep(1);
}

for (i=0; i<ncu; i++) {
pthread_join(tid[i],NULL);
sleep(1);
}

finish= 1;
sem_post(&bp); // Wake the barber
pthread_join(btid,NULL);
}



