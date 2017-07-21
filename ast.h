#ifndef AST_H_
#define AST_H_

#include <map>
using std::map;
#include <list>
using std:: list;
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;

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
