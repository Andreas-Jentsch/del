#include "t_del.h"
//-------------------------------------------------------------------------
void t_del::del_control_chars(std::bitset<8> Set)
{
    if(Set.test(0)) {
        this->_control_chars[0] = 0x0A; // lf
    }
    if(Set.test(1)) {
        this->_control_chars[1] = 0x0D; // cr
    }
    if(Set.test(2)) {
        this->_control_chars[2] = 0x09; // ht
    }
    if(Set.test(3)) {
        this->_control_chars[3] = 0x20; // sp
    }


    std::vector<int> p;
    for(int i = 0;i < this->_bufsize;i++)
    {
        for(int c = 0;c < CONTROL_CHARS_SIZE;c++)
        {
            if((this->line[i] == this->_control_chars[c]) && (this->_control_chars[c] != '\0')) {
                p.push_back(i);
            }
        }
    }
    int size = p.size();


    bool f = false;
    for(int i = 0;i < this->_bufsize;i++)
    {
        for(unsigned int c = 0;c < size;c++)
        {
            if(i == p[c]) {
                f = true;
            }
        }

        if(!f && this->line[i] != '\0') {
            this->_tmp[i] = this->line[i];
        }
        else {
            f = false;
        }
    }


    this->_adjust_arrays();
}
//-------------------------------------------------------------------------
void t_del::trim(std::bitset<8> Set)
{
    int pb = -1,pe = -1;
    if(Set.test(4))
    {
        for(int i = 0;i < this->_bufsize;i++)
        {
            if((isalpha(this->line[i])) || (isdigit(this->line[i])) || (ispunct(this->line[i])))
            {
                pb = i;
                i = BUFSIZE;
            }
        }
    }
    else {
        pb = 0;
    }


    if(Set.test(5))
    {
        for(int i = this->_bufsize - 1;i >= 0;i--)
        {
            if((isalpha(this->line[i])) || (isdigit(this->line[i])) || (ispunct(this->line[i])))
            {
                pe = i;
                i = -1;
            }
        }
    }
    else {
        pe = this->_bufsize - 1;
    }


    if(pb >= 0 && pe > 0)
    {
        for(int i = pb;i <= pe;i++)
        {
            if(this->line[i] != '\0') {
                this->_tmp[i] = this->line[i];
            }
        }
    }


    this->_adjust_arrays();
}
//-------------------------------------------------------------------------
void t_del::del_sign_at(const int& Pos)
{
    for(int i = 0;i < this->_bufsize;i++)
    {
        if((i != Pos) && (this->line[i] != '\0')) {
            this->_tmp[i] = this->line[i];
        }
    }


    this->_adjust_arrays();
}
//-------------------------------------------------------------------------
void t_del::del_sign_at_if(const int& Pos,const char& Sign)
{
    for(int i = 0;i < this->_bufsize;i++)
    {
        if((i != Pos) && (this->line[i] != '\0')) {
            this->_tmp[i] = this->line[i];
        }
        else if((i == Pos) && (this->line[i] != Sign)) {
            this->_tmp[i] = this->line[i];
        }
    }


    this->_adjust_arrays();
}
//-------------------------------------------------------------------------
void t_del::set_bufsize()
{
    for(int i = 0;i < BUFSIZE;i++)
    {
        if(this->line[i] == '\0')
        {
            this->_bufsize = i + 1;
            i = BUFSIZE;
        }
    }
}
//-------------------------------------------------------------------------
t_del::t_del()
{
    // init
    memset(this->data,0,BUFSIZE);
    memset(this->line,0,BUFSIZE);
    memset(this->_tmp,0,BUFSIZE);

    this->_control_chars[0] = 0;
    this->_control_chars[1] = 0;
    this->_control_chars[2] = 0;
    this->_control_chars[3] = 0;
}
//-------------------------------------------------------------------------
t_del::~t_del()
{
    //
}
//-------------------------------------------------------------------------
void t_del::_adjust_arrays()
{
    std::vector<char> t;
    for(int i = 0;i < this->_bufsize;i++)
    {
        if(this->_tmp[i] != '\0') {
            t.push_back(this->_tmp[i]);
        }
    }
    memset(this->data,0,BUFSIZE);
    memset(this->line,0,BUFSIZE);
    memset(this->_tmp,0,BUFSIZE);


    for(unsigned int i = 0;i < t.size();i++)
    {
        this->data[i] = t[i];
        this->line[i] = t[i];
    }


    this->set_bufsize();
}
//-------------------------------------------------------------------------