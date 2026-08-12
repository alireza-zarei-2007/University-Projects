#include <stdio.h>

int main(){
    int n=0;
    // User inputs
    int difficulty1=0, difficulty2=0, success1=0, success2=0, time1=0, time2=0;
    // Sum of training difficulties
    float sum_difficulty=0;
    // Indicates whether the 2 variables have been increasing or decreasing throughout
    int succuss_improving=1,succuss_declining=1, time_improving=1,time_declining=1;
    scanf("%d", &n);
    // Get initial values
    scanf ("%d ", &difficulty1);
    scanf ("%d ", &success1);
    scanf ("%d", &time1);
    sum_difficulty += 1.0*difficulty1;

    for (int i=1; i<n; i++){
        scanf ("%d ", &difficulty2);
        scanf ("%d ", &success2);
        scanf ("%d", &time2);

        // Calculate sum of difficulties
        sum_difficulty += 1.0*difficulty2;

        // Check if success values are increasing or decreasing
        if (success2 > success1){
            succuss_declining=0 ;
        }
        if (success2 < success1){
            succuss_improving=0;
        }
        success1 = success2;

        // Check if time values are increasing or decreasing
        if (time2 > time1){
            time_declining=0 ;
        }
        if (time2 < time1){
            time_improving=0;
        }
        time1 = time2;
    }

    // Determine if strictly constant, strictly increasing, or strictly decreasing
    int succuss_improved=0, succuss_declined=0, time_improved=0, time_declined=0;

    if (succuss_declining && succuss_improving){
        succuss_improved =1;
        succuss_declined =1;
    }else if(succuss_declining){
        succuss_declined =1;
    }else if(succuss_improving){
        succuss_improved =1;
    }

    if (time_declining && time_improving){
        time_improved =1;
        time_declined =1;
    }else if(time_declining){
        time_declined =1;
    }else if(time_improving){
        time_improved =1;
    }


    // Determine if improvement or decline has occurred
    if (succuss_improved && time_improved && ((sum_difficulty/n) >= 5)){
        printf("Athlete Status: Improving");
        return 0;
    }else if (succuss_declined && time_declined && ((sum_difficulty/n) < 5)){
        printf("Athlete Status: Declining");
        return 0;
    }
    printf("Athlete Status: Stable");
    return 0;
}