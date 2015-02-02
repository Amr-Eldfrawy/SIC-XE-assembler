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
#include <sstream>
#define INF 1000000000
#define MOD  1000000007
#define MAX 100000
using namespace std;

map <string,int>symbolTable;
map<string,int>inst;
map<string,bool>absolute;
bool firstEntering;
map<string,string>Appendix;
map<string, string>mnemonicNumber;
int base=0;
bool error1;
bool error2;
/*

 storage.insert("bla bla ");
 if( storage.find(your string ) == storgae.end() ) >> not found
 else >> found

*/

class Entry
{
public:
    int loc ;
    string label , op_code , operand ,comment,error,ObjectCode;
    Entry()
    {
        loc=0;
        label=op_code=operand=comment=error=ObjectCode="";
    }
    Entry(int x , string a , string b , string c , string d,string e,string o)
    {
        loc = x;
        label=a, op_code=b, operand=c ,comment=d,error=e,ObjectCode=o;
    }

};


vector<Entry>table;
int CURRENTADRESS;
// pair  >> (first  == string ) ,, (second == int )

//splitting the line into words and then check the lenght of the vector and call the function
//unless the words are comment it insert it in vector with the same cuurnt adress.
string Comment(vector<string>a){
    string temp="";
        for(int i=0;i<a.size();i++)
            temp+=a[i]+" ";
            return temp;
}

int checkByte(string a){

    if(a.size()<4)
        return -1;

    if(a[0]=='x'&&a[1]=='\''&&a[a.size()-1]=='\''){
            if((a.size()-3)%2==1)
            return -1;
        for(int i=2;i<a.size()-1;i++){
            if((a[i]>='0'&&a[i]<='9')||(a[i]>='a'&&a[i]<='f')){

            }
            else
                return -1;
        }
        return ((a.size()-3)/2);
    }
    else if((a[0]=='c'||a[0]=='C')&&a[1]=='\''&&a[a.size()-1]=='\''){

        return (a.size()-3);
    }
    else
        return -1;
}

bool checkWord(string a){
    if(a.size()==1){
        if((a[0]<'0'||a[0]>'9'))
            return false;
        return true;
    }
    if(a.size()==2&&a[1]=='-')
        return false;


    if(a[0]!='@'&&a[0]!='#'&&a[0]!='-'&&(a[0]<'0'||a[0]>'9'))
        return false;

    for(int i=1;i<a.size();i++){
        if(a[i]<'0'||a[i]>'9'){
            if(i==1){
                    if(a[1]=='-'&&(a[0]=='#'||a[0]=='@')){

                    }
                    else
                return false;
            }
            else
                return false;
        }
    }

    return true;
}


int todecimal(string a){
    int ans=0;
    int t=a.size()-1;
    for(int i=0;i<a.size();i++){
        if(a[i]=='A'||a[i]=='a'){
                ans+=10*pow(16,t);

        }
       else if(a[i]=='B'||a[i]=='b'){
            ans+=11*pow(16,t);
       }
         else if(a[i]=='C'||a[i]=='c'){
        ans+=12*pow(16,t);
        }
         else if(a[i]=='D'||a[i]=='d'){
        ans+=13*pow(16,t);
        }
         else if(a[i]=='E'||a[i]=='e'){
        ans+=10*pow(14,t);
        }
         else if(a[i]=='F'||a[i]=='f'){
       ans+=10*pow(15,t);
        }
         else if(a[i]>='0'&&a[i]<='9'){
            ans+=(a[i]-'0')*pow(16,t);
        }
        else
            return -1;
            t--;
    }
    return ans;
}

int Tointeger(string str)
{
    int res = 0 ;

    for(int i = 0 ; i < str.size() ; i++){
        if(str[i]<'0'||str[i]>'9')
        return -1;
        res =  res*10 + (int)(str[i]-'0');
    }

    return res;
}
string Tolower(string str)
{
    for(int i=0 ;i <str.size() ; i++)
        str[i]=tolower(str[i]);

    return str;
}
/*bool check_operand(string opcode,string oper){

       if(opcode.compare("tixr")==0||opcode.compare("clear")==0){
                if(oper.compare("a")==0||oper.compare("s")==0||oper.compare("t")==0||oper.compare("x")==0
                   ||oper.compare("b")==0||oper.compare("l")==0){

                 return true;
                }else{

                  return false;
                }

            }else{

                if(oper.size()==3){
                 if((oper[0]=='a'||oper[0]=='s'||oper[0]=='t'||oper[0]=='x'||oper[0]=='b'||oper[0]=='l')&&
                   oper[1]==','&&(oper[2]=='a'||oper[2]=='s'||oper[2]=='t'||oper[2]=='x'||oper[0]=='b'
                                  ||oper[0]=='l')){

                  return true;
               }else{

                  return false;
               }
              }else{

                 return false;
              }
        }


}*/
  int validateOpcode(string a){
    // int elly byrg3 d hy2olk ana gbt op-code mn anhy map tmam ?
        if(a=="org"||a=="equ")
        return 6;
     if( inst.find(a )!= inst.end())
       return inst[a];
    return -1;

  }
