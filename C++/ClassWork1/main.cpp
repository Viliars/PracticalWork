#include <iostream>
#include<vector>
#include<cstdlib>
#include<cstring>

namespace session
{

class event
{
protected:
int len_data;
int len_name;
public:
    char* data;
    char* name;
    event(const char* data,const char* name)
    {
    this->len_data=strlen(data); this->data=new char[this->len_data]; strcpy(this->data,data);
    this->len_name=strlen(name); this->name=new char[this->len_name]; strcpy(this->name,name);
    }
     virtual void print_res()=0;
    virtual ~event()
    {
        delete[] name;
        delete[] data;
    }
};

class test:public event
{
protected:
    int len_ex;
public:
    char* ex;
    bool dif;
test(const char* data,const char* name,const char* ex,bool dif): event(data,name)
{
    this->len_ex=strlen(ex); this->ex=new char[this->len_ex]; strcpy(this->ex,ex);
    this->dif=dif;
}
virtual void print_res()
{
    std::cout<<"Data = "<<data<<std::endl<<"Name of teacher = "<<name<<std::endl<<"Name of Test = "<<ex<<std::endl;
    std::cout<<(dif ? "Differential": "NoDifferential")<<std::endl<<std::endl;
}
virtual ~test() { delete[] ex;  }
};

class exam:public event
{
    protected:
    int len_ex;
public:
    char* ex;
    static int count;
exam(const char* data,const char* name,const char* ex): event(data,name)
{
    this->len_ex=strlen(ex); this->ex=new char[this->len_ex]; strcpy(this->ex,ex);
    count++;
}
virtual void print_res()
{
    std::cout<<"Data = "<<data<<std::endl<<"Name of teacher = "<<name<<std::endl<<"Name of Exam = "<<ex<<std::endl;
    std::cout<<"This exam is "<<count<<std::endl<<std::endl;
}
virtual ~exam() { delete[] ex;  }
};

int exam::count=0;
}

using namespace session;
using namespace std;
int main()
{
    vector<event* > a(5);
    a[0]=new test("27.03.2018","Feduchi N.M","MATHAN",true);
    a[1]=new exam("05.04.2018","Drus A.V","English");
    a[2]=new test("12.03.2018","Vredo M.A","Linal",false);
    a[3]=new exam("07.04.2018","Vredo A.M","Bibliography");
    a[4]=new test("29.03.2018","Stanichev V.V","System of programming",true);

    for(auto v:a) v->print_res();
    return 0;
}
