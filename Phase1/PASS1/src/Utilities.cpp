#include "Utilities.h"

Utilities::Utilities()
{
    //ctor
}

/////////////////
string Utilities::Comment(vector<string>a)
{
    string temp="";
    for(int i=0; i<a.size(); i++)
        temp+=a[i]+" ";
    return temp;
}

int Utilities::checkByte(string a)
{

    if(a.size()<4)
        return -1;

    if(a[0]=='x'&&a[1]=='\''&&a[a.size()-1]=='\'')
    {
        if((a.size()-3)%2==1)
            return -1;
        for(int i=2; i<a.size()-1; i++)
        {
            if((a[i]>='0'&&a[i]<='9')||(a[i]>='a'&&a[i]<='f'))
            {

            }
            else
                return -1;
        }
        return ((a.size()-3)/2);
    }
    else if(a[0]=='c'&&a[1]=='\''&&a[a.size()-1]=='\'')
    {

        return (a.size()-3);
    }
    else
        return -1;
}

bool Utilities::checkWord(string a)
{
    if(a.size()==1)
    {
        if((a[0]<'0'||a[0]>'9'))
            return false;
        return true;
    }
    if(a.size()==2&&a[1]=='-')
        return false;


    if(a[0]!='@'&&a[0]!='#'&&a[0]!='-'&&(a[0]<'0'||a[0]>'9'))
        return false;

    for(int i=1; i<a.size(); i++)
    {
        if(a[i]<'0'||a[i]>'9')
        {
            if(i==1)
            {
                if(a[1]=='-'&&(a[0]=='#'||a[0]=='@'))
                {

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


int Utilities::todecimal(string a)
{
    int ans=0;
    int t=a.size()-1;
    for(int i=0; i<a.size(); i++)
    {
        if(a[i]=='A'||a[i]=='a')
        {
            ans+=10*pow(16,t);

        }
        else if(a[i]=='B'||a[i]=='b')
        {
            ans+=11*pow(16,t);
        }
        else if(a[i]=='C'||a[i]=='c')
        {
            ans+=12*pow(16,t);
        }
        else if(a[i]=='D'||a[i]=='d')
        {
            ans+=13*pow(16,t);
        }
        else if(a[i]=='E'||a[i]=='e')
        {
            ans+=10*pow(14,t);
        }
        else if(a[i]=='F'||a[i]=='f')
        {
            ans+=10*pow(15,t);
        }
        else if(a[i]>='0'&&a[i]<='9')
        {
            ans+=(a[i]-'0')*pow(16,t);
        }
        else
            return -1;
        t--;
    }
    return ans;
}

int Utilities::Tointeger(string str)
{
    int res = 0 ;

    for(int i = 0 ; i < str.size() ; i++)
    {
        if(str[i]<'0'||str[i]>'9')
            return -1;
        res =  res*10 + (int)(str[i]-'0');
    }

    return res;
}
string Utilities::Tolower(string str)
{
    for(int i=0 ; i <str.size() ; i++)
        str[i]=tolower(str[i]);

    return str;
}
bool Utilities::check_operand(string opcode,string oper)
{

    if(opcode.compare("tkxr")==0||opcode.compare("clear")==0)
    {
        if(oper.compare("a")==0||oper.compare("s")==0||oper.compare("t")==0||oper.compare("x")==0
                ||oper.compare("b")==0||oper.compare("l")==0)
        {

            return true;
        }
        else
        {

            return false;
        }

    }
    else
    {

        if(oper.size()==3)
        {
            if((oper[0]=='a'||oper[0]=='s'||oper[0]=='t'||oper[0]=='x'||oper[0]=='b'||oper[0]=='l')&&
                    oper[1]==','&&(oper[2]=='a'||oper[2]=='s'||oper[2]=='t'||oper[2]=='x'||oper[0]=='b'
                                   ||oper[0]=='l'))
            {

                return true;
            }
            else
            {

                return false;
            }
        }
        else
        {

            return false;
        }
    }


}
int Utilities::validateOpcode(string a)
{

    if( inst.find(a ) != inst.end() )
    {

        return inst[a];
    }
    return -1;

}
bool Utilities::duplicateLable(string a)
{
    if( symbolTable.find(a ) == symbolTable.end() )
        return false;
    return true;
}

void Utilities::oneWord ( vector<string> line,vector<string> comment,int byt)
{

    string temp=Comment(comment);


    table.push_back(Entry(CURRENTADRESS,"",line[0],"",temp,""));
    CURRENTADRESS+=byt;

}
void Utilities::twoWord ( vector<string> line,int typeByte,vector<string>comment)
{

    string temp=Comment(comment);

    table.push_back(Entry(CURRENTADRESS,"",line[0],line[1],temp,""));
    CURRENTADRESS+=typeByte;

}


void Utilities::threeWord ( vector<string> line,int typeByte,vector<string>comment)
{
    string temp=Comment(comment);
    symbolTable[line[0]]=CURRENTADRESS;
    table.push_back(Entry(CURRENTADRESS,line[0],line[1],line[2],temp,""));


    if(typeByte!=5)
        CURRENTADRESS+=typeByte;
    else
    {
        if(line[1]=="byte")
        {
            int check=checkByte(line[2]);
            if(check!=-1)
                CURRENTADRESS+=check;
            else
                table[table.size()-1].error="****Error: Invalid Operand";
        }
        else if(line[1]=="word")
        {
            if(checkWord(line[2]))
                CURRENTADRESS+=3;
            else
                table[table.size()-1].error="****Error: Invalid Operand";
        }
        else if(line[1]=="resb")
        {
            int numOfByt=Tointeger(line[2]);
            if(numOfByt==-1)
            {
                table[table.size()-1].error="****Error: Invalid Operand";


            }

            else
                CURRENTADRESS+=numOfByt;
        }
        else
        {
            int numOfByt=Tointeger(line[2]);
            if(numOfByt==-1)
                table[table.size()-1].error="****Error: Invalid Operand";



            else
                CURRENTADRESS+=numOfByt*3;
        }

    }


}
void Utilities::parse_sic(string  line )
{
    if(line.size()>66)
    {
        table.push_back( Entry( CURRENTADRESS ,"" ,"" ,"" ,"","****Error: Invalid spaces in this line" ) ) ;

    }

    vector<string>res;
    vector<string>comments;
    string temp="";
    bool com=false;
    bool check_spaces=false;
    bool comment_field=false;
    if(line!=""&&line[0]=='.')
    {

    }
    else
    {
        for(int i=0; i<line.length()&&i<8; i++)
        {

            if(line[i]!=' ')
            {
                temp+=line[i];
            }
        }
        if(temp!="")
        {

            if(line[0]==' ')
            {
                check_spaces=true;
            }
            temp="";
        }
//................................

        for(int i=9; i<line.length()&&i<15; i++)
        {

            if(line[i]!=' ')
            {
                temp+=line[i];
            }
        }
        if(temp!="")
        {
            if(line[8]==' '||line[8]=='+')
            {

            }
            else
            {
                check_spaces=true;
            }

            if(line[9]==' ')
            {
                check_spaces=true;
            }
            temp="";
        }
//................................

        for(int i=17; i<line.length()&&i<35; i++)
        {

            if(line[i]!=' ')
            {
                temp+=line[i];
            }
        }
        if(temp!="")
        {
            if(line[15]!=' '||line[16]!=' ')
            {
                check_spaces=true;
            }

            if(line[17]==' ')
            {
                check_spaces=true;
            }
            temp="";
        }

        //................................

        for(int i=35; i<line.length(); i++)
        {
            if(line[i]!=' ')
            {
                temp+=line[i];
            }
        }
        if(temp!="")
        {

            comment_field=true;
            temp="";
        }
        if(check_spaces)
        {
            table.push_back(Entry(CURRENTADRESS,"","","","","****Error: invalid spaces in this line"));
        }

    }
    temp="";

    for(int i = 0 ; i < line.size(); i++)
    {
        if(line[i]!=' ')
            temp+=line[i];

        else if(temp!="")
        {


            if(temp[0]=='.'||i>=35)
                com=true;

            if(!com)
            {
                temp=Tolower(temp);
                res.push_back(temp);
            }

            else
                comments.push_back(temp);
            temp="";



        }
    }

    if(temp!="")
    {


        if(temp[0]=='.'||comment_field)
            com=true;


        if(!com)
        {
            temp=Tolower(temp);
            res.push_back(temp);
        }

        else
            comments.push_back(temp);

    }




    if(res.size()>0&&firstEntering)
    {
        string start="";
        if(line.size()>13)
        {
            for(int i=9; i<14; i++)
            {
                start+=line[i];
            }
            start=Tolower(start);
        }

        if(res.size()==2)
            CURRENTADRESS=todecimal(res[1]);
        else if(res.size()==3)
            CURRENTADRESS=todecimal(res[2]);

        firstEntering=false;
        if(res.size()==2&&res[0].compare("start")==0&&CURRENTADRESS!=-1&&start.compare("start")==0)
        {
            temp=Comment(comments);

            table.push_back(Entry(CURRENTADRESS,"",res[0],res[1],temp,""));
        }
        else if(res.size()==3&&res[1].compare("start")==0&&CURRENTADRESS!=-1&&start.compare("start")==0)
        {
            temp=Comment(comments);

            table.push_back(Entry(CURRENTADRESS,res[0],res[1],res[2],temp,""));
        }
        else
        {
            temp=Comment(comments);
            string lin=Comment(res);

            table.push_back(Entry(CURRENTADRESS,lin,"","",temp,"****Error: invalid start of the program"));
        }

    }
    else if(res.size()==3)
    {

        int byt=validateOpcode(res[1]);
        if(!duplicateLable(res[0]))
        {


            if(byt!=-1)
            {
                if((byt==2&&check_operand(res[1],res[2]))||byt!=2)
                    threeWord(res,byt,comments);
                else
                {
                    temp=Comment(comments);

                    table.push_back(Entry(CURRENTADRESS,res[0],res[1],res[2],temp,"****Error: Invalid Operand"));
                    CURRENTADRESS+=byt;

                }


            }

            else
            {
                temp=Comment(comments);
                table.push_back(Entry(CURRENTADRESS,res[0],res[1],res[2],temp,"****Error: Invalid OpCode"));
                CURRENTADRESS+=byt;

            }
        }
        else
        {
            temp=Comment(comments);
            table.push_back(Entry(CURRENTADRESS,res[0],res[1],res[2],temp,"****Error: Duplicate Symbol"));
            CURRENTADRESS+=byt;

        }
    }


    else if(res.size()==2)
    {
        int byt=validateOpcode(res[0]);

        if(byt!=-1)
        {
            if((byt==2&&check_operand(res[0],res[1]))||byt!=2)
            {

                twoWord(res,byt,comments);

            }
            else
            {
                temp=Comment(comments);
                table.push_back(Entry(CURRENTADRESS,"",res[0],res[1],temp,"****Error: Invalid Operand"));
                CURRENTADRESS+=byt;

            }
        }

        else
        {
            temp=Comment(comments);
            table.push_back(Entry(CURRENTADRESS,"",res[0],res[1],temp,"****Error: Invalid OpCode"));
            CURRENTADRESS+=byt;


        }

    }
    else if(res.size()==1)
    {

        string str = res[0];
        int byt=validateOpcode(str);
        if( byt!=-1)
            oneWord(res,comments,byt);

        else
        {
            temp=Comment(comments);
            table.push_back(Entry(CURRENTADRESS,"",res[0],"",temp,"****Error: Invalid OpCode"));
            CURRENTADRESS++;
        }

    }
    else if(res.size()>3)
    {
        table.push_back( Entry( CURRENTADRESS , "",line ,"" ,"","****Error: Invalid Entry" ) ) ;
    }
    else if(comments.size()>0)
    {
        temp=Comment(comments);
        if(!firstEntering)
            table.push_back( Entry( CURRENTADRESS ,"" ,"" ,"" ,temp,"" ) ) ;
        else
            table.push_back( Entry( -1 ,"" ,"" ,"" ,temp,"" ) ) ;

    }


}

void Utilities::parse(string  line )
{


    vector<string>res;
    vector<string>comments;
    string temp="";
    bool com=false;

    for(int i = 0 ; i < line.size(); i++)
    {
        if(line[i]!=' ')
            temp+=line[i];

        else if(temp!="")
        {


            if(temp[0]=='.')
                com=true;

            if(!com)
            {
                temp=Tolower(temp);
                res.push_back(temp);
            }

            else
                comments.push_back(temp);
            temp="";



        }
    }

    if(temp!="")
    {


        if(temp[0]=='.')
            com=true;


        if(!com)
        {
            temp=Tolower(temp);
            res.push_back(temp);
        }

        else
            comments.push_back(temp);

    }




    if(res.size()>0&&firstEntering)
    {
        if(res.size()==2)
            CURRENTADRESS=todecimal(res[1]);
        else if(res.size()==3)
            CURRENTADRESS=todecimal(res[2]);

        firstEntering=false;
        if(res.size()==2&&res[0].compare("start")==0&&CURRENTADRESS!=-1)
        {
            temp=Comment(comments);

            table.push_back(Entry(CURRENTADRESS,"",res[0],res[1],temp,""));
        }
        else if(res.size()==3&&res[1].compare("start")==0&&CURRENTADRESS!=-1)
        {
            temp=Comment(comments);

            table.push_back(Entry(CURRENTADRESS,res[0],res[1],res[2],temp,""));
        }
        else
        {
            temp=Comment(comments);
            string lin=Comment(res);

            table.push_back(Entry(CURRENTADRESS,lin,"","",temp,"****Error: invalid start of the program"));
        }



    }
    else if(res.size()==3)
    {

        int byt=validateOpcode(res[1]);
        if(!duplicateLable(res[0]))
        {


            if(byt!=-1)
            {
                if((byt==2&&check_operand(res[1],res[2]))||byt!=2)
                    threeWord(res,byt,comments);
                else
                {
                    temp=Comment(comments);
                    table.push_back(Entry(CURRENTADRESS,res[0],res[1],res[2],temp,"****Error: Invalid Operand"));
                    CURRENTADRESS+=byt;
                }


            }

            else
            {
                temp=Comment(comments);
                table.push_back(Entry(CURRENTADRESS,res[0],res[1],res[2],temp,"****Error: Invalid OpCode"));
                CURRENTADRESS+=byt;

            }
        }
        else
        {
            temp=Comment(comments);
            table.push_back(Entry(CURRENTADRESS,res[0],res[1],res[2],temp,"****Error: Duplicate Symbol"));
            CURRENTADRESS+=byt;

        }
    }


    else if(res.size()==2)
    {
        int byt=validateOpcode(res[0]);

        if(byt!=-1)
        {
            if((byt==2&&check_operand(res[0],res[1]))||byt!=2)
            {

                twoWord(res,byt,comments);

            }
            else
            {
                temp=Comment(comments);
                table.push_back(Entry(CURRENTADRESS,"",res[0],res[1],temp,"****Error: Invalid Operand"));
                CURRENTADRESS+=byt;

            }
        }

        else
        {
            temp=Comment(comments);
            table.push_back(Entry(CURRENTADRESS,"",res[0],res[1],temp,"****Error: Invalid OpCode"));
            CURRENTADRESS+=byt;

        }

    }
    else if(res.size()==1)
    {

        string str = res[0];
        int byt=validateOpcode(str);
        if( byt!=-1)
            oneWord(res,comments,byt);

        else
        {
            temp=Comment(comments);
            table.push_back(Entry(CURRENTADRESS,"",res[0],"",temp,"****Error: Invalid OpCode"));
            CURRENTADRESS++;
        }

    }
    else if(res.size()>3)
    {
        table.push_back( Entry( CURRENTADRESS , "",line ,"" ,"","****Error: Invalid Entry" ) ) ;
    }
    else if(comments.size()>0)
    {
        temp=Comment(comments);
        if(!firstEntering)
            table.push_back( Entry( CURRENTADRESS ,"" ,"" ,"" ,temp,"" ) ) ;
        else
            table.push_back( Entry( -1 ,"" ,"" ,"" ,temp,"" ) ) ;

    }



}
void Utilities::fillingMap()
{

    ifstream form;
    form.open("format.txt");
    string Line ;
    while(getline(form,Line))
    {

        string temp="";
        for(int i=0; i<Line.size()-1; i++)
            temp+=Line[i];

        inst[temp]=Line[Line.size()-1]-'0';
    }

    form.close();

}


void Utilities::checkEndLine(string line)
{
    vector<string>res;
    vector<string>comments;
    string temp="";
    bool com=false;

    for(int i = 0 ; i < line.size(); i++)
    {
        if(line[i]!=' ')
            temp+=line[i];

        else if(temp!="")
        {


            if(temp[0]=='.')
                com=true;

            if(!com)
            {
                temp=Tolower(temp);
                res.push_back(temp);
            }

            else
                comments.push_back(temp);
            temp="";



        }
    }

    if(temp!="")
    {


        if(temp[0]=='.')
            com=true;


        if(!com)
        {
            temp=Tolower(temp);
            res.push_back(temp);
        }

        else
            comments.push_back(temp);

    }

    temp=Comment(comments);
    if(res.size()==1&&res[0]=="end")
    {

        table.push_back(Entry(CURRENTADRESS,"",res[0],"",temp,""));

    }
    else
    {
        string lin=Comment(res);
        table.push_back(Entry(CURRENTADRESS,lin,"","",temp,"****Error: invalid end of the program"));
    }

}

bool Utilities::checkSpace(string a)
{
    for(int i=0; i<a.size(); i++)
        if(a[i]!=' ')
            return true;
    return false;
}
















///////////////////
Utilities::~Utilities()
{
    //dtor
}