bool check_operand(string opcode,string oper){
    int map_num= validateOpcode(opcode);

    if(map_num==2){
       if(opcode.compare("tixr")==0||opcode.compare("clear")==0){
            if(oper.compare("a")==0||oper.compare("s")==0||oper.compare("t")==0||oper.compare("x")==0
                   ||oper.compare("b")==0||oper.compare("l")==0){

                 return true;
                }else{

                  return false;
                }

        }else{

                if(oper.size()==3){
                 if((oper[0]=='a'||oper[0]=='s'||oper[0]=='t'||oper[0]=='x'||oper[0]=='b'||oper[0]=='l')&&
                   oper[1]==','&&(oper[2]=='a'||oper[2]=='s'||oper[2]=='t'||oper[2]=='x'||oper[0]=='b'
                                  ||oper[0]=='l')){

                  return true;
               }else{

                  return false;
               }
              }else{

                 return false;
              }
        }
      }else {
        if(oper[0]=='#'||oper[0]=='@'){
            if(oper.size()>=2&&oper[oper.size()-1]=='x'&&oper[oper.size()-2]==','){
                return false;
            }else{
              return true;
            }
        }else{
          return true;
        }
      }


}

  bool duplicateLable(string a){
     if( symbolTable.find(a ) == symbolTable.end())
       return false;
    return true;
  }

void oneWord ( vector<string> line,vector<string> comment,int byt)
{

        string temp=Comment(comment);
    table.push_back(Entry(CURRENTADRESS,"",line[0],"",temp,"",""));
         CURRENTADRESS+=byt;

}
int checkOrg(string a){
    if(a.size()==1&&a[0]=='*')
        return CURRENTADRESS;
        int k=0;
   if(a[0]=='#'||a[0]=='@')
            k++;
            string one="";
            string two="";
            int sign=-1;
            bool flag1=true;
            bool flag2=true;
   for(int i=k;i<a.size();i++){
        if(a[i]=='-'||a[i]=='+'){
            if(a[i]=='+')
                sign=1;
            else
                sign=2;
        }
        else if(a[i]<'0'||a[i]>'9'){
           if(sign==-1){
                one+=a[i];
            flag1=false;
           }
           else{
            flag2=false;
            two+=a[i];
           }
        }

        else{
          if(sign==-1)
             one+=a[i];
         else
            two+=a[i];

        }
   }
   if(one=="")
    return -1;
    if(flag1)
        return -1;

        if(symbolTable.find(one)==symbolTable.end())
            return -1;
        int adrs1=symbolTable[one];

    if(!flag2){
        if(symbolTable.find(two)==symbolTable.end())
        return -1;
        int adrs2=symbolTable[two];
        if(sign==1)
            return adrs1+adrs2;

        else{
             if(absolute.find(one)!=absolute.end())
             return -1;
            if(absolute.find(two)==absolute.end())
                return -1;
            return adrs1-adrs2;

        }

}
else{
    if(absolute.find(one)!=absolute.end())
             return -1;
    if(sign==-1)
        return adrs1;
    else{
        if(sign==1)
            return adrs1+Tointeger(two);
        else
            return adrs1-Tointeger(two);
    }
}


}

void twoWord ( vector<string> line,int typeByte,vector<string>comment,int k)
{

         string temp=Comment(comment);
          if(k==1)
         table.push_back(Entry(CURRENTADRESS,"",line[0],line[1],temp,"",""));
         else
            table.push_back(Entry(CURRENTADRESS,line[0],line[1],"",temp,"",""));
           // cout<<temp<<endl;
           if(typeByte==6){
                int org=checkOrg(line[1]);
                if(org==-1){
                table[table.size()-1].error="****Error: Invalid Operand";
                error1=false;
                }
                    else
                    CURRENTADRESS=org;
           }
           else
        CURRENTADRESS+=typeByte;

    }


