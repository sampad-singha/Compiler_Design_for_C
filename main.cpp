#include "bits/stdc++.h"
using namespace std;
bool isSeparator(char ch){
    string Separator = " ,;(){}[]";
    for(auto i:Separator){
        if(ch==i)return true;
    }
    return false;
}
bool isOperator(char ch){
    string Operator = "+-*/%<>=!";
    for(auto i:Operator){
        if(ch==i)return true;
    }
    return false;
}
bool isKeyword(string s){
    regex rgx("\\b(char|int|return|if|else|for)\\b");
    if(regex_match(s,rgx))return true;
    return false;
}
bool isConstant(string s){
    regex  rgx("^([+-]?[0-9]+)");
    if(regex_match(s,rgx))return true;
    return false;
}
bool isIdentifier(string s){
    regex rgx("\\b([a-zA-z_]+[a-zA-Z_0-9]*)\\b");

}
void parse(const string& s){
    vector <string> tokens;
    string token;
    for(auto i:s){
        if(isSeparator(i)){
            if(!token.empty())
                tokens.push_back(token);
            token="";
        }
        else if(isOperator(i)){
            if(!token.empty()){
                tokens.push_back(token);
                token="";
            }
            token.push_back(i);
            tokens.push_back(token);
            token="";
        }
        else{
            token.push_back(i);
        }
    }
    if(!token.empty()){
        tokens.push_back(token);
    }

    for(const auto& i:tokens){
        cout<<i<<endl;
    }

}
int main(){
    ifstream file("source.txt");
    string line;
    while(getline(file,line)){
        parse(line);
    }

    file.close();

    return 0;
}