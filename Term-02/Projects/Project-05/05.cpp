#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

const int NUM_OF_FEATURE_CITY = 2;
const int NUM_OF_FEATURE_TRUCK = 2;
const string TEHRAN = "Tehran";

struct Truck{
    int id;//
    int orig_capacity;//
    int curr_capacity;
    string curr_location = TEHRAN;
    string destination_city;
    bool Is_carrying = false;
};
struct Order{
    string origin_city;
    string destination_city;
    int weight;
    int id;
    bool Is_In_Truck = false;
    bool Is_delivered = false;
    int score;
    int cost;
    Truck* carrier_truck;
};
struct City{
    string name;    
    int distance;
    float score;
};

int OpenRead_CSV_File_Truk(const string& INPUT_TRUCK_FILE_NAME, vector<Truck>& trucks){
    ifstream file(INPUT_TRUCK_FILE_NAME);
    if(!file.is_open()){
        return 0;
    }

    string line;
    getline(file, line);

    while(getline(file, line)){
        Truck truck;
        stringstream ss(line);
        string cell;
        for(int i=0; i<NUM_OF_FEATURE_TRUCK; i++){
            getline(ss, cell, ',');
            if(i==0) truck.id = stoi(cell);
            if(i==1){ truck.orig_capacity = stoi(cell); truck.curr_capacity = stoi(cell); }
        }
        trucks.push_back(truck);
    }
    return 1;
}

int OpenRead_CSV_File_City(const string& INPUT_CITY_FILE_NAME, vector<City>& cities){
    ifstream file(INPUT_CITY_FILE_NAME);
    if(!file.is_open()){
        return 0;
    }

    string line;
    getline(file, line);

    while(getline(file, line)){
        City city;
        stringstream ss(line);
        string cell;
        for(int i=0; i<NUM_OF_FEATURE_CITY; i++){
            getline(ss, cell, ',');
            if(i==0) city.name = cell;
            if(i==1) city.distance = stoi(cell);
        }
        cities.push_back(city);
    }
    return 1;
}

void Set_Score(vector<Order>& orders){
    int largest_order_id = orders[orders.size()-1].id;
    for(int i=0; i<orders.size(); i++){
        orders[i].score = orders[i].weight + 5 *(largest_order_id - orders[i].id);
    }
}

City Find_City_With_Name(vector<City>& cities, string city_name){
    for(int i=0; i<cities.size(); i++){
        if(cities[i].name == city_name) return cities[i];
    }
}

void Set_Cost(vector<City>& cities, Order& order){
    string city_name;
    city_name = order.destination_city == TEHRAN ? order.origin_city : order.destination_city;
    City target_city = Find_City_With_Name(cities, city_name);
    order.cost = target_city.distance * order.weight;
}

void Add_Order(vector<Order>& orders, vector<City>& cities){
    Order new_order;
    string origin;
    string destination;
    int weight;
    cin >> origin >> destination >> weight;
    new_order.origin_city = origin;
    new_order.destination_city = destination;
    new_order.weight = weight;
    new_order.id = orders.size() + 1;
    orders.push_back(new_order);
    cout << "Order " << orders[orders.size() - 1].id << " added" << endl;
    Set_Score(orders);
    Set_Cost(cities, orders[orders.size() - 1]);
}

void Tracking_Order(vector<Order>& orders){
    int id;
    cin >> id;
    if(id < 1 || id > orders.size()){
        cout << "Order not found" << endl;
        return;
    }
    Order order = orders[id-1]; 
    if(!order.Is_delivered && !order.Is_In_Truck) 
        cout << "Order " << order.id << " is currently in warehouse in " << order.origin_city << endl;

    else if(!order.Is_delivered && order.Is_In_Truck)
        cout << "Order " << order.id << " is in transit to " << order.destination_city << endl;

    else if(order.Is_delivered)
        cout << "Order " << order.id << " is delivered to " << order.destination_city << endl;
}

Truck& Find_Truck(vector<Truck>& trucks, int& truck_id){
    for(int i=0; i<trucks.size(); i++){
        if(trucks[i].id == truck_id) return trucks[i];
    }
}

vector<Order> Find_Same_orig_dest_orders(vector<Order>& orders, string destination_city_truck, string origin_city_truck){
    vector<Order> Same_orig_dest_orders;
    for(int i=0; i<orders.size(); i++){
        if(!orders[i].Is_In_Truck && !orders[i].Is_delivered){
            if((orders[i].origin_city == origin_city_truck) && (orders[i].destination_city == destination_city_truck)){
                Order temp = orders[i];
                Same_orig_dest_orders.push_back(orders[i]);
            }
        }
    }
    return Same_orig_dest_orders;
}

void Sort_By_score(vector<Order>& target_orders){
    sort(target_orders.begin(), target_orders.end(), [](const Order& a, const Order& b){
        if(a.score != b.score){
            return a.score < b.score;
        }
        return a.id > b.id;
    });
}

