#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <list>
#include <algorithm>
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
    virtual void Print() {
        cout << "( ";
        for (std::map<string, JsonValue*>::iterator it = pairs.begin(); it!=pairs.end(); ++it){
            cout << it->first << " ";
            (it->second)->Print();
        }
        cout << " ) ";
    }
    JsonObject() {}
    void Add(string name, JsonValue* value){
        pairs[name] = value;
    }
};

class JsonArray : public JsonValue
{
private:
    list<JsonValue*> values;
    
public:
    virtual void Print(){
        cout << "( ";
        for (std::list<JsonValue*>::iterator it=values.begin(); it != values.end(); ++it){
            (*it)->Print();
            cout << " ";
        }
        cout << ") ";
    }
    void Add(JsonValue *v) {
        values.push_back(v);
    }
};

class JsonString : public JsonValue
{
private:
    string value;
    
public:
    JsonString(string s) : value(s) { };
    virtual void Print() { cout << "( string " << value << " ) "; }
};

class JsonNumber : public JsonValue
{
private:
    double value;
    
public:
    JsonNumber(double d) : value(d) { };
    virtual void Print() { cout << "( number " << value << " ) "; }
};

class JsonBoolean : public JsonValue
{
private:
    bool value;
    
public:
    JsonBoolean(bool b) : value(b) { };
    virtual void Print() {
        cout << " ( boolean ";
        if (value)
            cout << "true";
        else
            cout << "false";
        cout << " ) ";
    }
};

class JsonNull : public JsonValue
{
public:
    virtual void Print() { cout << "( null ) "; }
};

#endif // AST_H_


int main(){
    string line, str, value, inside;
    int arr_size;
    ifstream myfile("/Users/Joey/Documents/CPSC 332/Assignment 2/Assignment 2/Untitled.json");
    
    JsonObject* o = new JsonObject();
    JsonArray *a = new JsonArray();

    
    if(myfile.is_open()){
        while(getline(myfile, line)){
        
            cout << line << endl;
        
            if(regex_match(line, regex("(.*): \".*"))){
                str = line.substr(line.find('"'), line.find(':')-line.find('"'));
                value = line.substr(line.find(": ")+2, line.find(',')-(line.find(": ")+2));
                o->Add(str, new JsonString(value));
            }
            
            
            if(regex_match(line, regex("(.*): [0-9]+.*"))){
                str = line.substr(line.find('"'), line.find(':')-line.find('"'));
                value = line.substr(line.find(": ")+2, line.find(',')-(line.find(": ")+2));
                o->Add(str, new JsonString(value));
            }
            if(regex_match(line, regex("(.*): (true|false).*"))){
                str = line.substr(line.find('"'), line.find(':')-line.find('"'));
                value = line.substr(line.find(": ")+2, line.find(',')-(line.find(": ")+2));
                o->Add(str, new JsonString(value));
            }
            if(regex_match(line, regex("(.*): null.*"))){
                str = line.substr(line.find('"'), line.find(':')-line.find('"'));
                value = line.substr(line.find(": ")+2, line.find(',')-(line.find(": ")+2));
                o->Add(str, new JsonString(value));
            }
            if(regex_match(line, regex("(.*): \\[.*\\].*"))){
                str = line.substr(line.find('"'), line.find(':')-line.find('"'));
                arr_size = count(line.begin(), line.end(), ',')+1;
                line = line.substr(line.find('['), line.find("],") - line.find('['));
                cout << line << endl;
               
            }

        }
    }
    else{
        cout << "didn't open\n";
    }
    
    cout << endl << endl;
    
    o->Print();
    
    return 0;
}
