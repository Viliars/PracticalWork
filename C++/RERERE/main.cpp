#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<cstring>
using namespace std;


namespace library
{
// Classes
class Journal;
class Book;
class Test;
class Author;
class Base;

class Test
{
public:
static std::vector<int> a;
static bool find(int num)
{
    auto v=std::find(a.begin(),a.end(),num);
    if(v!=a.end()) return true;
    return false;
}
static void add(int num)
{
    a.push_back(num);
}
};



class Base
{
protected:
    int longer;
public:
    char* ISBN;
    int author;
    void TestISBN() throw(int)
    { //2-266-11156
        if(ISBN[1]!='-'||ISBN[5]!='-') throw 1;
    }
    void TestNumber() throw(int)
    {
        if(!Test::find(author)) throw 2;
    }
    Base(const char* ISBN,int author) throw(int)
    {
        this->longer=strlen(ISBN); this->ISBN=new char[this->longer]; strcpy(this->ISBN,ISBN);
        TestISBN();
        this->author=author; TestNumber();
    }
    Base(const Base& another)
    {
        this->longer=strlen(another.ISBN);
       delete[] this->ISBN;
       this->ISBN=new char[this->longer];
       strcpy(this->ISBN,another.ISBN);
    }
    virtual ~Base() { delete[] ISBN; }
    virtual void info()=0;
};

class Author
{
private:
    int lf;
    int ls;
public:
    int number;
    char* first_name;
    char* second_name;
Author(const char* first_name,const char* second_name,int num) throw(int)
{
    this->lf=strlen(first_name); this->first_name=new char[this->lf]; strcpy(this->first_name,first_name);
    this->ls=strlen(second_name); this->second_name=new char[this->ls]; strcpy(this->second_name,second_name);
    if(Test::find(num)) throw 3;
    this->number=num;
    Test::add(num);
}
~Author() { delete[] first_name; delete[] second_name; }
};



class Book:public Base
{
protected:
    int name_len;
public:
    char* name;
    int year;
    Book(const char* ISBN,int author,const char* name,int year): Base(ISBN,author)
    {
       this->name_len=strlen(name); this->name=new char[this->name_len]; strcpy(this->name,name);
       this->year=year;
    }
    Book(const Book& another): Base(another)
    {
       this->name_len=strlen(another.name);
       delete[] this->name;
       this->name=new char[this->name_len];
       strcpy(this->name,another.name);
       this->year=another.year;
    }
    Book& operator=(const Book& another)
    {
       this->name_len=strlen(another.name);
       delete[] this->name;
       this->name=new char[this->name_len];
       strcpy(this->name,another.name);
       this->year=another.year;
       this->longer=strlen(another.ISBN);
       delete[] this->ISBN;
       this->ISBN=new char[this->longer];
       strcpy(this->ISBN,another.ISBN);
       return *this;
    }
    virtual ~Book() { delete[] name; }
    virtual void info() {  std::cout<<"------------"<<endl<<"Name = "<<name<<endl<<"Year = "<<year<<endl<<"ISBN = "<<ISBN<<endl<<"------------"<<endl; }
};

class Journal:public Book
{
protected:
    int len_publ;
public:
    int serial;
    int circulation;
    char* publ;
    Journal(const char* ISBN,int author,const char* name,int year,int serial,int circulation,const char* publ): Book(ISBN,author,name,year)
    {
        this->len_publ=strlen(publ); this->publ=new char[this->len_publ]; strcpy(this->publ,publ);
        this->serial=serial;
        this->circulation=circulation;
    }
    Journal(const Journal& another) : Book(another)
    {
        this->len_publ=strlen(another.publ);
       delete[] this->publ;
       this->publ=new char[this->len_publ];
       strcpy(this->publ,another.publ);
       this->serial=another.serial;
        this->circulation=another.circulation;
    }
    virtual ~Journal() {  delete[] publ; }
    virtual void info()
    {
        std::cout<<"------------"<<endl<<"Name = "<<name<<endl<<"Year = "<<year<<endl<<"ISBN = "<<ISBN<<endl<<"Publishing house = "<<publ<<endl<<"Serial = "<<serial<<endl<<"------------"<<endl;
    }
};



std::vector<int> Test::a;
}

using namespace std;
using namespace library;
int main()
{
try
{
    Author Alex("Alex","Perch",4);
    Author Misha("Michael","Risher",5);
    Author Vika("Vika","Egorova",2);
    Author You("Yolia","Vampir",3);
    Book first("2-266-11156",4,"Creator of World",2018);
    first.info();
    Book second("2-366-13256",5,"Death",2009);
    second.info();
    second=first;
    second.info();
    Base* der=new Book("2-666-22236",2,"Don`t hold you breath",2013);
    der->info();
    Base* jor=new Journal("7-636-21136",3,"Be or not to be",1999,5,7,"VMK");
    jor->info();
}
catch(int x) { cout<<"ERROR "<<x<<endl; }
catch(...) { cout<<"ERROR"<<endl;  }
return 0;
}
