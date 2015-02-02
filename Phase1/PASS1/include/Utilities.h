#ifndef UTILITIES_H
#define UTILITIES_H
#include <fstream>
#include <string>
#include<iostream>
#include<stdio.h>
#include<vector>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<math.h>
#include"Entry.h"
#define INF 1000000000
#define MOD  1000000007
#define MAX 100000
using namespace std;

class Utilities
{
    public:
        map <string,int>symbolTable;
        map<string,int>inst;
        bool firstEntering=true;
        vector<Entry>table;
        int CURRENTADRESS;

        Utilities();
    bool checkSpace(string a);
    void checkEndLine(string line);
    void fillingMap();
    void parse(string  line );
    void parse_sic(string  line );
    void threeWord ( vector<string> line,int typeByte,vector<string>comment);
    void twoWord ( vector<string> line,int typeByte,vector<string>comment);
    void oneWord ( vector<string> line,vector<string> comment,int byt);
    bool duplicateLable(string a);
    int validateOpcode(string a);
    bool check_operand(string opcode,string oper);
    string Tolower(string str);
    int Tointeger(string str);
    int todecimal(string a);
    bool checkWord(string a);
    int checkByte(string a);
    string Comment(vector<string>a);


















        virtual ~Utilities();
    protected:
    private:
};

#endif // UTILITIES_H
