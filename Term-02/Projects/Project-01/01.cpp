#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef struct seat Seat;
typedef vector<Seat> SEAT_LIST;
typedef int HALL_NUMBER;
typedef string PERSON_NAME;
typedef string MOVIE_NAME;
typedef int SEAT_NUMBER;
typedef int TIME;
typedef pair<MOVIE_NAME,PERSON_NAME> MOVIE_PERSON;

struct seat{ 
    vector<MOVIE_PERSON> movie_person;
    seat() : movie_person(24,{" "," "}) {};
};

void Add_Show(vector<SEAT_LIST>& Hall){
    MOVIE_NAME movie_name;
    TIME time;
    HALL_NUMBER hall_number;
    cin >> movie_name >> time >> hall_number;
    if(Hall[hall_number-1][0].movie_person[time-1].first != " "){
        cout << "A movie is already scheduled in this hall at this time" << endl;
    }else{
        for(int i = 0; i < Hall[hall_number-1].size(); i++){
            Hall[hall_number-1][i].movie_person[time-1].first = movie_name;
        }
        cout << "OK" << endl;
    }
}

void Reserve(vector<SEAT_LIST>& Hall){
    
    HALL_NUMBER hall_number;
    TIME time;
    SEAT_NUMBER seat_number;
    PERSON_NAME person_name;
    cin >> hall_number >> time >> seat_number >> person_name;
    if(Hall[hall_number-1][seat_number-1].movie_person[time-1].first == " "){
        cout << "No show is scheduled in this hall at the specified time" << endl;
    }else{
        if(Hall[hall_number-1][seat_number-1].movie_person[time-1].second == " "){
            Hall[hall_number-1][seat_number-1].movie_person[time-1].second = person_name;
            cout << "OK" << endl;
        }else{
            cout << "This seat is already reserved" << endl;
        }
    }
}

void List_Movies(vector<SEAT_LIST>& Hall){
    HALL_NUMBER hall_number;
    TIME time;
    SEAT_NUMBER seat_number;
    PERSON_NAME person_name;
    MOVIE_NAME movie_name;
    cin >> hall_number;
    int movies_available_num = 0;
    Seat test_seat = Hall[hall_number-1][0];
    for(int i = 0; i<24; i++){
        int seats_available_num = Hall[hall_number-1].size();
        if(test_seat.movie_person[i].first != " "){
            movies_available_num ++;
            for(int j = 0; j<Hall[hall_number-1].size(); j++){
                if(Hall[hall_number-1][j].movie_person[i].second != " "){
                    seats_available_num --;
                }
            }
            cout << test_seat.movie_person[i].first << " at " << i+1 << ":00: " << seats_available_num << " seats available" << endl;
        }
    }
    if(movies_available_num == 0){
        cout << "No movie found" << endl;
    }
}

void Report_Seats(vector<SEAT_LIST>& Hall){
    HALL_NUMBER hall_number;
    TIME time;
    PERSON_NAME person_name;
    cin >> hall_number >> time;
    bool all_seats_available = true;
    for(int i = 0; i < Hall[hall_number-1].size(); i++){
        if(Hall[hall_number-1][i].movie_person[time-1].second != " "){
            cout << "Seat " << i+1 << " is reserved by " << Hall[hall_number-1][i].movie_person[time-1].second << endl;
            all_seats_available = false;
        }
    }
    if(all_seats_available){
        cout << "All seats are available" << endl;
    }
}

void Command_Recognition(vector<SEAT_LIST>& Hall){
    string command;
    while(cin >> command){
        if(command == "add_show"){
            Add_Show(Hall);
        }else if(command == "reserve"){
            Reserve(Hall);
        }else if(command == "list_movies"){
            List_Movies(Hall);
        }else if(command == "report_seats"){
            Report_Seats(Hall);
        }
    }
}

int main(){
    vector<SEAT_LIST> Hall(3);
    Hall[0].resize(10);
    Hall[1].resize(20);
    Hall[2].resize(30);
    Command_Recognition(Hall);
}