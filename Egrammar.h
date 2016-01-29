// Egrammar declarations

#ifndef _EGRAMMAR_H
#define _EGRAMMAR_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

extern enum EgrammarTokens {
	EOFSY = 0, ADDOP, MULOP, ASSIGNOPP, LPAREN, RPAREN, READSY, WRITESY, ID, NUMCONST, SUBOP, DIVOP
};

class symbolic {            
public:
	symbolic(double v = 0) : val(v)   { }
	double val;
};

#define YYTEXT_MAX 100
extern char yytext[YYTEXT_MAX];	// Global token text buffer

void list();
void stmt();
void E();
void Ttail();
void T();
void Ftail();
void F();
bool yylexopen(const char filename[]);
void yytextclear();
void yytextappend(int c);
int yylex();
int yyparse();
void match(int expectedTok);
void gram();

int yyparse();

#endif
