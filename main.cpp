
#include "t_del.h"
#include "t_options.h"
//-------------------------------------------------------------------------
t_del* del = NULL;
t_options* opt = NULL;
const int ERROR_MSG_ARRAY_SIZE = 7;
std::string E_MSG[ERROR_MSG_ARRAY_SIZE];
//-------------------------------------------------------------------------
void free_memory();
void init_options();
void init_error_msg_array();
void help();
//-------------------------------------------------------------------------
int main(int argc,char* argv[])
{
    del = new t_del();
    opt = new t_options();

    init_options();
    t_map::iterator option;
    opt->parse(argc,argv);


    option = opt->map.find(opt->popts[0]->longname); // --lf
    if(option != opt->map.end()) {
        del->set_control_char(0x0A);
    }

    option = opt->map.find(opt->popts[1]->longname); // --cr
    if(option != opt->map.end()) {
        del->set_control_char(0x0D);
    }

    option = opt->map.find(opt->popts[2]->longname); // -ht
    if(option != opt->map.end()) {
        del->set_control_char(0x09);
    }

    option = opt->map.find(opt->popts[3]->longname); // --sp
    if(option != opt->map.end()) {
        del->set_control_char(0x20);
    }


    option = opt->map.find(opt->popts[8]->longname); // --help
    if(option != opt->map.end()) {
        help();
        free_memory();
        return 0;
    }


    std::cin.getline(del->line,BUFSIZE,'\0');
    //strcpy(del->line,std::string("\n\t    Hello World\n\r\n Test String\n     ").c_str());
    for(int i = 0;i < BUFSIZE && del->line[i] != '\0';i++)
    {
        del->data.push_back(del->line[i]);
    }
    del->set_bufsize();


    option = opt->map.find(opt->popts[6]->longname); // --del-sign-at
    if(option != opt->map.end())
    {
        int p = atoi(option->second.c_str()) - 1;
        option = opt->map.find(opt->popts[7]->longname); // --if
        if(option != opt->map.end()) {
            del->del_sign_at_if(p,option->second[0]);
        }
        else {
            del->del_sign_at(p);
        }
    }


    if(del->control_chars_count() > 0) // --lf --cr --ht --sp
    {
        del->del_control_chars();
    }


    option = opt->map.find(opt->popts[4]->longname); // --trim-left
    if(option != opt->map.end()) {
        bool left = 1;
        option = opt->map.find(opt->popts[5]->longname); // --trim-right
        if(option != opt->map.end()) {
            del->trim(left,true);
        }
        else {
            del->trim(left,false);
        }
    }


    for(t_data::iterator i = del->data.begin();i != del->data.end() && *i != '\0';i++)
    {
        std::cout << *i;
    }
    free_memory();
    return 0;
}
//-------------------------------------------------------------------------
void free_memory()
{
    delete del,opt;
}
//-------------------------------------------------------------------------
void init_options()
{
    opt->popts.push_back(new t_opt(false,"--lf","-l"));         //0
    opt->popts.push_back(new t_opt(false,"--cr","-c"));
    opt->popts.push_back(new t_opt(false,"--ht","-t"));
    opt->popts.push_back(new t_opt(false,"--sp","-s"));         //3
    opt->popts.push_back(new t_opt(false,"--trim-left","-b"));
    opt->popts.push_back(new t_opt(false,"--trim-right","-e"));
    opt->popts.push_back(new t_opt(true,"--del-sign-at","-d"));
    opt->popts.push_back(new t_opt(true,"--if","-i"));          //7
    opt->popts.push_back(new t_opt(false,"--help","-h"));
    opt->popts.push_back(new t_opt(false,"--version","-v"));
}
//-------------------------------------------------------------------------
void init_error_msg_array()
{
    E_MSG[0] = "Syntax error.";
    E_MSG[1] = "There is no option: ";
    E_MSG[2] = "Check length of: ";
    E_MSG[3] = "Check syntax near: ";
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