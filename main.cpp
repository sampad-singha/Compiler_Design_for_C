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
bool isIdentifier(string s,vector<pair<string,string>>& table){
    regex rgx("\\b([a-zA-z_]+[a-zA-Z_0-9]*)\\b");
    bool flag = true;
    if(isKeyword(s)){
        //push to keyword table
        table.push_back(make_pair(s,"keyword"));
        flag = false;
        return false;
    } else if(isConstant(s)){
        //push to constant table
        table.push_back(make_pair(s,"constant"));
        flag = false;
        return false;
    }else if(isOperator(s[0])){
        //push to operator table
        table.push_back(make_pair(s,"operator"));
        flag = false;
        return false;
    }else if(regex_match(s,rgx)){
        //push to identifier table
        table.push_back(make_pair(s,"identifier"));
        return true;
    }
    cout<<"Invalid token: "<<s<<endl;
    return false;


}
void parse(const string& s,vector<pair<string,string>>& table){
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
        //cout<<i<<endl;
        isIdentifier(i,table);
    }

}
int main(){
    vector<pair<string,string>> table;
    ifstream file("source.txt");
    string line;
    while(getline(file,line)){
        parse(line,table);
    }

    file.close();
    cout<<"Table: "<<endl;
    for(auto i:table){
        cout<<i.first<<"\t"<<i.second<<endl;
    }

    return 0;
}