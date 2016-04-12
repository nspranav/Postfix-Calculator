//
//  main.cpp
//  
//
//  Created by Pranav Nadigapu on 4/7/16.
//  Copyright © 2016 Pranav Nadigapu. All rights reserved.
//

#include "Postfix_cal.h"

bool unarySign(const string &str,int &pos)
{
    if(pos<str.length()-1)
    {
        if(str.at(pos)=='+'||str.at(pos)=='-') //check if has characters +/-
        {
            if(isdigit(str.at(pos+1))||str.at(pos+1)=='.') //check if next to unary is point or digit
            {
                //pos++;
                return true;
            }
        }
    }
    return false;
}

bool floatPoint(const string &str,int &pos)
{
    
    if(pos<str.length()-1)
    {
        if(str.at(pos)=='.') //check if character is .
        {
            if(isdigit(str.at(pos+1))) //check if next to unary is point or digit
            {
                //pos++;
                return true;
            }
        }
    }
    return false;
}

bool isValidOperator(char c)
{
    if((c=='+'||c=='-'||c=='*'||c=='/'))
    {
        return true;
    }
    return false;
}

double getNumber(string &str, int &pos)
{
    str=str.substr(pos);
    int count=0;
    bool flag=false;
    for(int i=pos;i<str.length();i++)// check if token has two decimals, if yes then exit
    {
        if(str.at(i)=='.')
        {
            count++;
            flag=true;
        }
        if(flag&&(isValidOperator(str.at(i))))
        {
            
            std::string::size_type sz;     // alias of size_t
            
            double num = std::stod (str,&sz); //parses string for a number and stores the pos of non number
            pos=(int)sz;
            return num;
        }
        if(count>1&&flag)
        {
            cerr<< "Error: Invalid token "<<str<<endl;
            exit(1);
        }
    }
    std::string::size_type sz;     // alias of size_t
    
    double num = std::stod (str,&sz); //parses string for a number and stores the pos of non number
    pos=(int)sz;
    return num;
}


double operation(char c,double num1,double num2)
{
    switch (c) {
        case '+':
            return num1+num2;
        
        case '-':
            return num2-num1;
            
        case '*':
            return num1*num2;
            
        case '/':
            return num2/num1;
 
    }
    return 0;
}

double popStack(stack<double> &stk)
{
    if(stk.empty())
    {
        cerr<<"Stack is empty."<<endl;
    }
    else
    {
        double top=stk.top();
        stk.pop();
        return top;
    }
    return 0;
}

void printResult(stack<double> &stk)
{
    if(stk.empty())
    {
        cerr<<"Stack is empty."<<endl;
    }
    else
    {
        cout<<setprecision(3)<< stk.top()<<endl;
    }

}

void emptyStack(stack<double> &st)
{
    while (!st.empty())
    {
        st.pop();
    }
}

void process_tokens(string str, stack<double> &st)
{
    int tok=(int)st.size(); //to check if this is a new token
    double num;
    int pos=0;
    bool flag=false,unary=false;
    for(int i=0;i<str.length();i++)
    {
        flag=true;
        if(isdigit(str.at(i))||floatPoint(str, pos))
        {
            num=getNumber(str,pos);
            i=pos-1;
            st.push(num);
            //cout<<"The number is "<<num<<". The position the number ended is "<<pos<<endl;
            flag=false;
            
            if(pos==str.length())     //check if token has only number
                return;
            continue;
        }
        if(unarySign(str, pos))
        {
            num=getNumber(str,pos);
            i=pos;
            st.push(num);
            //cout<<"The number is "<<num<<". The position the number ended is "<<pos<<endl;
            flag=false;
            unary=true;
            if(pos==str.length())     //check if token has only number
                return;
        }
        if(isValidOperator(str.at(i)))
        {
                if(st.size()>tok+1&&st.size()>1)
                {
                    double num1,num2;
                    num1=popStack(st);
                    num2=popStack(st);
                    st.push(operation(str.at(i), num1, num2));
                    flag=false;
                }
                else if(st.size()>1&&st.size()==tok)
                {
                    double num1,num2;
                    num1=popStack(st);
                    num2=popStack(st);
                    st.push(operation(str.at(i), num1, num2));
                    flag=false;
                }
                else
                {
                    str=str.substr(i);
                    if(str.length()==1) // check if valid operator but stack is empty
                    {
                        cerr<<"Error: Stack Empty "<<endl;
                        continue;
                    }
                    i=-1;
                    pos=0;
                    tok=(int)st.size();
                    continue;
                }

        }
        if(str.at(i)=='=')
        {
            printResult(st);
            flag=false;
        }
        if(str.at(i)=='c')
        {
            emptyStack(st);
            if(str.length()>1)
            {
                str=str.substr(i+1);
                i=-1;
                pos=0;
                tok=(int)st.size();
                continue;
            }
            flag=false;
        }
        if(flag==true)
        {
            cerr<<"Error: Invalid character "<< str.at(i)<<endl;
        }
    }
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    stack<double> st ;
    string str, temp;
    while (getline(cin, str, '\n')) {
        //if(str.length()!=0)
        
        stringstream ss(str);
        while(getline(ss,temp, ' '))
        {
            //cout<<"the token is "<<temp<<endl;
            process_tokens(temp,st);
           
        }
        //cout<<endl;
    }
    printResult(st);
    return 0;
}


