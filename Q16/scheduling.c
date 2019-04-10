#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
struct Pro
{
int prono; //struct definition
int arrt; 
int burt; 
};
int main()
{

int tp; //Total Processes to be encountered
printf("\nEnter the Total Number of Processes:\n");//process initiaisation
scanf("%d",&tp);
struct Pro p[tp];


int minart; //to compute minimum arrival time
int t1=0; //Time variable
int l1,l2; //Loop variables used in sorting and other functions
float totalwaitt=0; //to compute Total Waiting Time
float totalturnt=0; //to compute Total Turnaround Time 
float avgwt; //to compute Average Waiting Time
float avgturnt; //to compute Average Turnaround Time

//DETAILS OF THE PROCESS
int burst[tp];// to store burst time
printf("Enter Details of %d Processes\n\n",tp);
for(l1=0;l1<tp;l1++)
{
printf("Enter the process id number: \t");
scanf("%d",&p[l1].prono);
printf("Enter Arrival Time:\t");
scanf("%d",&p[l1].arrt);
printf("Enter Burst Time: \t");
scanf("%d",&p[l1].burt);
burst[l1]=p[l1].burt;
printf("\n");
}

int te;
for(l1=0;l1<tp-1;l1++)
{
for(l2=0;l2<tp-l1-1;l2++)
{
if(p[l2].burt>p[l2+1].burt)  //Sorting on the basis burst time
{
te=p[l2].prono;
p[l2].prono=p[l2+1].prono;
p[l2+1].prono=te;
te=p[l2].arrt;
p[l2].arrt=p[l2+1].arrt;
p[l2+1].arrt=te;
te=p[l2].burt;
p[l2].burt=p[l2+1].burt;
p[l2+1].burt=te;
te=burst[l2];
burst[l2]=burst[l2+1];
burst[l2+1]=te;
}
}
}

//DISPLAYING THE DETAILS OF THE PROCESSES ENTERED
printf("******OUTPUT******");
printf("\nPROCESS NO\t\tARRIVAL TIME\t\t\tBURST TIME\t\n");
for(l1=0;l1<=tp-1;l1++)
{
printf("%d \t\t\t%d \t\t\t\t%d \n\n",p[l1].prono,p[l1].arrt,p[l1].burt);
}

//ASSIGNING THE TIME VARIABLE THE MINIMUM ARRIVAL TIME
minart=p[0].arrt;  //Minimum Arrival Time = First Process Arrival Time
for(l1=1;l1<tp;l1++)
{
if(p[l1].arrt<minart){
minart=p[l1].arrt;
}
t1=minart;
}


printf("\n\n********\n\n");
printf("Process\t|TurnAround-time|Waiting-time\t\n");
int c=0; //to count No. of process that finished execution
int flag=0; //to know if Process executed/printed variable
int timequanta=10; //to store Time Quantum of the processes
int wt[tp]; //computing waiting time
int tt[tp]; //computing turnaround time
for(l1=0;c!=tp;l1++)
{
	
if(p[l1].arrt<=t1 && p[l1].burt<=timequanta && p[l1].burt>0) //verify that Burst Time<Time Quantum
{
t1+=p[l1].burt; //time updation
p[l1].burt=0; //update value of burst time
flag=1; //to demonstrate that process is executed
}
else if(p[l1].arrt<=t1 && p[l1].burt>0)
{
p[l1].burt-=timequanta;  
t1+=timequanta;
}
if(p[l1].burt==0 && flag==1)
{
c++;
tt[l1]=t1-p[l1].arrt;
wt[l1]=t1-p[l1].arrt-burst[l1];
printf("%d\t|\t%d\t|\t%d\n",p[l1].prono,tt[l1],wt[l1]);
flag=0; //to check if process printed
}
if(l1==tp-1)
{
l1=-1;
}
}
printf("\n*****\n");
for(l1=0;l1<tp;l1++)
{
totalwaitt+=wt[l1];
totalturnt+=tt[l1];
}
avgwt=totalwaitt*1.0/tp;
avgturnt=totalturnt*1.0/tp;
printf("\nAverage Waiting Timeof the processes= %f\n",avgwt);
printf("\n\n");
printf("Average Turnaround Time of the processes= %f",avgturnt);
printf("\n");
}