void Sort_By_Id(vector<Order>& target_orders){
    sort(target_orders.begin(), target_orders.end(), [](const Order a, const Order b){
        return a.id < b.id;
    });
}

bool Has_Order(vector<Order>& Same_orig_dest_orders){
    return Same_orig_dest_orders.size() != 0;
}

void Initialize_Main_Orders_vector(vector<Order>& Same_orig_dest_orders, vector<Order>& orders){
    for(int i=0; i<Same_orig_dest_orders.size(); i++){
        for(int j=0; j<orders.size(); j++){
            if(Same_orig_dest_orders[i].id == orders[j].id) orders[j] = Same_orig_dest_orders[i];
        }
    }
}

void Truck_Loading(vector<Truck>& trucks, vector<Order>& orders){
    int truck_id;
    string destination_city_truck;
    vector<Order> Same_orig_dest_orders;
    cin >> truck_id >> destination_city_truck;
    Truck& truck = Find_Truck(trucks, truck_id);
    if((truck.Is_carrying) || (truck.curr_location == destination_city_truck)){
        cout << "No order could be loaded" << endl;
        return;
    }else if(truck.curr_location != TEHRAN && destination_city_truck != TEHRAN){
        cout << "No order could be loaded" << endl;
        return;
    }
    Same_orig_dest_orders = Find_Same_orig_dest_orders(orders, destination_city_truck, truck.curr_location);

    if(!Has_Order(Same_orig_dest_orders)){
        cout << "No order could be loaded" << endl;
        return;
    }else{
        Sort_By_score(Same_orig_dest_orders);
        for(int i = Same_orig_dest_orders.size()-1; i >= 0; i--){
            if(truck.curr_capacity - Same_orig_dest_orders[i].weight >= 0){
                Same_orig_dest_orders[i].Is_In_Truck = true;
                Same_orig_dest_orders[i].carrier_truck = &truck;
                truck.curr_capacity -= Same_orig_dest_orders[i].weight;
            }else{
                Same_orig_dest_orders.erase(Same_orig_dest_orders.begin() + i);
            }
        }
    }

    if(!Has_Order(Same_orig_dest_orders)){
        cout << "No order could be loaded" << endl;
        return;
    }else{
        truck.Is_carrying = true;
        truck.destination_city = destination_city_truck;
        Sort_By_Id(Same_orig_dest_orders);
        cout << "Truck " << truck_id << " loaded with orders:";
        for(int i=0; i<Same_orig_dest_orders.size(); i++){
            cout << " " << Same_orig_dest_orders[i].id;
        }
        cout << endl;
    }
    Initialize_Main_Orders_vector(Same_orig_dest_orders, orders);
}

void Set_Truck_deliver_orders_Mode(Truck& truck){

    truck.Is_carrying = false;
    truck.curr_location = truck.destination_city;
    truck.destination_city = "";
    truck.curr_capacity = truck.orig_capacity;
}

void Set_Orders_Delivered_Mode(vector<Order>& orders, int truck_id){
    for(int i=0; i<orders.size(); i++){
        if(orders[i].carrier_truck != nullptr){
            if(orders[i].carrier_truck->id == truck_id){
                orders[i].Is_In_Truck = false;
                orders[i].Is_delivered = true;
                orders[i].carrier_truck = nullptr;
                cout << " " << orders[i].id;
            }
        }
    }
}

bool Is_Truck_Empty(Truck& truck){
    return (truck.curr_capacity == truck.orig_capacity) && (!truck.Is_carrying);
}

void Deliver_Order(vector<Truck>& trucks, vector<Order>& orders){
    int truck_id;
    cin >> truck_id;
    Truck& truck = Find_Truck(trucks, truck_id);
    if(Is_Truck_Empty(truck)){
        cout << "No orders to deliver in truck " << truck_id << endl;
        return;
    }
    Set_Truck_deliver_orders_Mode(truck);
    cout << "Truck " << truck_id << " delivered orders:";
    Set_Orders_Delivered_Mode(orders, truck_id);
    cout << endl;
}

int Cal_SumOutgoingScores(vector<Order>& orders, string city_name){
    int sum = 0;
    for(int i=0; i<orders.size(); i++){
        if(orders[i].origin_city == city_name && orders[i].destination_city == TEHRAN && !orders[i].Is_delivered && !orders[i].Is_In_Truck) sum += orders[i].score;
    }
    return sum;
}

int Cal_SumIncomingScores(vector<Order>& orders, string city_name){
    int sum = 0;
    for(int i=0; i<orders.size(); i++){
        if(orders[i].origin_city == TEHRAN && orders[i].destination_city == city_name && !orders[i].Is_delivered && !orders[i].Is_In_Truck) sum += orders[i].score;
    }
    return sum;
}

float Cal_CityScore(vector<Order>& orders, City& city){
    return (float)(Cal_SumIncomingScores(orders, city.name) + Cal_SumOutgoingScores(orders, city.name)) / city.distance;
}

