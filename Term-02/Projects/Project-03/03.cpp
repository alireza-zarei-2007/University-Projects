#include <iostream>
#include <string>
using namespace std;
bool Is_Alpha(const string& S, int& cursor){
    char ch = S[cursor];
    if((ch >= 'a') && (ch <= 'z')){
        return true;
    }
    if((ch >= 'A') && (ch <= 'Z')){
        return true;
    }else{
        return false;
    }
}
bool Is_Integer(const string& S, int cursor){
    char ch = S[cursor];
    if((ch >= '0') && (ch <= '9')){
        return true;
    }else{
        return false;
    }
}
void readNumber(const string& s, int& index, int& num) {
    if (index >= s.length() || !isdigit(s[index])) {
        return;
    }
    
    num = num * 10 + (s[index] - '0');
    index++;
    readNumber(s, index, num);
}
int ReadNum(const string& S, int cursor2, int& cursor, int& num){
    num += S[cursor2]-'0';
    if(Is_Integer(S, cursor2+1)){
        num = num*10;
        return ReadNum(S, cursor2+1, cursor, num);
    }else{
        cursor = cursor2+1;
        return num;
    }
}
string Rewrite_The_Bracket(string str_loop, int Num_Of_Loop){
    if(Num_Of_Loop == 0) return "";
    return str_loop + Rewrite_The_Bracket(str_loop, Num_Of_Loop-1);
}
string Decoder(const string& S, int& cursor){
    if((S[cursor] == '\0') || (S[cursor] == ']')) return "";
    if(Is_Alpha(S, cursor)){
        string ch;
        ch =S[cursor];
        cursor++;
        return ch + Decoder(S, cursor);
    }
    if(Is_Integer(S, cursor)){
        int num=0;
        int Num_Of_Loop = ReadNum(S, cursor, cursor, num);
        cursor++;
        string str_loop = Decoder(S, cursor);
        cursor++;
        return Rewrite_The_Bracket(str_loop, Num_Of_Loop) + Decoder(S, cursor);
    }
}
int main(){
    string S;
    while(cin >> S){
        int cursor = 0;
        cout << Decoder(S, cursor) << endl;
    }
    return 0;
}