int checkEqu(string a,string label){
   if(a.size()==1&&a[0]=='*')
        return CURRENTADRESS;
        int k=0;
   if(a[0]=='#'||a[0]=='@')
            k++;
            string one="";
            string two="";
            int sign=-1;
            bool flag1=true;
            bool flag2=true;
   for(int i=k;i<a.size();i++){
        if(a[i]=='-'||a[i]=='+'){
            if(a[i]=='+')
                sign=1;
            else
                sign=2;
        }
        else if(a[i]<'0'||a[i]>'9'){
           if(sign==-1){
                one+=a[i];
            flag1=false;
           }
           else{
            flag2=false;
            two+=a[i];
           }
        }

        else{
          if(sign==-1)
             one+=a[i];
         else
            two+=a[i];

        }
   }
   if(one=="")
    return -1;
    if(sign!=-1&&two=="")
        return -1;

    if(flag1&&!flag2)
        return -1;
    //two integers
   if(flag1&&flag2){
        if(sign==-1){
            absolute[label]=true;
            return Tointeger(one);
        }
        else
            return -1;
   }
   // two words
   else{
    if(sign==-1){
            if(symbolTable.find(one)!=symbolTable.end()){
                 if(absolute.find(one)!=absolute.end())
                   absolute[label]=true;

                return symbolTable[one];
            }
            else
                return -1;
    }
    else{

        int addrs;
        if(symbolTable.find(one)!=symbolTable.end())
             addrs=symbolTable[one];
            else
                return -1;
        if(flag2==true){
            if(absolute.find(one)!=absolute.end())
                absolute[label]=true;
            if(sign==1){

                return addrs+Tointeger(two);
            }
            else{
                return addrs-Tointeger(two);
            }
        }
        else{
            if(absolute.find(one)!=absolute.end()&&absolute.find(two)!=absolute.end())
                absolute[label]=true;
            int addrs2;
            if(symbolTable.find(two)!=symbolTable.end())
            addrs2=symbolTable[two];
            else
                return -1;
           if(sign==1){
               if(absolute.find(one)==absolute.end()&&absolute.find(two)==absolute.end())
               return -1;
                return addrs+addrs2;
            }
            else{
                return addrs-addrs2;
            }
        }
    }

   }


}



void threeWord ( vector<string> line,int typeByte,vector<string>comment)
{
      string temp=Comment(comment);
    symbolTable[line[0]]=CURRENTADRESS;
     table.push_back(Entry(CURRENTADRESS,line[0],line[1],line[2],temp,"",""));


    if(typeByte<5)
        CURRENTADRESS+=typeByte;
    else {
            if(line[1]=="equ"){
                   int adress=checkEqu(line[2],line[0]);
            if(adress==-1){
                     error1=false;
                table[table.size()-1].error="****Error: Invalid Operand";
            }
            else{
                symbolTable[line[0]]=adress;
            }

            }

         else if(line[1]=="byte"){
            int check=checkByte(line[2]);
            if(check!=-1)
             CURRENTADRESS+=check;
            else{
                table[table.size()-1].error="****Error: Invalid Operand";
                 error1=false;
            }
        }
        else if(line[1]=="word"){
                if(checkWord(line[2]))
             CURRENTADRESS+=3;
        else{
            table[table.size()-1].error="****Error: Invalid Operand";
             error1=false;
        }
        }
        else if(line[1]=="resb"){
           int numOfByt=Tointeger(line[2]);
           if(numOfByt==-1){
                table[table.size()-1].error="****Error: Invalid Operand";
                 error1=false;

            //   erorrEntires.push_back(make_pair("****Error: Invalid Operand",CURRENTADRESS));
           }

           else
           CURRENTADRESS+=numOfByt;
        }
        else{
          int numOfByt=Tointeger(line[2]);
          if(numOfByt==-1){
            table[table.size()-1].error="****Error: Invalid Operand";
             error1=false;
          }

           //    erorrEntires.push_back(make_pair("****Error: Invalid Operand",CURRENTADRESS));

           else
           CURRENTADRESS+=numOfByt*3;
        }

    }


}

