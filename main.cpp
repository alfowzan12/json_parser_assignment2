#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <list>
using namespace std;

#ifndef AST_H_
#define AST_H_

class JsonValue
{
public:
    virtual void Print() = 0;
};

class JsonObject : public JsonValue
{
private:
    map<string, JsonValue*> pairs;
    
public:
    virtual void Print();
    void Add(string name, JsonValue* value){
        pairs.insert(pair<string, JsonValue*>(name, value));
    };
};

class JsonArray : public JsonValue
{
private:
    list<JsonValue*> values;
    
public:
    virtual void Print();
    void Add(JsonValue *v){
        
    };
};

class JsonString : public JsonValue
{
private:
    string value;
    
public:
    JsonString(string s) : value(s) { };
    virtual void Print();
};

class JsonNumber : public JsonValue
{
private:
    double value;
    
public:
    JsonNumber(double d) : value(d) { };
    virtual void Print();
};

class JsonBoolean : public JsonValue
{
private:
    bool value;
    
public:
    JsonBoolean(bool b) : value(b) { };
    virtual void Print();
};

class JsonNull : public JsonValue
{
public:
    virtual void Print();
};

#endif // AST_H_


int main(){
    string line;
    ifstream myfile("/Users/Joey/Documents/CPSC 332/Assignment 2/Assignment 2/Untitled.json");
    if(myfile.is_open()){
//        while(getline(myfile, line)){
//            cout << line << endl;
//            if(line[0] == '{' || line[0] == '}'){
//                cout << "boop\n";
//            }
//            if(regex_match(line, regex("(.*): \".*"))){
//                cout << "str matched\n";
//            }
//            if(regex_match(line, regex("(.*): [0-9]+.*"))){
//                cout << "num matched\n";
//            }
//            if(regex_match(line, regex("(.*): (true|false).*"))){
//                cout << "bool matched\n";
//            }
//            if(regex_match(line, regex("(.*): null.*"))){
//                cout << "nul matched\n";
//            }
//            if(regex_match(line, regex("(.*): \\[.*\\].*"))){
//                cout << "arr matched\n";
//            }
//        }
        JsonObject* o = new JsonObject();
        o->Add("str", new JsonString("foo"));
        o->Add("num", new JsonNumber(123));
        o->Add("bool", new JsonBoolean(true));
        o->Add("nul", new JsonNull());

    }
    else{
        cout << "didn't open\n";
    }
    return 0;
}
