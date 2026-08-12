#include <stdio.h>
#define NUM 365
int calculate_sleep_minutes(int sleep_time[], int wake_time[], int n, int* low_sleep){
    int sum =0;
    int counter =0;
    for (int i=0; i<n; i++){
        counter =0;
        if ((sleep_time[i]>=2000) && (sleep_time[i]<=2359)){
            counter += (wake_time[i]%100)-(sleep_time[i]%100)+(24-(sleep_time[i]/100))*60 +(wake_time[i]/100)*60;
            sum += counter;
            if(counter<360){
                *low_sleep += 1;
            }
        }else{
            counter += (wake_time[i]%100)-(sleep_time[i]%100)+((wake_time[i]/100)-(sleep_time[i]/100))*60;
            sum += counter;
            if(counter<360){
                *low_sleep += 1;
            }
        }
    }
    return sum;
}

int is_irregular(int sleep_time[], int wake_time[], int n){
    int irregular=0;
    for (int i=0; i<n; i++){
        if (((sleep_time[i]>0000) && (sleep_time[i]<0500)) || (wake_time[i]>1000)){
            irregular++;
        }
    }
    return irregular;
}

int main(){
    int sleep_time[NUM];
    int wake_time[NUM];
    int n=0, low_sleep=0, irregular=0;
    scanf("%d", &n);
    for (int i=0; i<n; i++){
        scanf("%04d-%04d", &sleep_time[i], &wake_time[i]);
    }
    int calculate_sleep = calculate_sleep_minutes(sleep_time,wake_time,n,&low_sleep);
    printf("Total sleep: %d minutes\nAverage Sleep: %.2f minutes\nLow Sleep Nights: %d\nIrregular Nights: %d\n", calculate_sleep , 1.00*calculate_sleep/n , low_sleep , is_irregular(sleep_time,wake_time,n));
}