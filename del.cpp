
// c++ del.cpp -o del

#include <vector>
#include <string.h>
#include <iostream>
#include <cstdlib>      // atoi()
#include <cctype>       // isalpha()

using namespace std;

const int BUFSIZE = 1024;
const int SIGNSIZE = 4;

void help();
void pr(const std::string& R,const int& DLLF = 0);

int main(int argc,char* argv[])
{
    string arg;
    bool dlf = 0,dcr = 0,dht = 0,dsp = 0,dsap = 0; // d = delete (lf = line feed)
    bool tl = 0,tr = 0;
    bool dllf = 0; // dllf = delete last line feed
    char sign[SIGNSIZE] = {0};
    int pos = -1; // position vom Zeichen welches geloescht werden soll
    char s = '0'; // --if sign
    
    for(int i = 0;i < argc;i++)
    {
        arg = argv[i];
        
        if((arg.length() == 2) && (arg[0] == '-'))
        {
            switch(arg[1])
            {
                case 'l': { dlf = 1; break; }
                case 'c': { dcr = 1; break; }
                case 't': { dht = 1; break; }
                case 's': { dsp = 1; break; }
                case 'b': { tl = 1; break; }
                case 'e': { tr = 1; break; }
                case 'd':{dsap = 1;break;}
                case 'i':{s = -7;break;}
                case 'r':{dllf = 1;break;}
            }
        }
        
        // --lf
        if((arg.length() == 4) && (arg[0] == '-') && (arg[1] == '-'))
        {
            if((arg[2] == 'l') && (arg[3] == 'f'))
            {
                dlf = 1;
            }
        }
        
        // --cr
        if((arg.length() == 4) && (arg[0] == '-') && (arg[1] == '-'))
        {
            if((arg[2] == 'c') && (arg[3] == 'r'))
            {
                dcr = 1;
            }
        }
        
        // --ht
        if((arg.length() == 4) && (arg[0] == '-') && (arg[1] == '-'))
        {
            if((arg[2] == 'h') && (arg[3] == 't'))
            {
                dht = 1;
            }
        }
        
        // --sp
        if((arg.length() == 4) && (arg[0] == '-') && (arg[1] == '-'))
        {
            if((arg[2] == 's') && (arg[3] == 'p')) { dsp = 1; }
        }
        
        // ----del-sign-at
        if((arg.length() == 13) && (arg[0] == '-') && (arg[1] == '-'))
        {
            if((i + 1) <= argc)
            {
                arg = argv[i + 1];
                for(int k = 0;k < arg.length();k++)
                {
                    if(!isdigit(arg[k])) { return 1; }
                }
                pos = atoi(argv[i + 1]);
                pos--; // begin at position 1
            }
        }
        
        // --if
        if((arg.length() == 4) && (arg[0] == '-') && (arg[1] == '-'))
        {
            if((arg[2] == 'i') && (arg[3] == 'f') && (i + 1 <= argc))
            {
                arg = argv[i + 1];
                if(arg.length() != 1) { return 1; }
                
                s = arg[0];
            }
        }
        
        // --remove
        if((arg.length() == 8) && (arg[0] == '-') && (arg[1] == '-'))
        {
            if((arg[2] == 'r') && (arg[3] == 'e') && (arg[4] == 'm')) { dllf = 1; }
        }
        
        if(dlf == 1)
        {
            sign[0] = 0x0A;
        }
        
        if(dcr == 1)
        {
            sign[1] = 0x0D;
        }
        
        if(dht == 1)
        {
            sign[2] = 0x09;
        }
        
        if(dsp == 1)
        {
            sign[3] = 0x20;
        }
    }
    
    vector<int> p; // p = position | gesuchtes Zeichen
    char l[BUFSIZE] = {0}; // l = line | komplette Zeile aus stdout >> max BUFSIZE
    string r = ""; // r = result
    bool f = 0; // f = found | position gefunden
    
    std::cin.getline(l,BUFSIZE,'\0');
    
    // determine how long the string is
    int byte = 0;
    for(int i = 0;i < BUFSIZE;i++)
    {
        if(l[i] == '\0')
        {
            byte = i;
            i = BUFSIZE; // for end
        }
    }
    
    // if the option --del-sign-at is set
    if((pos >= 0) && (s == '0'))
    {
        for(int i = 0;i < byte;i++)
        {
            if((i != pos) && (l[i] != '\0'))
            {
                r += l[i];
            }
        }
        pr(r,dllf);
        return 0;
    }
    
    // if the option --del-sign-at & --if is set
    if((pos >= 0) && (s != '0'))
    {
        for(int i = 0;i < byte;i++)
        {
            if((i != pos) && (l[i] != '\0'))
            {
                r += l[i];
            }
                else if((i == pos) && (l[i] != s))
                {
                    r += l[i];
                }
        }
        pr(r,dllf);
        return 0;
    }
    
    // if the option --lf, --cr, --ht or/and --sp is set
    if(/*(pos == -1) || */(dlf == 1) || (dcr == 1) || (dsp == 1))
    {
        // store all positions of the searched character in vector p
        for(int i = 0;i < byte;i++)
        {
            for(int c = 0;c < SIGNSIZE;c++)
            {
                if((l[i] == sign[c]) && (sign[c] != '\0')) { p.push_back(i); }
            }
        }
        
        // write all characters that are not in the vector p in r
        for(int i = 0;i < byte;i++)
        {
            for(unsigned int c = 0;c < p.size();c++)
            {
                if(i == p[c]) { f = 1; }
            }
            
            if(!f && l[i] != '\0') { r += l[i]; }
                else { f = 0; }
        }
        
        // --trim-left | write all characters back to l
        /*if(tl == 1)
        {
            memset(l,0,BUFSIZE);
            for(int i = 0;i < r.length();i++)
            {
                l[i] = r[i];
            }
            r = "";
        }*/
    }
    
    // if the option --trim-left is set
    if(tl == 1)
    {
        // write all characters back to l
        if((dlf == 1) || (dcr == 1) || (dsp == 1))
        {
            memset(l,0,BUFSIZE);
            for(int i = 0;i < r.length();i++)
            {
                l[i] = r[i];
            }
            r = "";
        }
        for(int i = 0;i < byte;i++)
        {
            // determine the first character that is not a control character
            if((isalpha(l[i])) || (isdigit(l[i])) || (ispunct(l[i])))
            {
                for(int c = i;c < byte;c++)
                {
                    if(l[c] != '\0') { r += l[c]; }
                }
                i = BUFSIZE; // for end
            }
        }
    }
    
    // if the option --trim-right is set
    if(tr == 1)
    {
        if(tl == 1)
        {
            memset(l,0,BUFSIZE);
            for(int i = 0;i < r.length();i++)
            {
                l[i] = r[i];
            }
            r = "";
        }
        
        for(int i = byte - 1;i >= 0;i--)
        {
            // determine the last character that is not a control character
            if((isalpha(l[i])) || (isdigit(l[i])) || (ispunct(l[i])))
            {
                for(int c = 0;c <= i;c++)
                {
                    if(l[c] != '\0') { r += l[c]; }
                }
                i = -1; // for end
            }
        }
    }
    
    // output
    pr(r,dllf);
    /*if(dllf == 1) { cout << r; }
        else { cout << r << endl; }*/
    
    //help();
    
    return 0;
}