bool isNumber(string str)
{
    for(int i = 0 ; i < str.size() ; i++)if(str[i]<'0' || str[i]>'9')return 0;
    return 1;
}
string Add(string a , string b)
{
    int val1 = atoi(a.c_str());
    int val2 = atoi(b.c_str());
    int Number = val1+val2;
    ostringstream convert;
    convert << Number;
    return convert.str();
}
string Multi(string a , string b)
{

    int val1 = atoi(a.c_str());
    int val2 = atoi(b.c_str());
    int Number = val1*val2;
    ostringstream convert;
    convert << Number;
    return convert.str();

}
string Divide(string a , string b)
{
    int val1 = atoi(a.c_str());
    int val2 = atoi(b.c_str());
    int Number = val1/val2;
    ostringstream convert;
    convert << Number;
    return convert.str();


}
string Sub(string a , string b)
{
    int val1 = atoi(a.c_str());
    int val2 = atoi(b.c_str());
    int Number = val1-val2;
    ostringstream convert;
    convert << Number;
    return convert.str();

}
string evaluateExp(vector<string>postfixexp)
{
    // "234" ,"123","222","-","+"   >> number

    stack<string> S ;


    for (int i = 0; i <postfixexp.size(); i++)
    {

        if (isNumber(postfixexp[i]))
            S.push(postfixexp[i]);
        else
        {
            if (postfixexp[i] == "*")
            {
                string first = S.top();
                S.pop();
                string second = S.top();
                S.pop();
                S.push(Multi(first,second));
            }
            else if (postfixexp[i] == "+")
            {
                string first = S.top();
                S.pop();
                string second = S.top();
                S.pop();
                S.push(Add(first,second));

            }
            else if (postfixexp[i] == "/")
            {
                string first = S.top();
                S.pop();
                string second = S.top();
                S.pop();
                S.push(Divide(first,second));

            }
            else if (postfixexp[i] == "-")
            {
                string first = S.top();
                S.pop();
                string second = S.top();
                S.pop();
                S.push(Sub(first,second));

            }

        }
    }
    return S.top();
}
bool higherPrecedence(string s, string peek)
{

    if (peek == "(")
        return false;
    string order[]= {"+","-","*","/"};
    int index1 = 0, index2=0;
    for(int i = 0 ; i < 4 ; i++)
    {
        if(s==order[i])
            index1=i;
        if(peek==order[i])
            index2=i;

    }
    return index1<=index2;

}
vector<string> toPostfix(vector<string>str)
{
    // "(" , "100" ,  "+" ,  "123" , ")" ,  "-"  , "1245"  >>>> "100" ,  "123" ,  "+" , "1245" , " - "

    vector<string> ans ;
    stack<string> S ;
    for (int i = 0; i < str.size(); i++)
    {
        string top = str[i];
        // simple char
        if (isNumber(top))
        {
            ans.push_back(top);
            continue;

        }
        // ( * , + , / , * , ( , ) )
        else
        {
            if(top!="*" || top!="+"|| top!="/" || top!="*" || top!="(" ||top!=")")return vector<string>();
            if (top == ")")
            {

                while (!S.empty() && S.top()!= "(")
                    ans .push_back(S.top()),S.pop();
                S.pop();

            }
            else if (S.empty())
            {
                S.push(top);
                continue;
            }
            else
            {
                if (top == "(")
                {
                    S.push(top);
                    continue;
                }

                while (!S.empty() && higherPrecedence(top, S.top() )  )
                    ans .push_back(S.top()),S.pop();
                S.push(top);
            }
        }

    }
    while (!S.empty())
        ans .push_back(S.top()),S.pop();

    return ans;

}
vector<string> ParseLine(string line )

{
  vector<string>res;

  string temp="";
  bool check_symbol=false;
  for(int i=0;i<line.size();i++){

   if(line[i]=='+'||line[i]=='-'||line[i]=='('||line[i]==')'||line[i]=='*'
      ||line[i]=='/'){
     if(temp!=""){

       if(check_symbol){
         if(symbolTable.find(temp)!=symbolTable.end()){

           ostringstream convert;
           convert <<symbolTable[temp];
           string temp2 = convert.str();
          temp=temp2;
         }else{
           res.clear();
           temp="";
           break;
         }
       }
     res.push_back(temp);
     check_symbol=false;
     temp="";
     }
     temp="";

     temp=line[i];
     res.push_back(temp);
   }else{

    if(line[i]<'0'||line[i]>'9'){
       check_symbol=true;
     }
     temp+=line[i];
   }
  }
  if(temp!=""){

        if(check_symbol){

         if(symbolTable.find(temp)!=symbolTable.end()){

            ostringstream convert;
           convert <<symbolTable[temp];
           string temp2 = convert.str();
          temp=temp2;
         }else{
          res.clear();
           temp="";

         }
       }

     res.push_back(temp);

  }

  return res;
}

