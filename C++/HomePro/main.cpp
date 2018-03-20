#include <iostream>
#include<string>
#include<cstdlib>
#include<cstring>
#include <ctime>
namespace unix{

class nix
{
protected:
    int len_name;
public:
    int year;
    char* name;
    virtual void info()=0;
    nix(const char* name,int year ){ this->len_name=strlen(name); this->name=new char[this->len_name]; strcpy(this->name,name); this->year=year; std::cout<<"Kernel created"<<std::endl; }
    virtual ~nix() { delete[] name; std::cout<<"DELETE KERNEL"<<std::endl; }
};


class Unix:public virtual nix
{
protected:
    int len_version;
public:
    char* version;
    void info() { std::cout<<"I am "<<name<<" "<<version<<std::endl; }
    Unix(const char* version,int year,const char* name="Unix"): nix(name,year)
    {
        len_version=strlen(version); this->version=new char[len_version]; strcpy(this->version,version); std::cout<<"Unix created"<<std::endl;
    }
    Unix& operator=(const Unix& another)
    {
        if(another.len_name!=this->len_name) {  this->len_name=another.len_name; delete[] this->name; this->name=new char[this->len_name]; } strcpy(this->name,another.name);
        if(another.len_version!=this->len_version) {  this->len_version=another.len_version; delete[] this->version; this->version=new char[this->len_version]; } strcpy(this->version,another.version);
        return *this;
    }
    virtual ~Unix() { delete[] version; std::cout<<"DELETE_UNIX "<<name<<" "; }
};


class BSD:public virtual nix
{
public:
    int version;
    int year;
    void info() { std::cout<<"I am "<<version<<name<<std::endl; }
    BSD(int version,int year,const char* name="BSD"): nix(name,year) { this->version=version; std::cout<<"BSD created"<<std::endl; }
    virtual ~BSD() { std::cout<<"DELETE_BSD "<<name<<" ";  }
};


class NewBSD:public BSD
{
protected:
    int len_ver;
public:
    char* ver;
    void info() { std::cout<<"I am "<<ver<<name<<" "<<version<<std::endl;  }
    NewBSD(const char* ver,int version,int year,const char* name="BSD"): nix(name,year),BSD(version,year,name)
    {
       this->len_ver=strlen(ver); this->ver=new char[this->len_ver]; strcpy(this->ver,ver);
    }
    ~NewBSD() { delete[] ver;
    std::cout<<"DELETE_NEW ";}
};


class NewUnix:public Unix,public BSD
{
public:
    void info() { std::cout<<"I am "<<BSD::version<<name<<" "<<Unix::version<<std::endl; }
    static int count;
    NewUnix(const char* version,int year,const char* name="Unix",int ver=1): nix(name,year), Unix(version,year,name), BSD(ver,year,name) {
        count++;
    }
    ~NewUnix() {   std::cout<<"DELETE_NEW2 "; }
};


int NewUnix::count=0;
}
namespace win{


class Win{
protected:
    int len_name;
public:
    char* name;
    int bit;
    Win(const char* name,int bit=64)
    {
        this->len_name=strlen(name); this->name=new char[this->len_name]; strcpy(this->name,name);
        if(bit==64||bit==32) this->bit=bit;
        else throw 2;
        std::cout<<"Win created"<<std::endl;
    }
    virtual ~Win() { delete[] name; std::cout<<"DELETE WIN"<<std::endl; }
    // methods
    void run(int how)
    {
        try
        {
            for(int i=0;i<how;i++)
            {
                std::srand(unsigned(std::time(0)));
                int random_variable = std::rand();
                random_variable%=3;
                if(!random_variable) throw 3;
            }
        }
        catch(...)
        {
            std::cout<<"WINDOWS FELL BLUE SCREEN ERROR"<<std::endl;
        }
    }
};
}
namespace mac{
class Mac{
protected:
    int len_name;
    char* name;
    public:
    Mac(const char* name="MacOS")
    {
        this->len_name=strlen(name); this->name=new char[this->len_name]; strcpy(this->name,name);
        std::cout<<"MacOS created"<<std::endl;
    }
    virtual ~Mac()
    {
        delete[] name;
        std::cout<<"DELETE MAC"<<std::endl;
    }
};
}


using namespace std;
using namespace unix;
using namespace win;
using namespace mac;
int main()
{
    setlocale(LC_ALL, "rus");
    Unix V0("PDP7",1969,"Unics");
    Unix V1("Version 1",1971,"Unix");
    Unix V2("Version 2",1972);
    Unix V3("Version 3",1973);
    Unix V4("Version 4",1973);
    Unix V5("Version 5",1974);
    Unix V6("PWB",1974);
    Unix V7("Version 6",1975);
    BSD B0(1,1978);
    BSD B1(2,1979);
    NewBSD B3("Net",1,1993);
    NewBSD B4("Net",3,2005);
    NewBSD B5("Open",2,1996);
    NewBSD B6("Open",3,2006);
    NewBSD B7("Free",1,1993);
    NewBSD B8("Free",2,1995);
    NewBSD B9("Free",3,1998);
    NewBSD B10("Free",6,2006);
    Unix L0("0.0.1",1991,"Linux");
    Unix L1("GNU",1983,"Linux");
    NewUnix NU0("Version 8",1985,"Unix",8);
    Mac M0("MacOS");
try
{
    Win W0("Windows 10",32);
    W0.run(200);
}
catch(...) {  cout<<"!!! ERROR !!!"<<endl; }
    return 0;
}
