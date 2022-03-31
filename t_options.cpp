#include "t_options.h"

void t_options::parse(int Argc,char** Argv)
{
    if(this->popts.size() == 0)
    {
        std::cout << "Warning: The Array t_options::popts is empty." << std::endl;
        std::cout << "  Use obj->popts.insert(std::make_pair(std::string,bool))" << std::endl;
        return;
    }


    std::string tmp;
    for(int i = 0;i < Argc;i++)
    {
        tmp = Argv[i];
        if(tmp.length() >= 2 && tmp[0] == '-')
        {
            for(int c = 0;c < this->popts.size();c++)
            {
                if((tmp == popts[c]->longname || tmp == popts[c]->shortname) && !popts[c]->val_required) {
                    this->map.insert(std::make_pair(popts[c]->longname,"-n"));
                }
                if((tmp == popts[c]->longname || tmp == popts[c]->shortname) && popts[c]->val_required)
                {
                    if(((i + 1) < Argc) && std::string(Argv[i + 1])[0] != '-') {
                        this->map.insert(std::make_pair(popts[c]->longname,std::string(Argv[i + 1])));
                    }
                    else
                    {
                        std::string option = (popts[c]->longname.length() > 0) ? popts[c]->longname : popts[c]->shortname;
                        std::cout << _msg[0] << option << std::endl;
                        std::cout << "  Negative numbers are not allowed. Or a value is missing." << std::endl;
                    }
                }
            }
        }
    }
    int breakpoint = 1;
}

t_options::t_options()
{
    this->_msg[0] = "Syntax error: Error near ";
}
t_options::~t_options()
{
    for(int i = 0;i < this->popts.size();i++)
    {
        if(this->popts[i] != NULL)
        {
            delete this->popts[i];
        }
    }
    this->popts.clear();
}