void parse(string  line )
{


  vector<string>res;
  vector<string>comments;
  string temp="";
  bool com=false;

  for(int i = 0 ; i < line.size();i++)
  {
        if(line[i]!=' ')
           temp+=line[i];

        else if(temp!="")
        {


                 if(temp[0]=='.')
                        com=true;

            if(!com){
                    if(res.size()==2&&res[1]=="byte"&&(temp[0]=='C'||temp[0]=='c')){
                    res.push_back(temp);
                    }
                else{

                temp=Tolower(temp);
                res.push_back(temp);
                }
            }

            else
            comments.push_back(temp);
        temp="";



        }
  }

   if(temp!=""){


            if(temp[0]=='.')
            com=true;


          if(!com){
                if(res.size()==2&&res[1]=="byte"&&(temp[0]=='C'||temp[0]=='c')){
                res.push_back(temp);
                }
                else{

                temp=Tolower(temp);
                res.push_back(temp);
                }
            }

            else
            comments.push_back(temp);

     }





  if(res.size()>0&&firstEntering){
    if(res.size()==2)
        CURRENTADRESS=todecimal(res[1]);
    else if(res.size()==3)
        CURRENTADRESS=todecimal(res[2]);

    firstEntering=false;
    if(res.size()==2&&res[0].compare("start")==0&&CURRENTADRESS!=-1){
         temp=Comment(comments);

           table.push_back(Entry(CURRENTADRESS,"",res[0],res[1],temp,"",""));
    }
    else if(res.size()==3&&res[1].compare("start")==0&&CURRENTADRESS!=-1){
        temp=Comment(comments);

           table.push_back(Entry(CURRENTADRESS,res[0],res[1],res[2],temp,"",""));
    }
    else{
        temp=Comment(comments);
            string lin=Comment(res);
      error1=false;
     table.push_back(Entry(CURRENTADRESS,lin,"","",temp,"****Error: invalid start of the program",""));
    }



  }
  else if(res.size()==3||(res.size()>3&&res[2]=="C'"&&res[3]=="'")){
        if(res.size()>3&&res[2]=="C'"&&res[3]=="'"){
           res[2]="C' '";

        }

    int byt=validateOpcode(res[1]);
   if(!duplicateLable(res[0])){


        if(byt!=-1){
            if(check_operand(res[1],res[2]))
            threeWord(res,byt,comments);
            else{
                temp=Comment(comments);
                 error1=false;
                table.push_back(Entry(CURRENTADRESS,res[0],res[1],res[2],temp,"****Error: Invalid Operand",""));
                CURRENTADRESS+=byt;

            }


        }

      else
     {
         temp=Comment(comments);
          error1=false;
                table.push_back(Entry(CURRENTADRESS,res[0],res[1],res[2],temp,"****Error: Invalid OpCode",""));
                CURRENTADRESS+=byt;

     }
     }
   else{
        temp=Comment(comments);
         error1=false;
                table.push_back(Entry(CURRENTADRESS,res[0],res[1],res[2],temp,"****Error: Duplicate Symbol",""));
                CURRENTADRESS+=byt;

   }
   }


  else if(res.size()==2){
    int byt=validateOpcode(res[0]);
        if(byt!=-1){
            if(check_operand(res[0],res[1])){
            twoWord(res,byt,comments,1);
                }
              else{
                temp=Comment(comments);
                 error1=false;
                table.push_back(Entry(CURRENTADRESS,"",res[0],res[1],temp,"****Error: Invalid Operand",""));
                CURRENTADRESS+=byt;

            }
            }
            else{

                 int byt2=validateOpcode(res[1]);

                if(byt2==1||res[1]=="rsub"){
                    twoWord(res,byt,comments,2);
                }
                else{
                temp=Comment(comments);
                if(byt2==-1){
                 error1=false;
               table.push_back(Entry(CURRENTADRESS,line,"","","","****Error: Invalid OpCode",""));
                }
                else{
                         error1=false;
                table.push_back(Entry(CURRENTADRESS,line,"","","","****Error: Invalid Operand",""));
                }
                CURRENTADRESS+=byt;
                }
            }




  }
else if(res.size()==1){

    string str = res[0];
    int byt=validateOpcode(str);
    if( byt!=-1)
                oneWord(res,comments,byt);

        else
        {
                temp=Comment(comments);
                 error1=false;
                table.push_back(Entry(CURRENTADRESS,"",res[0],"",temp,"****Error: Invalid OpCode",""));
                  CURRENTADRESS++;
        }

  }
else if(res.size()>3){

         error1=false;

     table.push_back( Entry( CURRENTADRESS , "",line ,"" ,"","****Error: Invalid Entry","" ) ) ;

}
  else if(comments.size()>0){
    temp=Comment(comments);
        if(!firstEntering)
        table.push_back( Entry( CURRENTADRESS ,"" ,"" ,"" ,temp,"","" ) ) ;
        else
             table.push_back( Entry( -1 ,"" ,"" ,"" ,temp,"" ,"") ) ;

  }



}
void fillingMap(){

     ifstream form;
   form.open("format.txt");
    string Line ;
    while(getline(form,Line)){

        string temp="";
        for(int i=0;i<Line.size()-1;i++)
            temp+=Line[i];

        inst[temp]=Line[Line.size()-1]-'0';
    }

    form.close();

    //..........................................
ifstream appn;
   appn.open("appendix.txt");

    while(getline(appn,Line)){
        string op="";
        string bin="";
        bool flag=true;
        for(int i=0;i<Line.size();i++){
            if(Line[i]==' ')
                flag=false;
            else if(flag)
                op+=Line[i];
            else
                bin+=Line[i];
        }
        Appendix[op]=bin;

    }

    appn.close();

}


void checkEndLine(string line){
     vector<string>res;
  vector<string>comments;
  string temp="";
  bool com=false;

  for(int i = 0 ; i < line.size();i++)
  {
        if(line[i]!=' ')
           temp+=line[i];

        else if(temp!="")
        {


                 if(temp[0]=='.')
                        com=true;

            if(!com){
                temp=Tolower(temp);
                        res.push_back(temp);
            }

            else
            comments.push_back(temp);
        temp="";



        }
  }

   if(temp!=""){


            if(temp[0]=='.')
            com=true;


          if(!com){
                temp=Tolower(temp);
                        res.push_back(temp);
            }

            else
            comments.push_back(temp);

     }

         temp=Comment(comments);
      if(res.size()==1&&res[0]=="end"){

            table.push_back(Entry(CURRENTADRESS,"",res[0],"",temp,"",""));

     }
     else{
            string lin=Comment(res);
        error1=false;
        table.push_back(Entry(CURRENTADRESS,lin,"","",temp,"****Error: invalid end of the program",""));
     }

}

