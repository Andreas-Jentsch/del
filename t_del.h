#ifndef t_delH
#define t_delH
//-------------------------------------------------------------------------
#include <vector>
#include <cstring>      // memset
#include <iostream>
//#include <bitset>
#include <iomanip>      // setw()
//-------------------------------------------------------------------------
typedef std::vector<char> t_data;
//-------------------------------------------------------------------------
const int BUFSIZE = 2048;
const int CONTROL_CHARS_SIZE = 4;
//-------------------------------------------------------------------------
//enum t_direction {left,right,both};
enum t_cc {lf,cr,ht,sp,all};
//-------------------------------------------------------------------------
class t_del
{
public:
    //char data[BUFSIZE];
    t_data data;
    char line[BUFSIZE];

    void del_control_chars();
    void trim(bool left,bool right);
    void del_sign_at(const int& Pos);
    void del_sign_at_if(const int& Pos,const char& Sign);
    void set_bufsize();
    void set_control_char(char sign);
    int  control_chars_count();

    t_del();
    ~t_del();


private:
    int _bufsize;
    int _control_chars_count;
    char _control_chars[CONTROL_CHARS_SIZE];
    char _tmp[BUFSIZE];

    void _adjust_arrays();
};
//-------------------------------------------------------------------------
#endif