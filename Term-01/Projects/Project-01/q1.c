int main(){

    char arr[MAX_LENGTH];
    int pos=1, lives=0, energy=0, Length=1;
    char move, ch;

    // Get jungle map from user
    for (int i=0; i<MAX_LENGTH; i++){
        ch = getchar();
        if(ch == '\n'){
            break;
        }
        arr[i] = ch;
        Length++;
    }

    // Get initial lives and energy of Tarzan
    scanf("%d", &lives);
    scanf("%d", &energy);

    do
    {
        // Get user input
        scanf(" %c", &move);

        // Exit the program
        if (move == 'Q'){
            return 0;
        }

        // Reduce Tarzan's energy
        energy -= getEnergyCost(move);

        // Get Tarzan's new position
        int NewPosition = getNewPosition(&pos,move);

        // If a double-step move is made but energy is 1, adjust position by one step back
        if (energy == -1){
            energy =0;
            if (move=='T'){
                NewPosition -= 1;
            }else if (move=='K'){
                NewPosition += 1;
            }
        }

        // Check if Tarzan goes out of jungle bounds
        if ((NewPosition<1)||(NewPosition>=Length)){
            printf("TARZAN GOT LOST IN THE JUNGLE!");
            return 0;
        }

        // Check if Tarzan reaches his friend
        if(arr[NewPosition-1]=='F'){
            printf("TARZAN REACHED HIS FRIEND!");
            return 0;
        }

        // Check if Tarzan steps on a trap and verify if he still has lives left
        if(arr[NewPosition-1]=='T'){
            lives -= 1;
            printf("TARZAN STEPPED ON A TRAP, LOSE 1 LIFE\n");
            if(lives==0){
                printf ("Moved to positon %d, Energy left: %d, Lives left: %d\n", NewPosition , energy , lives);
                printf("TARZAN HAS NO LIFE LEFT!");
                return 0;
            }
        }
        
        // Check if Tarzan steps into a hole and verify if he still has lives left
        if(arr[NewPosition-1]=='H'){
            lives -= 1;
            printf("TARZAN STEPPED INTO A HOLE, LOSE 1 LIFE\n");
            if(lives==0){
                printf ("Moved to positon %d, Energy left: %d, Lives left: %d\n", NewPosition , energy , lives);
                printf("\nTARZAN HAS NO LIFE LEFT!");
                return 0;
            }
        }

        // Display Tarzan's current position, remaining energy and remaining lives after each move
        printf ("Moved to positon %d, Energy left: %d, Lives left: %d\n", NewPosition , energy , lives);
       
    }
    while(energy>0);

    // If all moves are completed successfully but Tarzan does not reach his friend
    printf("TARZAN RAN OUT OF ENERGY!");


}