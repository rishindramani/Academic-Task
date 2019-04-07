#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() 
{ 
  int c,j,pro;//variable for count and number of processes
  int ti,re;// time and process variables
  int check=0;//flag variable
  int quan=10; //time quantum=10 given
  int wt=0,tat=0,at[10],bt[10],rt[10]; //initialising waiting time,turnaround time,arrival time,burst time
  
  printf("\n\nEnter Total Processes:\t "); 
  scanf("%d",&pro); 
  re=pro;
   
  for(c=0;c<pro;c++) 
  { 
    printf("Enter Arrival Time and Burst Time for Process %d :",c+1); 
    scanf("%d",&at[c]); 
    scanf("%d",&bt[c]); 
    rt[c]=bt[c]; 
  } 
  printf("Time Quantum= %d time units\t",quan); 

  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
  for(ti=0,c=0;re!=0;) 
  { 
    if(rt[c]<=quan && rt[c]>0) //loop ealuation from remaining time in the queue
    { 
      ti+=rt[c]; 
      rt[c]=0; 
      check=1; 
    } 
    else if(rt[c]>0)
    { 
      rt[c]-=quan;                   //preempting on the basis of time quanta scheduling processes having short execution time first.
      ti+=quan; 
    } 
    if(rt[c]==0 && check==1) 
    { 
      re--; 
      printf("P[%d]\t|\t%d\t|\t%d\n",c+1,ti-at[c],ti-at[c]-bt[c]); 
      wt+=ti-at[c]-bt[c]; 
      tat+=ti-at[c]; 
      check=0; 
    } 
    if(c==pro-1) 
    {
	
      c=0; 
    }
	else if(at[c+1]<=ti) 
    {
	   c++; 
    }
	else 
    {
	   c=0; 
}
  } 
  printf("\nAverage Waiting Time= %f\n",wt*1.0/pro); //printing the average waiting time and average turnaround time
  printf("Average Turnaround Time = %f",tat*1.0/pro); 

  return 0; 
}