string toLower(string str){
    for(int i=0; i<str.length(); i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

City Best_Alpha(City& city1, City& city2){
    return toLower(city1.name) < toLower(city2.name) ? city1 : city2;
}

City Find_Best_City(vector<City>& cities){
    City best;
    City temp;
    best = cities[0];
    for(int i=1; i<cities.size(); i++){
        temp = cities[i];
        if(best.score < temp.score){
            best = temp;
        }else if(best.score == temp.score){
            best = Best_Alpha(best, temp);
        }
    }
    return best;
}

int Cal_SumOrdersIn_Tehran(vector<Order>& orders, string dest_city){
    int sum = 0;
    for(int i=0; i<orders.size(); i++){
        if(!orders[i].Is_In_Truck && !orders[i].Is_delivered){
            if(orders[i].origin_city == TEHRAN && orders[i].destination_city == dest_city){
                sum += orders[i].weight;
            }
        }
    }
    return sum;
}

vector<Truck> Find_TrucksIn_Tehran(vector<Truck>& trucks){
    vector<Truck> trucks_target;
    for(int i=0; i<trucks.size(); i++){
        if(trucks[i].curr_location == TEHRAN && !trucks[i].Is_carrying){
            trucks_target.push_back(trucks[i]);
        }
    }
    return trucks_target;
}

void Remove_trucksWith_Not_Enough_Capacity(vector<Truck>& trucks_target, int sum_weight_orders){
    for(int i=trucks_target.size()-1; i>=0; i--){
        if(trucks_target[i].orig_capacity - sum_weight_orders < 0){
            trucks_target.erase(trucks_target.begin() + i);
        }else{
            trucks_target[i].curr_capacity -= sum_weight_orders;
        }
    }
}

Truck Find_Truck_Lower_Capacity(vector<Truck>& trucksIn_tehran){
    sort(trucksIn_tehran.begin(), trucksIn_tehran.end(), [](const Truck& a, const Truck& b){
        if(a.curr_capacity != b.curr_capacity){
            return a.curr_capacity < b.curr_capacity;
        }
        return a.id < b.id;
    });
    return trucksIn_tehran[0];
}

void Recommender(vector<Truck>& trucks, vector<City>& cities, vector<Order>& orders){
    for(int i=0; i<cities.size(); i++){
        cities[i].score = Cal_CityScore(orders, cities[i]);
    }
    City best_city = Find_Best_City(cities);
    int sum_weight_ordersIn_tehran = Cal_SumOrdersIn_Tehran(orders, best_city.name);
    vector<Truck> trucksIn_tehran = Find_TrucksIn_Tehran(trucks);
    Remove_trucksWith_Not_Enough_Capacity(trucksIn_tehran, sum_weight_ordersIn_tehran);
    Truck best_truck = Find_Truck_Lower_Capacity(trucksIn_tehran);
    cout << "Recommended city: " << best_city.name << endl;
    cout << "Recommended truck: " << best_truck.id << endl;
}

void financial_report(vector<Order>& orders){
    vector<Order> delivered_orders;
    int total_income = 0;
    for(int i=0; i<orders.size(); i++){
        if(orders[i].Is_delivered){
            delivered_orders.push_back(orders[i]);
            total_income += orders[i].cost;
        }
    }
    cout << "Total income: " << total_income << endl;
    cout << "Delivered orders:" << endl;
    if(total_income > 0){
        for(int i=0; i<delivered_orders.size(); i++){
            cout << delivered_orders[i].id << " " << delivered_orders[i].cost << endl;
        }
    }
}

void Command_Recognition(string command, vector<Truck>& trucks, vector<City>& cities, vector<Order>& orders){
    if(command == "add_order") Add_Order(orders, cities);
    if(command == "track") Tracking_Order(orders);
    if(command == "load") Truck_Loading(trucks, orders);
    if(command == "deliver") Deliver_Order(trucks, orders);
    if(command == "recommend") Recommender(trucks, cities, orders);
    if(command == "financial_report") financial_report(orders);
}

void Recieve_Commands(vector<Truck>& trucks, vector<City>& cities, vector<Order>& orders){
    string command;
    while(cin >> command){
        Command_Recognition(command, trucks, cities, orders);
    }
}

int main(int argc, char* argv[]){
    if(argc != 3){
        cerr << "Exactly two arguments must be entered !" << endl;
        return 1;
    }
    const string INPUT_TRUCK_FILE_NAME = argv[1];
    const string INPUT_CITY_FILE_NAME = argv[2];
    vector<Truck> trucks;
    vector<City> cities;
    vector<Order> orders;
    if(!OpenRead_CSV_File_Truk(INPUT_TRUCK_FILE_NAME, trucks)) cerr << "The file could not be opened" << endl;
    if(!OpenRead_CSV_File_City(INPUT_CITY_FILE_NAME, cities)) cerr << "The file could not be opened" << endl;
    Recieve_Commands(trucks, cities, orders);
    return 1;
}