bool checkSpace(string a){
for(int i=0;i<a.size();i++)
    if(a[i]!=' ')
    return true;
return false;
}

string binary_to_hexa(string a){
    int dec=0;
    for(int i=0;i<a.size();i++){
        dec+=(a[i]-'0')*pow(2,a.size()-i-1);
    }
     char buffer [33];
    itoa (dec,buffer,16);
    return buffer;
}


string formate1(string line){
          return binary_to_hexa( Appendix[line] );
}


vector <string>splitLine(string line)
{

  vector<string>res;
  string temp="";
  for(  int i = 0; i < line.size() ; i++)
    {
       if(line[i]==',')
       {
         res.push_back(temp);
         temp="";
       }
      else
        temp+=line[i];
    }
   res.push_back(temp);

  return res;

}



string formate2(string opCode , string operand ){

  // op_code r1,r2
  string res="";
 vector<string>rigisters = splitLine(operand);
  res += binary_to_hexa( Appendix[opCode] );
  res+=mnemonicNumber[rigisters[0]];

  if(rigisters.size()>1)
    res+=mnemonicNumber[rigisters[1]];
  else
    res+="0";


  return res;

}






//form  just tell you format type
string formate3_4(int index,string instr,string operand,int current_address){
    string res="";
  string nixbpe="000000";
  string temp="";
  if(instr[0]=='+'){

    for(int i=1;i<instr.size();i++)
      temp+=instr[i];
    instr=temp;
    nixbpe[5]='1';
  }
  if(operand[0]=='#'){
   nixbpe[1]='1';
  }else if(operand[0]=='@'){
   nixbpe[0]='1';
  }else{
   nixbpe[0]='1';
   nixbpe[1]='1';
    //check ni==00
  }
  string opValue= Appendix[instr];

  opValue[opValue.size()-1]=nixbpe[1];
  opValue[opValue.size()-2]=nixbpe[0];
  //al method dy 8ltt
  temp=binary_to_hexa(opValue);
  if(temp.size()==1){
     string temp2="";
      temp2='0';
      temp2+=temp[0];
      temp=temp2;
  }
  for(int i=0;i<temp.size();i++)
    res+=temp[i];


  if(operand[operand.size()-1]=='x'&&operand[operand.size()-2]==','){
    nixbpe[2]='1';
    temp="";
    for(int i=0;i<operand.size()-2;i++){
        temp+=operand[i];
    }
    operand=temp;

  }

  string dis="";
  if(nixbpe[5]=='0'){

   int TA= Tointeger(evaluateExp(toPostfix (ParseLine(operand))) );
   if(TA!=-1){

   int dis=TA-(current_address+3);

    if(TA!=-2){
    if(dis>=-2048&&dis<=2047){
      nixbpe[4]='1';
    }else{
      //dis will change here=TA-B
      //lsa man3rfsh lw mandash 3la LDB 7n3ml 2eh
      dis=TA-base;
      nixbpe[3]='1';
    }
    }else{
        temp="";
        for(int i=1;i<operand.size();i++)
            temp+=operand[i];
     dis=Tointeger(temp);
    }

   int xbpe=(nixbpe[2]-'0')*8+(nixbpe[3]-'0')*4+(nixbpe[4]-'0')*2;
        char buffer [33];
       temp= itoa (xbpe,buffer,16);
    for(int i=0;i<temp.size();i++){
      res+=temp[i];
    }


   temp=itoa (dis,buffer,16);
    if(temp.size()>3){
         string temp2="";
         temp2=temp[temp.size()-3];
         temp2+=temp[temp.size()-2];
         temp2+=temp[temp.size()-1];
         temp=temp2;
    }else{
         string temp2="";
        for(int i=0;i<(3-temp.size());i++){
            temp2+='0';
        }
        for(int i=0;i<temp.size();i++){
            temp2+=temp[i];
        }
        temp=temp2;
    }

    for(int i=0;i<temp.size();i++){
      res+=temp[i];
    }
    return res;
   }else{
    //error
    if(operand==""){
        temp="0000";
      for(int i=0;i<temp.size();i++){
      res+=temp[i];
      }
       return res;
    }else{
    table[index].error="invalid expression or symbol";
     error2=false;
    }

   }
  }else{
    int xbpe=1+(nixbpe[2]-'0')*8;
        char buffer [33];
       temp= itoa (xbpe,buffer,16);
    for(int i=0;i<temp.size();i++)
      res+=temp[i];
    //lsa mat3mltsh
    int TA= Tointeger(evaluateExp(toPostfix (ParseLine(operand))) );
    if(TA!=-1){
      if(TA!=-2){
    temp= itoa (TA,buffer,16);
    }else{
     temp="";
        for(int i=1;i<operand.size();i++)
            temp+=operand[i];
      TA  = atoi(temp.c_str());

    }
    temp= itoa (TA,buffer,16);
     if(temp.size()>5){
        string temp2="";
         temp2=temp[temp.size()-5];
         temp2+=temp[temp.size()-4];
         temp2+=temp[temp.size()-3];
         temp2+=temp[temp.size()-2];
         temp2+=temp[temp.size()-1];
         temp=temp2;
     }else{
        string temp2="";
        for(int i=0;i<(5-temp.size());i++){
            temp2+='0';
        }
        for(int i=0;i<temp.size();i++){
            temp2+=temp[i];
        }
        temp=temp2;
     }

     for(int i=0;i<temp.size();i++)
      res+=temp[i];

    return res;
    }else{
     //error
      if(operand==""){
        temp="000000";
      for(int i=0;i<temp.size();i++){
      res+=temp[i];
      }
       return res;
    }else{
       table[index].error="invalid expression or symbol";
        error2=false;
    }
    }


  }

return res;


}
void objectCode(){

  for(int i=0;i<table.size();i++){
    if(table[i].op_code=="start"||table[i].op_code=="end"||table[i].op_code=="")
              continue;
      if(table[i].op_code=="byte"){
            if(table[i].operand[0]=='x'){
                for(int j=2;j<table[i].operand.size()-1;j++)
                    table[i].ObjectCode+=table[i].operand[j];
            }
            else{

                for(int j=2;j<table[i].operand.size()-1;j++){
                    int ascii=table[i].operand[j];
                       char buffer [33];
                    itoa (ascii,buffer,16);
                    table[i].ObjectCode+=buffer;
                }
            }

      }
      else if(table[i].op_code=="word"){
        int dec=0;
        for(int j=2;j<table[i].operand.size()-1;j++){
            dec=dec*10+table[i].operand[j];
        }
            char buffer [33];
        itoa (dec,buffer,16);
        table[i].ObjectCode=buffer;
      }
      else{
        int byt=inst[table[i].op_code];

    string res="";
    if(byt==1)
      res=formate1(table[i].op_code);
    else if(byt==2)
      res=formate2(table[i].op_code,table[i].operand);
      else if(byt==3||byt==4)
      res=formate3_4(i,table[i].op_code,table[i].operand,table[i].loc);
      table[i].ObjectCode=res;
      if(table[i].op_code=="ldb"){
        base=Tointeger(evaluateExp(toPostfix (ParseLine(table[i].operand))) );
        if(base==-2){
            string temp="";
        for(int i=1;i<table[i].operand.size();i++)
            temp+=table[i].operand[i];
          base=Tointeger(temp);
        }else if(base==-1){
            error2=false;
     //   table[i].error="invalid expression or symbol";
        //error
        }
      }

  }
  }


}
void initRigisters()
{

  mnemonicNumber["a"]="0";
  mnemonicNumber["x"]="1";
  mnemonicNumber["l"]="2";
  mnemonicNumber["b"]="3";
  mnemonicNumber["s"]="4";
  mnemonicNumber["t"]="5";
  mnemonicNumber["f"]="6";
  mnemonicNumber["pc"]="8";
  mnemonicNumber["sw"]="9";
}
vector<pair<string, int > >objectFile;
vector<int >objectFileFormate4;
string programName;
int startAdress;



  void buildObjectFile()
  {

    programName="";
    for(int i =  0 ; i < table.size() ; i++)
    {

        if(table[i].op_code=="start"){
          if(table[i].label!=""){
            programName=table[i].label;
          }
                startAdress=table[i].loc;

        }
      if(table[i].ObjectCode !="")
      {


        if(table[i].op_code[0]=='+'&&table[i].operand[0]!='#')
        objectFileFormate4.push_back(table[i].loc);
        objectFile.push_back(make_pair(table[i].ObjectCode,table[i].loc));




      }

    }
  }
