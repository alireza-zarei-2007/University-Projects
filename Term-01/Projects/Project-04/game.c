#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#define PI 3.14159265358
#define G 0.4
//////////////////////////////////////////////////////////استراکچر تانک چپ
typedef struct {
    int x;//موقعیت تانک          
    int health;//جان تانک        
    char view[3][10];//شکل ظاهری تانک
    int currentTurn;//نوبت تانک  
    int firepower;//قدرت شلیک
    float firingAngle;//زاویه شلیک
    double col_fire;//مکان عمودی گلوله
    double row_fire;//مکان افقی گلوله
} Tank1;
//////////////////////////////////////////////////////////استراکچر تانک راست
typedef struct {
    int x;          
    int health;        
    char view[3][10];
    int currentTurn;  
    int firepower;
    float firingAngle;
    double col_fire;
    double row_fire;
} Tank2;

////////////////////////////////////////////////////////////////////////////////
void PrintGrid(Tank1 *tank1, Tank2 *tank2, int *israndom, int *turn1_length, char grid[][121]);
void printStatsBar(int tank1_health, int tank2_health);
void randomInRange(Tank1 *tank1, Tank2 *tank2);
void updateTankPosition(Tank1 *tank1, Tank2 *tank2, int *turn1_length);
void drawTanks(char grid[][121], Tank1 *tank1, Tank2 *tank2, int *israndom, int *turn1_length);
void clearDynamicElements(char grid[][121], Tank1 *tank1, Tank2 *tank2);
int GetSecondInput(Tank1 *tank1, Tank2 *tank2);
int GetThirdInput(Tank1 *tank1, Tank2 *tank2);
void turn_to_player1(Tank1 *tank1, Tank2 *tank2, int *israndom, int *turn1_length, char grid[][121]);
void turn_to_player2(Tank1 *tank1, Tank2 *tank2, int *israndom, int *turn1_length, char grid[][121]);
int checkTerrainCollision(Tank1 *tank1, Tank2 *tank2);
int checkTankCollision(Tank1 *tank1, Tank2 *tank2);
void calculateShotParameters(Tank1 *tank1, Tank2 *tank2, char grid[][121]);
void computeShotPath (double Vx, double Vy, Tank1 *tank1, Tank2 *tank2, char grid[][121]);
void displayShot (Tank1 *tank1, Tank2 *tank2, char grid[][121]);
void clearPrevShot(Tank1 *tank1, Tank2 *tank2, double col_fire_prev,double row_fire_prev, char grid[][121]);
double ghadr(double x);
int who_is_winner(Tank1 *tank1, Tank2 *tank2);
//////////////////////////////////////////////////////////////////////////////////


void PrintGrid(Tank1 *tank1, Tank2 *tank2, int *israndom, int *turn1_length, char grid[][121]){
    //کشیدن تانک ها روی زمین
    drawTanks(grid, tank1, tank2, israndom, turn1_length);
    //کشیدن تانک و زمین با هم
    printf("|------------------------------------------------------------------------------------------------------------------------|\n");
    for(int i=0; i<22; i++){
        printf("|");
        for(int j=0; j<121; j++){
            printf("%c", grid[i][j]);
        }
        printf("|");
        printf("\n");
    }
    printf("|------------------------------------------------------------------------------------------------------------------------|\n");
}

//////////////////////////////////////////////////////////////////////////////////////

void printStatsBar(int tank1_health, int tank2_health){//چاپ تابلوی جان تانک ها
    printf("\n");
    printf("==========================================================================================================================\n");
    printf("|                         [P1] TANK ALPHA  | HEALTH: %3d%%   ||   [P2] TANK BETA  | HEALTH: %3d%%                          |\n", tank1_health, tank2_health);
    printf("==========================================================================================================================\n");
}

//////////////////////////////////////////////////////////////////////////////////////

void randomInRange(Tank1 *tank1, Tank2 *tank2){//قراردادن رندوم تانک ها
    tank1->x = 0 + rand() % 25;
    tank2->x = 84 + rand() % 28;
}

////////////////////////////////////////////////////////////////////////////////////////

void updateTankPosition(Tank1 *tank1, Tank2 *tank2, int *turn1_length){//جابه جا کردن تانک با توجه به ورودی کاربر ها
    if (tank1->currentTurn == 1){
        tank1->x += *turn1_length;
    }
    if(tank2->currentTurn == 2){
        tank2->x += *turn1_length;
    }
    *turn1_length = 0;
}

////////////////////////////////////////////////////////////////////////////////////////

