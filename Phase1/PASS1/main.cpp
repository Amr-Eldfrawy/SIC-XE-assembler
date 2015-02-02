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
#include"Utilities.h"
#include<math.h>
#define INF 1000000000
#define MOD  1000000007
#define MAX 100000

using namespace std;
Utilities u;

int main()
{
    u.fillingMap();
    string inputFile;
    cout<<"Please enter the input file"<<endl;
    cin>>inputFile;
    freopen("output.txt","w",stdout);

    ifstream code;
    code.open(inputFile.c_str());

    string prev="" ;
    string next="";
    while(getline(code,next))
    {
        if(u.checkSpace(next))
        {
            if(prev!="")
                u.parse(prev);
            prev=next;
        }
    }
    u.checkEndLine(prev);
    code.close();
    printf("%5s%20s%20s%20s%30s             %s\n\n","LineNo","Adress","Label","Op-code","Operand","Comment");
    for(int i=0; i<u.table.size(); i++)
    {
        char buffer [33];
        if(u.table[i].loc!=-1)
            itoa (u.table[i].loc,buffer,16);
        printf("%5d%20s%20s%20s%30s             %s\n",i,buffer,u.table[i].label.c_str(),u.table[i].op_code.c_str(),u.table[i].operand.c_str(),u.table[i].comment.c_str());
        if(u.table[i].error!="")
            printf("                                            %s\n",u.table[i].error.c_str());

    }

    cout<<"\n\n\n\n\n"<<endl;
    cout<<"                     *********************Symbol Table********************"<<endl<<endl;
    printf("%20s             |         %20s\n","Symbol","Address");
    printf("     ****************************|*******************************\n");
    typedef map<string, int>::const_iterator MapIterator;
    for (MapIterator iter = u.symbolTable.begin(); iter !=u.symbolTable.end(); iter++)
    {
        char buffer [33];

        itoa (iter->second,buffer,16);

        printf("%20s             |         %20s\n",iter->first.c_str(),buffer);


    }

    return 0;


}