string modifyLocation(int loc , int len)
{

        string lenght="";
                char buffer [33];
        itoa (loc,buffer,16);
                lenght=buffer;
        while(lenght.size()<len)
        lenght="0"+lenght;

  return lenght;
}
 FILE * file = fopen( "objectfile.txt", "w" );
void generateObjectFile()
{
         string res ="";


        string header="H";
        int len;
    if(programName!=""){
        header+=programName;
    }
       // cout<<CURRENTADRESS;
        string lenght=modifyLocation(CURRENTADRESS-startAdress ,6);


  string start=modifyLocation(startAdress,6);

            fprintf(file,"%s%s%s\n",header.c_str(),start.c_str(),lenght.c_str());



        int numberOfFormate4=0,numberOfotherForamte=0;
        for(int i =0; i <objectFile.size();i+=9)
    {

      numberOfFormate4=numberOfotherForamte=0;
      res="T";
      res+=modifyLocation(objectFile[i].second,6);
          string  temp="";
      int size=0;
       for(int j = i ; j < i+9 && j<objectFile.size() ; j++)
        temp+=objectFile[j].first,size+=objectFile[j].first.size();

      res+=modifyLocation(size/2,2)+temp;

     fprintf(file,"%s\n",res.c_str());

    }

  for(int i = 0 ; i < objectFileFormate4.size();i++)
        fprintf(file,"M%s05\n",modifyLocation(objectFileFormate4[i]+1,6).c_str());

        fprintf(file,"E%s\n",start.c_str());



}




