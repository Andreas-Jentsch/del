#ifndef TEST_T_OPTIONS_H
#define TEST_T_OPTIONS_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
typedef struct t_opt {
    bool val_required;
    std::string longname;
    std::string shortname;
    t_opt(bool v,std::string l,std::string s) {
        val_required = v;
        longname = l;
        shortname = s;
    }
} t_opt;
typedef std::vector<t_opt*> t_popts; // map<option,value required>
typedef std::map<std::string,std::string> t_map; // map<option,value>
// auf map mit find zugreifen!!!!
// del-sign-at und --lf --cr usw. kann zusammen verwendet werden, erst del-sign abarbeiten dann lf,cr usw.
// checken ob bei --del-sign-at der angegebene Wert nicht groesser ist als der ganze string oder ob ein minus Wert
class t_options {
    public:
        std::string progname;
        std::string progpath;
        t_map map;
        t_popts popts; // possible options

        void parse(int Argc,char** Argv);

        t_options();
        ~t_options();

    private:
        std::string _msg[2];
        //void _prog_pathname();
};


#endif
