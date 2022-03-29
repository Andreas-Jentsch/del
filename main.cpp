
#include "t_del.h"
//-------------------------------------------------------------------------
t_del* del = nullptr;
const int PO_SIZE = 22;
const int ERROR_MSG_ARRAY_SIZE = 7;
std::string E_MSG[ERROR_MSG_ARRAY_SIZE];
//-------------------------------------------------------------------------
// possible options
const std::string PO[PO_SIZE] = \
{ \
    "--lf","--cr","--ht","--sp", \
    "--trim-left","--trim-right","--del-sign-at","--if", \
    "--del-last-lf","--help","--version" \
};
//-------------------------------------------------------------------------
void free_memory();
void init_error_msg_array();
void help();
//-------------------------------------------------------------------------
int main(int argc,char* argv[])
{
    // syntax check (options)
    int of;
    std::string arg;
    init_error_msg_array();

    for(int i = 0;i < argc;i++)
    {
        of = 0;
        arg = argv[i];

        if(arg[0] != '-') {
            continue;
        }
        else
        {
            for(int c = 0;c < PO_SIZE;c++)
            {
                if(arg == PO[c])
                {
                    of = 1;
                    c = PO_SIZE;
                }
            }
        }
        if(!of)
        {
            std::cerr << E_MSG[0] << std::endl << E_MSG[1] << arg << std::endl;
            return 1;
        }
    } // syntax check (options) end


    del = new t_del();
    std::bitset<8> bitset;
    int l = 0,c = 0,t = 0,s = 0,b = 0,e = 0,d = 0,i = 0;
    int pos = -1;
    char sign = '0';

    for(int q = 0;q < argc;q++)
    {
        arg = argv[q];
        if((arg.length() == 2) && (arg[0] == '-'))
        {
            switch(arg[1])
            {
                case 'l': { l = 1; break; }
                case 'c': { c = 1; break; }
                case 't': { t = 1; break; }
                case 's': { s = 1; break; }
                case 'b': { b = 1; break; }
                case 'e': { e = 1; break; }
                case 'd': { d = 1; break; }
                case 'i': { i = 1; break; }
                case 'h':
                {
                    help();
                    return 0;
                }
            }
        }


        if(arg == PO[0] || l) {
            bitset.set(0,true);
        }
        if(arg == PO[1] || c) {
            bitset.set(1,true);
        }
        if(arg == PO[2] || t) {
            bitset.set(2,true);
        }
        if(arg == PO[3] || s) {
            bitset.set(3,true);
        }
        if(arg == PO[4] || b) {
            bitset.set(4,true);
        }
        if(arg == PO[5] || e) {
            bitset.set(5,true);
        }
        if(arg == PO[6] || d)
        {
            if(pos < 0)
            {
                bitset.set(6,true);

                if(q + 1 < argc)
                {
                    arg = argv[q + 1];
                    for(int k = 0;k < arg.length();k++)
                    {
                        if(!isdigit(arg[k]))
                        {
                            std::cerr << E_MSG[0] << std::endl;
                            std::cerr << E_MSG[4] << std::endl;
                            return 1;
                        }
                    }
                    pos = atoi(arg.c_str());
                    pos--; // begin at position 1
                }
                else
                {
                    std::cerr << E_MSG[0] << std::endl;
                    std::cerr << E_MSG[3] << arg << std::endl;
                    return 1;
                }
            }
        }


        if((arg == PO[7] || i) && (pos >= 0 && sign == '0'))
        {
            bitset.set(7,true);

            if(q + 1 < argc)
            {
                arg = argv[q + 1];
                if(arg.length() != 1)
                {
                    std::cerr << E_MSG[0] << std::endl;
                    std::cerr << E_MSG[2] << arg << std::endl;
                    return 1;
                }

                sign = arg[0];
            }
            else
            {
                std::cerr << E_MSG[0] << std::endl;
                std::cerr << E_MSG[3] << arg << std::endl;
                return 1;
            }
        }
    }


    //std::cin.getline(del->line,BUFSIZE,'\0');
    strcpy(del->line,std::string("\n H\r\nO\tK \n").c_str());
    del->set_bufsize();


    if(!bitset.test(6) && !bitset.test(7))
    {
        if(bitset.test(4) || bitset.test(5)) {
            del->trim(bitset);
        }
        if(bitset.test(0) || bitset.test(1) || bitset.test(2) || bitset.test(3)) {
            del->del_control_chars(bitset);
        }
    }


    if(bitset.test(6) && !bitset.test(7))
    {
        del->del_sign_at(pos);
    }


    if(bitset.test(6) && bitset.test(7))
    {
        del->del_sign_at_if(pos,sign);
    }


    std::cout << del->data;
    free_memory();
    return 0;
}
//-------------------------------------------------------------------------
void free_memory()
{
    delete del;
}
//-------------------------------------------------------------------------
void init_error_msg_array()
{
    E_MSG[0] = "Syntax error.";
    E_MSG[1] = "There is no option: ";
    E_MSG[2] = "Check length of: ";
    E_MSG[3] = "Check syntax near: ";
    E_MSG[4] = "The " + PO[6] + " option requires a number as a value.";
}
//-------------------------------------------------------------------------
void help()
{
    int fw = 2,sw = 21;
    std::cout << std::left;
    std::cout << "Usage: del [Option]..." << std::endl;
    std::cout << std::setw(fw) << " " << std::setw(sw) << "-l, --lf";
    std::cout << "Removes all line feeds. Escape sequence \"\\n\"." << std::endl;

    std::cout << std::setw(fw) << " " << std::setw(sw) << "-c, --cr";
    std::cout << "Removes all carriage returns. Escape sequence \"\\r\"." << std::endl;

    std::cout << std::setw(fw) << " " << std::setw(sw) << "-t, --ht";
    std::cout << "Removes all horizontal tabs. Escape sequence \"\\t\"." << std::endl;

    std::cout << std::setw(fw) << " " << std::setw(sw) << "-s, --sp";
    std::cout << "Removes all spaces." << std::endl;


    std::cout << std::setw(fw) << " " << std::setw(sw) << "-b, --trim-left";
    std::cout << "Removes spaces and the following control characters" << std::endl;
    std::cout << std::setw(fw) << " " << std::setw(sw) << " ";
    std::cout << "that appear to the left of the string. \"\\n \\t \\r\"" << std::endl;

    std::cout << std::setw(fw) << " " << std::setw(sw) << "-e, --trim-right";
    std::cout << "Removes spaces and the following control characters" << std::endl;
    std::cout << std::setw(fw) << " " << std::setw(sw) << " ";
    std::cout << "that appear to the right of the string. \"\\n \\t \\r\"" << std::endl;

    std::cout << std::setw(fw) << " " << std::setw(sw) << "-d, --del-sign-at";
    std::cout << "Deletes a character at the specified position. The" << std::endl;
    std::cout << std::setw(fw) << " " << std::setw(sw) << " ";
    std::cout << "first character has the index 1." << std::endl;
    std::cout << std::setw(fw) << " " << std::setw(sw) << " ";
    std::cout << "This option can only be combined with -i, --if." << std::endl;

    std::cout << std::setw(fw) << " " << std::setw(sw) << "-i, --if";
    std::cout << "Checks whether there is a specific character in the" << std::endl;
    std::cout << std::setw(fw) << " " << std::setw(sw) << " ";
    std::cout << "place of -d, --del-sign-at." << std::endl;
    std::cout << std::setw(fw) << " " << std::setw(sw) << " ";
    std::cout << "Only one character can be specified here." << std::endl;

    std::cout << std::setw(fw) << " " << std::setw(sw) << "-h, --help";
    std::cout << "Display this help and exit." << std::endl;

    std::cout << std::endl << "Report bugs to <info@custom-app.org> (in English or German)." << std::endl;
    std::cout << "Del Utils home page: <https://>" << std::endl;
}