int main()
{

    firstEntering=true;
    error1=true;
    error2=true;
     initRigisters();
     fillingMap();
     string inputFile;
     cout<<"Please enter the input file"<<endl;
     cin>>inputFile;
    ifstream code;
    code.open(inputFile.c_str());
    string prev="" ;
    string next="";
    while(getline(code,next)){
        if(checkSpace(next)){
        if(prev!="")
        parse(prev);
        prev=next;
        }
    }
    checkEndLine(prev);
    code.close();

     FILE * file2 = fopen( "output.txt", "w" );
   fprintf(file2,"                                                          %s\n","PASS 1");
    fprintf(file2,"                                                        %s\n","..........");
     fprintf(file2,"\n\n\n");

    fprintf(file2,"%5s%20s%20s%20s%30s             ","LineNo","Adress","Label","Op-code","Operand");
        fprintf(file2,"\n\n\n");

       for(int i=0;i<table.size();i++){
         string location="";
          char buffer [33];
          if(table[i].loc!=-1){
        itoa (table[i].loc,buffer,16);
            location=buffer;
          }
            fprintf(file2,"%5d%20s%20s%20s%30s             ",i,location.c_str(),table[i].label.c_str(),table[i].op_code.c_str(),table[i].operand.c_str());

                    fprintf(file2,"\n");
              if(table[i].comment!="")
                fprintf(file2,"%5d                                            %s\n",i,table[i].comment.c_str());
            if(table[i].error!="")
                fprintf(file2,"                                            %s\n",table[i].error.c_str());



    }


        fprintf(file2,"\n\n\n\n\n\n");
        fprintf(file2,"                     *********************Symbol Table********************\n\n");

      fprintf(file2,"%20s             |         %20s\n","Symbol","Address");
      fprintf(file2,"     ****************************|*******************************\n");
    typedef map<string, int>::const_iterator MapIterator;
for (MapIterator iter = symbolTable.begin(); iter !=symbolTable.end(); iter++)
{
            char buffer [33];

        itoa (iter->second,buffer,16);

  fprintf(file2,"%20s             |         %20s\n",iter->first.c_str(),buffer);


}
    fprintf(file2,"\n\n\n\n\n\n\n");
//

if(error1){

    objectCode();

    fprintf(file2,"                                                          %s\n","PASS 2");
    fprintf(file2,"                                                        %s\n","..........");
    fprintf(file2,"\n\n\n");

 fprintf(file2,"%5s%20s%20s%20s%30s             ","LineNo","Adress","Label","Op-code","Operand");

        fprintf(file2,"%s","ObjectCode");
        fprintf(file2,"\n\n\n");

       for(int i=0;i<table.size();i++){
            string location="";
          char buffer [33];
          if(table[i].loc!=-1){
        itoa (table[i].loc,buffer,16);
            location=buffer;
          }

        fprintf(file2,"%5d%20s%20s%20s%30s             ",i,location.c_str(),table[i].label.c_str(),table[i].op_code.c_str(),table[i].operand.c_str());
                    if(table[i].ObjectCode!=""&&table[i].error=="")
                    fprintf(file2,"%10s",table[i].ObjectCode.c_str());
                    fprintf(file2,"\n");
              if(table[i].comment!="")
                fprintf(file2,"%5d                                            %s\n",i,table[i].comment.c_str());
            if(table[i].error!="")
                fprintf(file2,"                                            %s\n",table[i].error.c_str());



    }

    }
fprintf(file2,"\n\n\n\n\n\n\n");

     if(!error1){
            //error of pass1
             fprintf(file2,"                     *********************pass1 errors********************\n\n");

       for(int i=0;i<table.size();i++){
            if(table[i].error!="")
                fprintf(file2,"line number : %d ,error: %s\n",i,table[i].error.c_str());

       }

        }
        else{
            //error of pass2
            fprintf(file2,"                     *********************pass2 errors********************\n\n");

              for(int i=0;i<table.size();i++){
                     if(table[i].error!="")
            fprintf(file2,"line number : %d ,error: %s\n",i,table[i].error.c_str());
    }

}


// clear flags

// ...
if(error2){
buildObjectFile();
generateObjectFile();
}




    return 0;

}
