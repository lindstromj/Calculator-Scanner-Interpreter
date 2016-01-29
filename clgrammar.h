#include "EGrammar.h"
#include<fstream>
#include<iostream>
#include<string>
#include<iomanip>
#include<map>
using namespace std;

int curtok; // Current lexical token

static double stack[100];
static int top = 0;
static void stackinit() { top = 0; }
static int empty() { return top == 0; }
static double pop() { return stack[top--]; }
static void push(double v) { stack[++top] = v; }


map<string, symbolic *> symTab;
symbolic *syml;


void match(int expectedTok)
{
	if(curtok == expectedTok)
    {
        if(curtok != EOFSY)
        curtok = yylex();
    }
    else
    {
        cout << "Token " << expectedTok
        << " expected, but instead encountered "
        << yytext << endl;
    }
}

void gram()
{
	stackinit();	
	curtok = yylex();

	list();
	match(EOFSY);
}

void list() 
{
	if ((curtok == ID) || (curtok == READSY) || (curtok == WRITESY))
	{
		stmt();
		list();
	}
	
}

void stmt()
{
	if (curtok == ID)
	{
		string curID = yytext;	
		match(ID);
		match(ASSIGNOPP);			
		E();						
		symTab[curID] = new symbolic(pop());
		syml = symTab[curID];
		cout << "ASSIGN: " << curID << " = " << syml->val << endl;
	}
	if (curtok == READSY)
	{
		double inputVal;
		match(READSY);
		cout << "Read: Enter value for " << yytext << "> ";
		cin >> inputVal;
		symTab[yytext] = new symbolic(inputVal);
		match(ID);
	}
	if (curtok == WRITESY)
	{
		match(WRITESY);
		E();						
		cout << "WRITE: " << pop() << endl;
	}
}


void E() {
    T();
	Ttail();
}
void Ttail() {
    if (curtok == ADDOP)
	{
		match(ADDOP);		
		T();				
		double val2 = pop();
		double val1 = pop();
		push (val1+val2);
		Ttail();
	}
	else if (curtok == SUBOP)
	{
		match(SUBOP);		
		T();
		double val2 = pop();
		double val1 = pop();
		push (val1-val2);
		Ttail();
	}
	
}

void T() {
	F();
	Ftail();
}

void Ftail() 
 {
	if (curtok == MULOP)
	{
		match(MULOP);
		F();
		double val2 = pop();
		double val1 = pop();
		push (val1*val2);
		Ftail();
	}
	else if (curtok == DIVOP)
	{
		match(DIVOP);
		F();
		double val2 = pop();
		double val1 = pop();
		push (val1/val2);
		Ftail();
	}
	
}

void F() 
{
	if (curtok == LPAREN)
	{
		match(LPAREN);
		E();
		match(RPAREN);
	}
	else if (curtok == ID)
	{
		if (symTab.count(yytext) == 0)
		{
			throw exception();		
		}
		syml = symTab[yytext];
		push (syml->val);
		match(ID);
	}
	else if (curtok == NUMCONST)
	{
		push (atof(yytext));
		match(NUMCONST);
	}

}
