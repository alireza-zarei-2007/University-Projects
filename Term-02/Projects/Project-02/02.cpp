#include <iostream>
#include <string>
using namespace std;

bool Is_palindrome(string& input_string, int cursor_start, int cursor_end){
    if(!(isalpha(input_string[cursor_start]))){
        return Is_palindrome(input_string,cursor_start+1,cursor_end);
    }
    if(!(isalpha(input_string[cursor_end]))){
        return Is_palindrome(input_string,cursor_start,cursor_end-1);
    }
    if(cursor_end <= cursor_start){
        return true;
    }
    if(tolower(input_string[cursor_start]) == tolower(input_string[cursor_end])){
        return Is_palindrome(input_string,cursor_start+1 ,cursor_end-1);
    }else {
        return false;
    }
}
void Is_palindrome_answer(){
    string input_string;
    int cursor_end;
    int cursor_start = 0;
    int NumOfLines = 0;
    cin >> NumOfLines;
    cin.ignore();
    if(NumOfLines < 1){
        cout << "No input recieved" << endl;
    }
    while(NumOfLines){
        getline(cin, input_string);
        cursor_end = input_string.length() - 1;
        if(Is_palindrome(input_string, cursor_start, cursor_end)){
            cout << "yes";
        }else{
            cout << "no";
        }
        if(NumOfLines != 1){
            cout << '\n';
        }
        NumOfLines--;
    }
}
int main(){
    Is_palindrome_answer();
    return 0;
}