void drawTanks(char grid[][121], Tank1 *tank1, Tank2 *tank2, int *israndom, int *turn1_length){
    //پاک کردن تانک  های قبل حرکت
    clearDynamicElements(grid, tank1, tank2);
    // کشیدن رندوم تانک ها
    if(*israndom == 1){
        randomInRange(tank1, tank2);
        *turn1_length = 0;
        *israndom = 0;        
    }
    // تعیین پوزیشن تانک ها
    updateTankPosition(tank1, tank2, turn1_length);
    //اضافه کردن تانک ها در حالت جدید به نقشه
    int k=0, z=0;
    for (int i=17; i<20; i++){
        z=0;
        for (int j=tank1->x; j<tank1->x+9; j++){
            grid[i][j] = tank1->view[k][z];
            z++;
        }
        k++;
    }
    k=0; 
    z=0;
    for (int i=17; i<20; i++){
        z=0;
        for (int j=tank2->x; j<tank2->x+9; j++){
            grid[i][j] = tank2->view[k][z];
            z++;
        }
        k++;
    }
}
////////////////////////////////////////////////////////////////////////////////////////

void clearDynamicElements(char grid[][121], Tank1 *tank1, Tank2 *tank2){
    int k=0, z=0;
    for (int i=17; i<20; i++){
        z=0;
        for (int j=tank1->x; j<tank1->x+9; j++){
            grid[i][j] = 32;//گذاشتن کاراکتر اسپیس به جای خانه های تانک
            z++;
        }
        k++;
    }
    k=0; 
    z=0;
    for (int i=17; i<20; i++){
        z=0;
        for (int j=tank2->x; j<tank2->x+9; j++){
            grid[i][j] = 32;//گذاشتن کاراکتر اسپیس به جای خانه های تانک
            z++;
        }
        k++;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
int GetSecondInput(Tank1 *tank1, Tank2 *tank2){
    if(tank1->currentTurn == 1){
        printf("(Player 1) Enter Firing Angle [0-180]: ");
        scanf("%f", &tank1->firingAngle);
        if((tank1->firingAngle > 180) || (tank1->firingAngle < 0)){
            return 0;//زاویه شلیک در محدوده مجاز نیست
        }else{
            return 1;
        }
    }
    if(tank2->currentTurn == 2){
        printf("(Player 2) Enter Firing Angle [0-180]: ");
        scanf("%f", &tank2->firingAngle);
        if((tank2->firingAngle > 180) || (tank2->firingAngle < 0)){
            return 0;//زاویه شلیک در محدوده مجاز نیست
        }else{
            return 1;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
int GetThirdInput(Tank1 *tank1, Tank2 *tank2){
    if(tank1->currentTurn == 1){
        printf("(Player 1) Enter Shot Power [1-100]: ");
        scanf("%d", &tank1->firepower);
        if((tank1->firepower > 100) || (tank1->firepower < 1)){
            return 0;//قدرت شلیک در محدوده مجاز نیست
        }else{
            return 1;
        }
    }
    if(tank2->currentTurn == 2){
        printf("(Player 2) Enter Shot Power [1-100]: ");
        scanf("%d", &tank2->firepower);
        if((tank2->firepower > 100) || (tank2->firepower < 1)){
            return 0;//قدرت شلیک در محدوده مجاز نیست
        }else{
            return 1;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
void turn_to_player1(Tank1 *tank1, Tank2 *tank2, int *israndom, int *turn1_length, char grid[][121]){
    printStatsBar(tank1->health, tank2->health);
    PrintGrid(tank1, tank2, israndom, turn1_length, grid);
    tank1->currentTurn = 1;
    tank2->currentTurn = 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////
void turn_to_player2(Tank1 *tank1, Tank2 *tank2, int *israndom, int *turn1_length, char grid[][121]){
    printStatsBar(tank1->health, tank2->health);
    PrintGrid(tank1, tank2, israndom, turn1_length, grid);
    tank1->currentTurn = 0;
    tank2->currentTurn = 2;
}
///////////////////////////////////////////////////////////////////////////////////////////////
int checkTerrainCollision(Tank1 *tank1, Tank2 *tank2){//بررسی همپوشانی گلوله با عناصر ایستا
    char grid[22][121] = {
   "                  ^                                                                                                     ",
   "                 ^^^                                                                            ^                       ",
   "                ^^^^^                                                                          ^^^                      ",
   "                                                                                              ^^^^^                     ",
   "                                                                                                                        ",
   "                                                                                                                        ",
   "                      ^^                                                                                                ",
   "                     ^^^^                                                                                               ",
   "                    ^^^^^^                                                                                    ^         ",
   "                                                                                                             ^^^        ",
   "                                                                                                                        ",
   "                                                                                                                        ",
   "                                                          ^                                                             ",
   "                                                         ^^^         ^^                                                 ",
   "                                                        ^^^^^       ^^^^                                                ",
   "                                               ^       ^^^^^^^^    ^^^^^^                                               ",
   "                                              ^^^     ^^^^^^^^^^  ^^^^^^^^     ^                                        ",
   "                                   ^^        ^^^^^  ^^^^^^^^^^^^^^^^^^^^^^^^  ^^^                                       ",
   "                                  ^^^^     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                      ",
   "                                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                    ",
   "########################################################################################################################",
   "########################################################################################################################",
    };
    if(tank1->currentTurn == 1){
        if(((int)round(tank1->row_fire) < 0) || ((int)round(tank1->col_fire) < 0) || ((int)round(tank1->col_fire) >= 120)){
            return 1;//گلوله از کادر بازی خارج شده است
        }
        if((grid[(int)round(tank1->row_fire)][(int)round(tank1->col_fire)] == '^') || (grid[(int)round(tank1->row_fire)][(int)round(tank1->col_fire)] == '#')){
            return 1;//گلوله به سنگ یا دیوار برخورد کرده است
        }
        if(grid[(int)round(tank1->row_fire)][(int)round(tank1->col_fire)] == 32){
            return 0;//گلوله هنوز در فضا در حال حرکت است
        }
    }else if(tank2->currentTurn == 2){
        if(((int)round(tank2->row_fire) < 0) || ((int)round(tank2->col_fire) < 0) || ((int)round(tank2->col_fire) >= 120)){
            return 1;//گلوله از کادر بازی خارج شده است
        }
        if((grid[(int)round(tank2->row_fire)][(int)round(tank2->col_fire)] == '^') || (grid[(int)round(tank2->row_fire)][(int)round(tank2->col_fire)] == '#')){
            return 1;//گلوله به سنگ یا دیوار برخورد کرده است
        }
        if(grid[(int)round(tank2->row_fire)][(int)round(tank2->col_fire)] == 32){
            return 0;//گلوله هنوز در فضا در حال حرکت است
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
int checkTankCollision(Tank1 *tank1, Tank2 *tank2){//بررسی همپوشانی گلوله با تانک ها
    if(tank1->currentTurn == 1){
        int k=0, z=0;
        for (int i=17; i<20; i++){
            z=0;
            for (int j=tank1->x; j<tank1->x+9; j++){
                if((i == (int)round(tank1->row_fire)) && (j == (int)round(tank1->col_fire))){
                    return 2;//ریترن دو به معنای شلیک به تانک خودی است
                }
                z++;
            }
            k++;
        }
        k=0; 
        z=0;
        for (int i=17; i<20; i++){
            z=0;
            for (int j=tank2->x; j<tank2->x+9; j++){
                if((i == (int)round(tank1->row_fire)) && (j == (int)round(tank1->col_fire))){
                    return 1;//ریترن یک به معنای شلیک موفق به تانک حریف است
                }
                z++;
            }
            k++;
        }
        return 0;//به معنای اینکه شلیک هنوز به چیزی برخورد نکرده است
    }else if(tank2->currentTurn == 2){
        int k=0, z=0;
        for (int i=17; i<20; i++){
            z=0;
            for (int j=tank2->x; j<tank2->x+9; j++){
                if((i == (int)round(tank2->row_fire)) && (j == (int)round(tank2->col_fire))){
                    return 2;//ریترن دو به معنای شلیک به تانک خودی است
                }
                z++;
            }
            k++;
        }
        k=0; 
        z=0;
        for (int i=17; i<20; i++){
            z=0;
            for (int j=tank1->x; j<tank1->x+9; j++){
                if((i == (int)round(tank2->row_fire)) && (j == (int)round(tank2->col_fire))){
                    return 1;//ریترن یک به معنای شلیک موفق به تانک حریف است
                }
                z++;
            }
            k++;
        }
        return 0;//به معنای اینکه شلیک هنوز به چیزی برخورد نکرده است
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
void calculateShotParameters(Tank1 *tank1, Tank2 *tank2, char grid[][121]){//محاسبه پارامتر های شلیک
    if(tank1->currentTurn == 1){
        double firing_angle_rad = (double)(tank1->firingAngle) * ((double)PI/180);
        double power = 2 + 7*pow((double)(tank1->firepower)/100, (double)1.5);
        double Vx = cos(firing_angle_rad) * power;   
        double Vy = sin(firing_angle_rad) * power;
        computeShotPath(Vx, Vy, tank1, tank2, grid);   
    }
    if(tank2->currentTurn == 2){
        double firing_angle_rad = (double)(tank2->firingAngle) * ((double)PI/180);
        double power = 2 + 7*pow((double)(tank2->firepower)/100, (double)1.5);
        double Vx = (-1)*(cos(firing_angle_rad) * power);   
        double Vy = sin(firing_angle_rad) * power;
        computeShotPath(Vx, Vy, tank1, tank2, grid);   
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
void computeShotPath (double Vx, double Vy, Tank1 *tank1, Tank2 *tank2, char grid[][121]){//محاسبه مسیر گلوله
    if(tank1->currentTurn == 1){
        //زمان نسبی
        double t=0;
        //موقعیت اول شلیک گلوله
        double X0 = (double)(tank1->x + 9);    
        double Y0 = (double)17;
        //ذخیره شلیک قبلی    
        double col_fire_prev = X0;
        double row_fire_prev = Y0;
        //محاسبه تعداد حرکت پیکسلی گلوله
        double delta_col=0;
        double delta_row=0;
        //مقداردهی اولیه
        tank1->col_fire = X0;
        tank1->row_fire = Y0;
        //کشیدن اولیه گلوله
        displayShot(tank1, tank2, grid);
        clearPrevShot(tank1, tank2, col_fire_prev, row_fire_prev, grid);
        while(1){
            //محاسبه حرکت پرتابه ای
            tank1->col_fire = (Vx*t) + X0;
            tank1->row_fire = (-1)*(((-0.5)*G*t*t) + (Vy*t)) + Y0;
            //ذخیره قدرمطلق حرکت پیکسلی گلوله
            delta_col += ghadr(tank1->col_fire - col_fire_prev);
            delta_row += ghadr(tank1->row_fire - row_fire_prev);
            //ذخیره موقعیت گلوله به عنوان موقعیت قبلی
            col_fire_prev = tank1->col_fire;
            row_fire_prev = tank1->row_fire;
            //چک کردن برخورد گلوله با تانک یا کوه و زمین یا خروج از زمین بازی
            int checkTank = checkTankCollision(tank1, tank2);
            int checkTerrain = checkTerrainCollision(tank1, tank2);
            if(checkTank == 2){
                //در صورت برخورد گلوله به تانک خودی، زمان 0.1 کم شود و دوباره مقدار حساب شود و برای اخرین بار تیر نمایش داده شود
                Sleep(750);
                system("cls");
                t -= (double)(0.1);
                tank1->col_fire = (Vx*t) + X0;
                tank1->row_fire = (-1)*(((-0.5)*G*t*t) + (Vy*t)) + Y0;
                col_fire_prev = tank1->col_fire;
                row_fire_prev = tank1->row_fire;
                displayShot(tank1, tank2, grid);
                clearPrevShot(tank1, tank2, col_fire_prev, row_fire_prev, grid);
                printf("BOOM!!! Friendly Fire");
                //کم کردن جون تانک
                tank1->health -= 20;
                break;
            }else if(checkTank == 1){
                //در صورت برخورد گلوله به تانک حریف، زمان 0.1 کم میشود و دوباره مقدار حساب میشود و برای آخرین بار تیر نمایش داده شود
                Sleep(750);
                system("cls");
                t -= (double)(0.1);
                tank1->col_fire = (Vx*t) + X0;
                tank1->row_fire = (-1)*(((-0.5)*G*t*t) + (Vy*t)) + Y0;
                col_fire_prev = tank1->col_fire;
                row_fire_prev = tank1->row_fire;
                displayShot(tank1, tank2, grid);
                clearPrevShot(tank1, tank2, col_fire_prev, row_fire_prev, grid);
                printf("BOOM!!! Clean Hit On The Enemy");
                //کم کردن جون تانک
                tank2->health -= 20;
                break;
            }else if(checkTank == 0){

            }
            if(checkTerrain == 1){
                //در صورت برخورد گلوله به سنگ یا خروج از کادر، زمان 0.1 کم میشود و دوباره نمایش داده میشود
                Sleep(750);
                system("cls");
                t -= (double)(0.1);
                tank1->col_fire = (Vx*t) + X0;
                tank1->row_fire = (-1)*(((-0.5)*G*t*t) + (Vy*t)) + Y0;
                col_fire_prev = tank1->col_fire;
                row_fire_prev = tank1->row_fire;
                displayShot(tank1, tank2, grid);
                clearPrevShot(tank1, tank2, col_fire_prev, row_fire_prev, grid);
                printf("Shot Terminated!");
                break;
            }else if(checkTerrain == 0){
                //در صورت برخورد نکردن، ادامه یابد
            }
            if(round(delta_col + delta_row) == 6){//در صورت جابه جا شدن گلوله به اندازه 6 واحد، گلوله چاپ شود
                Sleep(750);
                system("cls");
                displayShot(tank1, tank2, grid);
                clearPrevShot(tank1, tank2, col_fire_prev, row_fire_prev, grid);
                delta_col =0;
                delta_row =0;
            }
            //هر دور زمان 0.1 زیاد شود
            t += (double)(0.1);
        }
        
    }else if(tank2->currentTurn == 2){//این بخش مانند بخش بالا فقط برای تانک دوم است
        double t=0;
        double X0 = (double)(tank2->x - 1);    
        double Y0 = (double)17;    
        double col_fire_prev = X0;
        double row_fire_prev = Y0;
        double delta_col=0;
        double delta_row=0;
        tank2->col_fire = X0;
        tank2->row_fire = Y0;
        displayShot(tank1, tank2, grid);
        clearPrevShot(tank1, tank2, col_fire_prev, row_fire_prev, grid);
        while(1){
            tank2->col_fire = (Vx*t) + X0;
            tank2->row_fire = (-1)*(((-0.5)*G*t*t) + (Vy*t)) + Y0;
            delta_col += ghadr(tank2->col_fire - col_fire_prev);
            delta_row += ghadr(tank2->row_fire - row_fire_prev);
            col_fire_prev = tank2->col_fire;
            row_fire_prev = tank2->row_fire;
            int checkTank = checkTankCollision(tank1, tank2);
            int checkTerrain = checkTerrainCollision(tank1, tank2);
            if(checkTank == 2){
                Sleep(750);
                system("cls");
                t -= (double)(0.1);
                tank2->col_fire = (Vx*t) + X0;
                tank2->row_fire = (-1)*(((-0.5)*G*t*t) + (Vy*t)) + Y0;
                col_fire_prev = tank2->col_fire;
                row_fire_prev = tank2->row_fire;
                displayShot(tank1, tank2, grid);
                clearPrevShot(tank1, tank2, col_fire_prev, row_fire_prev, grid);
                printf("BOOM!!! Friendly Fire");
                tank2->health -= 20;
                break;
            }else if(checkTank == 1){
                Sleep(750);
                system("cls");
                t -= (double)(0.1);
                tank2->col_fire = (Vx*t) + X0;
                tank2->row_fire = (-1)*(((-0.5)*G*t*t) + (Vy*t)) + Y0;
                col_fire_prev = tank2->col_fire;
                row_fire_prev = tank2->row_fire;
                displayShot(tank1, tank2, grid);
                clearPrevShot(tank1, tank2, col_fire_prev, row_fire_prev, grid);
                printf("BOOM!!! Clean Hit On The Enemy");
                tank1->health -= 20;
                break;
            }else if(checkTank == 0){

            }
            if(checkTerrain == 1){
                Sleep(750);
                system("cls");
                t -= (double)(0.1);
                tank2->col_fire = (Vx*t) + X0;
                tank2->row_fire = (-1)*(((-0.5)*G*t*t) + (Vy*t)) + Y0;
                col_fire_prev = tank2->col_fire;
                row_fire_prev = tank2->row_fire;
                displayShot(tank1, tank2, grid);
                clearPrevShot(tank1, tank2, col_fire_prev, row_fire_prev, grid);
                printf("Shot Terminated!");
                break;
            }else if(checkTerrain == 0){

            }
            if(round((delta_col) + delta_row) == 6){
                Sleep(750);
                system("cls");
                displayShot(tank1, tank2, grid);
                clearPrevShot(tank1, tank2, col_fire_prev, row_fire_prev, grid);
                delta_col =0;
                delta_row =0;
            }
            t += (double)(0.1);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
void displayShot (Tank1 *tank1, Tank2 *tank2, char grid[][121]){//نمایش فرایند شلیک گلوله
    if(tank1->currentTurn == 1){
        grid[(int)round(tank1->row_fire)][(int)round(tank1->col_fire)] = '*';
        printf("|------------------------------------------------------------------------------------------------------------------------|\n");
        for(int i=0; i<22; i++){
            printf("|");
            for(int j=0; j<121; j++){
                printf("%c", grid[i][j]);
            }
            printf("|");
            printf("\n");
        }
        printf("|------------------------------------------------------------------------------------------------------------------------|\n");
    }
    if(tank2->currentTurn == 2){
        grid[(int)round(tank2->row_fire)][(int)round(tank2->col_fire)] = '*';
        printf("|------------------------------------------------------------------------------------------------------------------------|\n");
        for(int i=0; i<22; i++){
            printf("|");
            for(int j=0; j<121; j++){
                printf("%c", grid[i][j]);
            }
            printf("|");
            printf("\n");
        }
        printf("|------------------------------------------------------------------------------------------------------------------------|\n");
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
void clearPrevShot(Tank1 *tank1, Tank2 *tank2, double col_fire_prev,double row_fire_prev, char grid[][121]){
    if(tank1->currentTurn == 1){
        grid[(int)round(row_fire_prev)][(int)round(col_fire_prev)] = 32;//به جای گلوله قبلی، اسپیس قرار داده شود
    }
    if(tank2->currentTurn == 2){
        grid[(int)round(row_fire_prev)][(int)round(col_fire_prev)] = 32;//به جای گلوله قبلی، اسپیس قرار داده شود
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
double ghadr(double x){//تابع محاسبه قدرمطلق
    if(x < 0){
        x = (-1) * x;
    }
    return x;
}
int who_is_winner(Tank1 *tank1, Tank2 *tank2){//تابع چک کردن اینکه آیا کسی برنده شده یا خیر
    if(tank1->health == 0){
        printf("--------------------------------------------------------PLAYER 2 WINS-----------------------------------------------------");
        return 1;//ریترن 1 به معنای برنده شدن یکی از دو بازیکن است.
    }else if(tank2->health == 0){
        printf("--------------------------------------------------------PLAYER 1 WINS-----------------------------------------------------");
        return 1;//ریترن 1 به معنای برنده شدن یکی از دو بازیکن است.
    }else{
        return 0;//هنوز بازیکنی برنده نشده است.
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    char grid[22][121] = {
   "                  ^                                                                                                     ",
   "                 ^^^                                                                            ^                       ",
   "                ^^^^^                                                                          ^^^                      ",
   "                                                                                              ^^^^^                     ",
   "                                                                                                                        ",
   "                                                                                                                        ",
   "                      ^^                                                                                                ",
   "                     ^^^^                                                                                               ",
   "                    ^^^^^^                                                                                    ^         ",
   "                                                                                                             ^^^        ",
   "                                                                                                                        ",
   "                                                                                                                        ",
   "                                                          ^                                                             ",
   "                                                         ^^^         ^^                                                 ",
   "                                                        ^^^^^       ^^^^                                                ",
   "                                               ^       ^^^^^^^^    ^^^^^^                                               ",
   "                                              ^^^     ^^^^^^^^^^  ^^^^^^^^     ^                                        ",
   "                                   ^^        ^^^^^  ^^^^^^^^^^^^^^^^^^^^^^^^  ^^^                                       ",
   "                                  ^^^^     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                      ",
   "                                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                    ",
   "########################################################################################################################",
   "########################################################################################################################",
    };
    //ایجاد فضا برای بازیکن اول و دوم
    Tank1 *tank1 = (Tank1*)malloc(sizeof(Tank1));
    Tank2 *tank2 = (Tank2*)malloc(sizeof(Tank2));
    //تعریف ظاهر تانک ها
    char view_tank1[3][10] = {"   __    ",
                              " _|__|_//",
                              "|_______|",};
    char view_tank2[3][10] = {"    __   ",
                              "\\\\_|__|_ ",
                              "|_______|",};
    //سه حرکت هر بازیکن
    char turn1;
    int turn1_length=0;
    //چک کردن ایجاد کردن یا نکردن صفحه ی رندوم برای بازی
    int israndom=1;
    //تعریف های اولیه
    tank1->health = 100;
    tank2->health = 100;
    memcpy(tank1->view, view_tank1, sizeof(view_tank1));
    memcpy(tank2->view, view_tank2, sizeof(view_tank2));    
    tank1->currentTurn = 1;
    tank2->currentTurn = 0;
    srand(time(NULL));
    //آرایه مورد نیاز برای فهمیدن اینکه کاربر بعد از کاراکتر، عدد دیگری وارد کرده یا خیر
    char check[100];
    //کشیدن اولیه بازی
    tank1->x =0;
    tank2->x =0;
    printStatsBar(tank1->health, tank2->health);
    PrintGrid(tank1, tank2, &israndom, &turn1_length, grid);
    //حلقه مدیریت و چرخش بازی بین بازیکن ها
    while(1){
        //پاک کردن فایل تعداد حرکت تانک ها
        memset(check, 0, sizeof(check));
        //تشخیص شروع بازی برای دریافت ورودی
        if(tank1->currentTurn == 1){
            printf("(Player 1) Enter Command - L=Left, R=Right, S=Skip, Q=Quit, N=New Game: ");
            scanf(" %c%[^\n]", &turn1, check);
            sscanf(check, "%d", &turn1_length);
        }
        if(tank2->currentTurn == 2){
            printf("(Player 2) Enter Command - L=Left, R=Right, S=Skip, Q=Quit, N=New Game: ");
            scanf(" %c%[^\n]", &turn1, check);
            sscanf(check, "%d", &turn1_length);
        }




        //تشخیص بازیکن برای اعمال کار
        if (tank1->currentTurn == 1){
            if (turn1 == 'R'){//در صورت وارد کردن R
                if((tank1->x + turn1_length) > 24){//در صورت در محدوده مجاز نبودن
                    printf("Illegal Move - Your Turn Is Lost!\n");
                    Sleep(3000);
                    system("cls");
                    turn1_length = 0;
                    turn_to_player2(tank1, tank2, &israndom, &turn1_length, grid);
                    continue;
                }else{//در صورت در محدوده مجاز بودن
                    system("cls");
                    printStatsBar(tank1->health, tank2->health);
                    PrintGrid(tank1, tank2, &israndom, &turn1_length, grid);
                    //دریافت ورودی های 2 و 3
                    if(GetSecondInput(tank1, tank2) == 1){
                        if(GetThirdInput(tank1, tank2) == 1){
                            //در صورت در محدوده مجاز بودن هر دو ورودی، شلیک نمایش داده شود و پس از چک کردن جان تانک ها، برنامه ادامه یابد
                            system("cls");
                            calculateShotParameters(tank1, tank2, grid);
                            turn1_length = 0;
                            Sleep(3000);
                            system("cls");
                            turn_to_player2(tank1, tank2, &israndom, &turn1_length, grid);
                            if(who_is_winner(tank1, tank2) == 1){
                                break;
                            }
                            continue;
                        }else{
                            //در صورت خارج محدوده بودن قدرت شلیک
                            printf("Power Out Of Range - Your Turn Is Lost!\n");
                            Sleep(3000);
                            system("cls");
                            turn1_length = 0;
                            turn_to_player2(tank1, tank2, &israndom, &turn1_length, grid);
                            continue;
                        }
                    }else{
                        //در صورت خارج محدوده بودن زاویه شلیک
                        printf("Angle Out Of Range - Your Turn Is Lost!\n");
                        Sleep(3000);
                        system("cls");
                        turn1_length = 0;
                        turn_to_player2(tank1, tank2, &israndom, &turn1_length, grid);
                        continue;
                    }
                }
            }
            if (turn1 == 'L'){//در صورت وارد کردن L
                if((tank1->x - turn1_length) < 0){//در صورت در محدوده مجاز نبودن
                    printf("Illegal Move - Your Turn Is Lost!\n");
                    Sleep(3000);
                    system("cls");
                    turn1_length = 0;
                    turn_to_player2(tank1, tank2, &israndom, &turn1_length, grid);
                    continue;
                }else{//در صورت در محدوده مجاز بودن
                    system("cls");
                    turn1_length *= -1;
                    printStatsBar(tank1->health, tank2->health);
                    PrintGrid(tank1, tank2, &israndom, &turn1_length, grid);
                    //دریافت ورودی های 2 و 3
                    if(GetSecondInput(tank1, tank2) == 1){
                        if(GetThirdInput(tank1, tank2) == 1){
                            //در صورت در محدوده مجاز بودن هر دو ورودی، شلیک نمایش داده شود و پس از چک کردن جان تانک ها، برنامه ادامه یابد
                            system("cls");
                            calculateShotParameters(tank1, tank2, grid);
                            turn1_length = 0;
                            Sleep(3000);
                            system("cls");
                            turn_to_player2(tank1, tank2, &israndom, &turn1_length, grid);
                            if(who_is_winner(tank1, tank2) == 1){
                                break;
                            }
                            continue;
                        }else{
                            //در صورت خارج محدوده بودن قدرت شلیک
                            printf("Power Out Of Range - Your Turn Is Lost!\n");
                            Sleep(3000);
                            system("cls");
                            turn1_length = 0;
                            turn_to_player2(tank1, tank2, &israndom, &turn1_length, grid);
                            continue;
                        }
                    }else{
                        //در صورت خارج محدوده بودن زاویه شلیک
                        printf("Angle Out Of Range - Your Turn Is Lost!\n");
                        Sleep(3000);
                        system("cls");
                        turn1_length = 0;
                        turn_to_player2(tank1, tank2, &israndom, &turn1_length, grid);
                        continue;
                    }
                }
            }
            if (turn1 == 'S'){//در صورت جا به جا کردن نوبت
                system("cls");
                turn_to_player2(tank1, tank2, &israndom, &turn1_length, grid);
                continue;
            }
            if (turn1 == 'Q'){//در صورت خروج از بازی
                break;
            }
            if (turn1 == 'N'){//در صورت درخواست بازی جدید
                tank1->health = 100;
                tank2->health = 100;
                israndom = 1;
                system("cls");
                turn_to_player1(tank1, tank2, &israndom, &turn1_length, grid);
                continue;
            }else{//در صورت وارد کردن هر چی غیر از مقادیر مجاز
                printf("Illegal Move - Your Turn Is Lost!\n");
                Sleep(3000);
                system("cls");
                turn1_length = 0;
                turn_to_player2(tank1, tank2, &israndom, &turn1_length, grid);
                continue;
            }
        }
        
        
        
        // تمام کامنت ها برای تانک1، برای تانک2 نیز صادق است
        else if (tank2->currentTurn == 2){
            if (turn1 == 'R'){//در صورت وارد کردن R
                if((tank2->x + turn1_length) > 111){//در صورت در محدوده مجاز نبودن
                    printf("Illegal Move - Your Turn Is Lost!\n");
                    Sleep(3000);
                    system("cls");
                    turn1_length = 0;
                    turn_to_player1(tank1, tank2, &israndom, &turn1_length, grid);
                    continue;
                }else{//در صورت در محدوده مجاز بودن
                    system("cls");
                    printStatsBar(tank1->health, tank2->health);
                    PrintGrid(tank1, tank2, &israndom, &turn1_length, grid);
                    /////////////دریافت ورودی های 2 و 3
                    if(GetSecondInput(tank1, tank2) == 1){
                        if(GetThirdInput(tank1, tank2) == 1){
                            system("cls");
                            calculateShotParameters(tank1, tank2, grid);
                            turn1_length = 0;
                            Sleep(3000);
                            system("cls");
                            turn_to_player1(tank1, tank2, &israndom, &turn1_length, grid);
                            if(who_is_winner(tank1, tank2) == 1){
                                break;
                            }
                            continue;
                        }else{
                            printf("Power Out Of Range - Your Turn Is Lost!\n");
                            Sleep(3000);
                            system("cls");
                            turn1_length = 0;
                            turn_to_player1(tank1, tank2, &israndom, &turn1_length, grid);
                            continue;
                        }
                    }else{
                        printf("Angle Out Of Range - Your Turn Is Lost!\n");
                        Sleep(3000);
                        system("cls");
                        turn1_length = 0;
                        turn_to_player1(tank1, tank2, &israndom, &turn1_length, grid);
                        continue;
                    }
                    //////////////
                }
            }
            if (turn1 == 'L'){//در صورت وارد کردن L
                if((tank2->x - turn1_length) < 84){//در صورت در محدوده مجاز نبودن
                    printf("Illegal Move - Your Turn Is Lost!\n");
                    Sleep(3000);
                    system("cls");
                    turn1_length = 0;
                    turn_to_player1(tank1, tank2, &israndom, &turn1_length, grid);
                    continue;
                }else{//در صورت در محدوده مجاز بودن
                    system("cls");
                    turn1_length *= -1;
                    printStatsBar(tank1->health, tank2->health);
                    PrintGrid(tank1, tank2, &israndom, &turn1_length, grid);
                    //////////////دریافت های ورودی 2 و 3
                    if(GetSecondInput(tank1, tank2) == 1){
                        if(GetThirdInput(tank1, tank2) == 1){
                            system("cls");
                            calculateShotParameters(tank1, tank2, grid);
                            turn1_length = 0;
                            Sleep(3000);
                            system("cls");
                            turn_to_player1(tank1, tank2, &israndom, &turn1_length, grid);
                            if(who_is_winner(tank1, tank2) == 1){
                                break;
                            }
                            continue;
                        }else{
                            printf("Power Out Of Range - Your Turn Is Lost!\n");
                            Sleep(3000);
                            system("cls");
                            turn1_length = 0;
                            turn_to_player1(tank1, tank2, &israndom, &turn1_length, grid);
                            continue;
                        }
                    }else{
                        printf("Angle Out Of Range - Your Turn Is Lost!\n");
                        Sleep(3000);
                        system("cls");
                        turn1_length = 0;
                        turn_to_player1(tank1, tank2, &israndom, &turn1_length, grid);
                        continue;
                    }
                    ////////////////
                }
            }
            if (turn1 == 'S'){//در صورت جا به جا کردن نوبت
                system("cls");
                turn_to_player1(tank1, tank2, &israndom, &turn1_length, grid);
                continue;
            }
            if (turn1 == 'Q'){//در صورت خروج از بازی
                break;
            }
            if (turn1 == 'N'){//در صورت درخواست بازی جدید
                tank1->health = 100;
                tank2->health = 100;
                israndom = 1;
                system("cls");
                turn_to_player1(tank1, tank2, &israndom, &turn1_length, grid);
                continue;
            }else{//در صورت وارد کردن هر چی غیر از مقادیر مجاز
                printf("Illegal Move - Your Turn Is Lost!\n");
                Sleep(3000);
                system("cls");
                turn1_length = 0;
                turn_to_player1(tank1, tank2, &israndom, &turn1_length, grid);
                continue;
            }
        }




    }
    //آزاد کردن حافظه در آخر بازی
    free(tank1);
    free(tank2);
    return 0;
}