void help()
{
    string s = "    "; // s = spaces
    string v = "";
    cout << s << "-l, --lf             Removes all line feeds. Escape sequence \"\\n\"." << endl;
    cout << s << "-c, --cr             Removes all carriage returns. Escape sequence \"\\r\"." << endl;
    cout << s << "-t, --ht             Removes all horizontal tabs. Escape sequence \"\\t\"." << endl;
    cout << s << "-s, --sp             Removes all spaces." << endl;
    cout << s << "-b, --trim-left      Removes spaces and the following control characters that" << endl;
    cout << s << "                     appear to the left of the string. \"\\n \\t \\r\"" << endl;
    cout << s << "-e, --trim-right     Trim Right" << endl;
    cout << s << "-d, --del-sign-at    Deletes a character at the specified position. The first character has the index 1." << endl;
    cout << s << "                     This option can only be combined with -r, --del-last-lf and with -i, --if." << endl;
    cout << s << "-i, --if             Checks whether there is a specific character in the place of -d, --del-sign-at." << endl;
    cout << s << "                     Only one character can be specified here." << endl;
    cout << s << "-r, --del-last-lf    The del program inserts a line break (lf) at the end of the string." << endl;
    cout << s << "                     If this is not needed, it can be prevented with the option -r, --del-last-lf." << endl << endl;
    cout << s << "-h, --help           Display this help and exit." << endl;
    cout << s << "-v, --version        Output version information and exit." << endl;
    cout << s << "                     The maximum buffer size is " << BUFSIZE << "." << endl;
}

void version()
{
    /*Copyright (C) 2022
License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.*/
}

void pr(const std::string& R,const int& DLLF)
{
    if(DLLF == 1) { cout << R; }
        else { cout << R << endl; }
}















































