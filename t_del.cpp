#include "t_del.h"
//-------------------------------------------------------------------------
void t_del::del_control_chars()
{
    for(t_data::iterator i = this->data.begin();i != this->data.end();i++)
    {
        for(int c = 0;c < CONTROL_CHARS_SIZE;c++)
        {
            if((*i == this->_control_chars[c]) && (this->_control_chars[c] != '\0')) {
                i = this->data.erase(i) - 1;
            }
        }
    }
    this->set_bufsize();
}
//-------------------------------------------------------------------------
void t_del::trim(bool left,bool right)
{
    if(left)
    {
        for(t_data::iterator i = this->data.begin();i != this->data.end();i++)
        {
            if((isalpha(*i)) || (isdigit(*i)) || (ispunct(*i)))
            {
                this->data.erase(this->data.begin(),i);
                break;
            }
        }
    }


    if(right)
    {
        if(left) {
            this->set_bufsize();
        }
        for(int i = (this->_bufsize - 1);i >= 0;i--)
        {
            if((isalpha(this->data[i])) || (isdigit(this->data[i])) || (ispunct(this->data[i])))
            {
                this->data.erase(this->data.begin() + (i + 1),this->data.end());
                break;
            }
        }
    }
    this->set_bufsize();
}
//-------------------------------------------------------------------------
void t_del::del_sign_at(const int& Pos)
{
    this->data.erase(this->data.begin() + Pos);
    this->set_bufsize();
}
//-------------------------------------------------------------------------
void t_del::del_sign_at_if(const int& Pos,const char& Sign)
{
    t_data::iterator i = this->data.begin() + Pos;
    if(*i == Sign) {
        this->data.erase(i);
    }
    this->set_bufsize();
}
//-------------------------------------------------------------------------
void t_del::set_bufsize()
{
    /*for(int i = 0;i < BUFSIZE;i++)
    {
        if(this->line[i] == '\0')
        {
            this->_bufsize = i + 1;
            i = BUFSIZE;
        }
    }*/
    this->_bufsize = this->data.size();
}
//-------------------------------------------------------------------------
void t_del::set_control_char(char sign)
{
    this->_control_chars[this->_control_chars_count] = sign;
    this->_control_chars_count++;
}
//-------------------------------------------------------------------------
int t_del::control_chars_count()
{
    return this->_control_chars_count;
}
//-------------------------------------------------------------------------
t_del::t_del()
{
    // init
    //memset(this->data,0,BUFSIZE);
    memset(this->line,0,BUFSIZE);
    memset(this->_tmp,0,BUFSIZE);
    memset(this->_control_chars,0,CONTROL_CHARS_SIZE);

    this->_control_chars_count = 0;
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
    //memset(this->data,0,BUFSIZE);
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