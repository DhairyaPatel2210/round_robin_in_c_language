#include<conio.h>
#include<stdio.h>
#define size 20
/*
variable naming
no_process = total number of processes
process_nm = it will store process name
arrival_time = store the value of arrival time
burst_time = store the value of burst time
quantam_number = value of quantam for rr algo
rem_burst_time = it will store the values of remaining burst time after
                execution of procees for one time
wt = total waiting time
tat = total turn around time
time = store the current value of time
flag = store that process is executed fully or not
process_number = total number of process but this value is needed for the loop
average_wt = average waiting time
average_tat = average turn around time
*/

typedef struct process_nam
{
    char process_name[20];
}process_name;


void main()
{
    int no_process,temp;
    printf("------This program is for round robin(preemptive)------");
    printf("\nEnter the number of processes : ");
    scanf("%d",&no_process);
    process_name process_nm[no_process],temp_procees_nm;
    int arrival_time[no_process],burst_time[no_process],quantam_number,rem_burst_time[no_process];
    printf("\nEnter Quantam number : ");
    scanf("%d",&quantam_number);
    for(int i=0;i<no_process;i++)
    {
        printf("Enter process name : ");
        scanf("%s",&process_nm[i].process_name);
        printf("Enter arrival time : ");
        scanf("%d",&arrival_time[i]);
        printf("Enter burst time : ");
        scanf("%d",&burst_time[i]);
        rem_burst_time[i] = burst_time[i];  //copying burst time to remaining burst time
        printf("-----------------------------\n");
    }
    //code for sorting the processes according to their arrival time with the use of selection sort
    for(int i=0;i<no_process-1;i++)
    {
        int minimum = i;
        for(int j=i+1;j<no_process;j++)
        {
            if(arrival_time[j]<arrival_time[minimum])
            {
                minimum = j;
            }
        }
        temp = arrival_time[minimum];
        arrival_time[minimum] = arrival_time[i];
        arrival_time[i] = temp;

        temp_procees_nm = process_nm[minimum];
        process_nm[minimum] = process_nm[i];
        process_nm[i] = temp_procees_nm;

        temp = burst_time[minimum];
        burst_time[minimum] = burst_time[i];
        burst_time[i] = temp;

        temp = rem_burst_time[minimum];
        rem_burst_time[minimum] = rem_burst_time[i];
        rem_burst_time[i] = temp;
    }

    //printing out the process name, arrival time, burst time
    printf("\nQuantam number : %d",quantam_number);
    printf("\nProcess_name \t\t arrival_time \t\t burst_time");
    for(int i=0;i<no_process;i++)
    {
        printf("\n %s \t\t\t %d \t\t\t %d",process_nm[i].process_name,arrival_time[i],burst_time[i]);
    }


    //code for calculating waiting time(wt) and turn around time(tat)
    int wt=0,tat=0;
    int time=0;
    int flag = 0;
    int process_number = no_process;
    for(int i = 0 ; process_number != 0 ;)
    {
        //if rem_burst_time is less than or equal quantam then we will not need to execute it again and burst time should be greater than 0
        if(rem_burst_time[i]<=quantam_number && rem_burst_time[i] > 0)
        {
            time  = time + rem_burst_time[i];
            rem_burst_time[i] = 0;
            flag = 1;
        }
        //if rem_burst_time is greater than 0 and quantam time then we will need to execute it again
        else if(rem_burst_time[i] > 0)
        {
            rem_burst_time[i] = rem_burst_time[i] - quantam_number;
            time = time + quantam_number;
        }

        //now if particular process is executed completely then we will reduce the number of process and will calculate waiting time
        //waiting time : time that one process need to wait until it executed completely

        if(flag == 1 && rem_burst_time[i] == 0)
        {
            process_number--;
            wt = ( wt + time ) - (arrival_time[i] + burst_time[i]) ;
            tat=( tat + time )- arrival_time[i];
            flag = 0;
        }
        //if value of i that mean last process is reached and all processes not executed then we need to restart from 1st process again
        if(i == no_process - 1)
        {
            i=0;
        }
        //we will move to next process only if arrival time of next process is less then the current time
        else if(arrival_time[i+1] <= time)
        {
            i++;
        }
        //in all other cases we will change value of i=0
        else
        {
            i=0;
        }
    }

    //calculating average waiting time and turn around time
    float average_wt=0,average_tat=0;
    average_wt = (wt * 1.0 )/ no_process;
    average_tat = (tat * 1.0 )/ no_process;
    //printing the values
    printf("\n-----------------------------");
    printf("\nAverage waiting time  = %f",average_wt);
    printf("\nAverage turnaround time  = %f",average_tat);
    printf("\n-----------------------------");
}

