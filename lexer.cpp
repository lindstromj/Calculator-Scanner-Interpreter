// Egrammar Lexer

#include "EGrammar.h"

char yytext[YYTEXT_MAX];	// Global token text buffer

static int yytextpos = 0;

ifstream fin;				// lex input file stream

bool yylexopen(const char filename[])
{
	fin.open(filename, ios_base::in);

	return  fin.is_open();
}

void yytextclear()
{
	yytextpos = 0;
	yytext[yytextpos] = 0;
}

void yytextappend(int c)
{
	if (yytextpos >= YYTEXT_MAX - 1)
		return;		// ignore char
	yytext[yytextpos++] = (char)c;
	yytext[yytextpos] = 0;			// null sentinel at end
}

int yylex()
{
	int c;

	while (1)
	{
		yytextclear();
		int c;
		while ((c = fin.get()) == ' ' || c == '\t' || c == '\n')	
	
		continue;	

		if (c == '/')	
		{
			if (fin.peek() == '*')	
			{
				fin.get();	
				while (c = fin.get())
				{
				if ((c == '*' && fin.peek() == '/') || c == '\n')
					break;					
				}
				fin.get();	
					continue; 
			}
			else 
				yytext[0]='/';
				yytext[1]=0;
				return DIVOP; //MULOP be * | / 
		}

		if (c == EOF){
			return EOFSY;
		}

		if (c == ':' && fin.peek() == '=')
		{
			yytext[0]=c;
			yytext[1]=fin.get();
			yytext[2]=0;
			return ASSIGNOPP;
		}
		if (c == '('){
			yytext[0] = '(';
			yytext[1]=0;
			return LPAREN;
		}
		if (c == ')'){
			yytext[0] = ')';
			yytext[1]=0;
			return RPAREN;
		}

		if (c == '+'){
			yytext[0] = '+';
			yytext[1]=0;
			return ADDOP; //ADDOP can be + | - 
		}
		if (c == '-'){
			yytext[0] = '-';
			yytext[1]=0;
			return SUBOP; //ADDOP can be + | - 
		}
		if (c == '*'){
			yytext[0] = '*';
			yytext[1]=0;
			return MULOP; //MULOP can be * | / 
		}
		
		if (c >= '0' && c <= '9') 
		{
			int dec = 0;	
			yytext[0] = c;
			int i = 1;
			while (((c = fin.get()) >= '0' && c <= '9') || (c == '.')) 
			{
				if (c == '.')	
					dec++;
				if (dec == 2)
					throw exception();
				yytext[i] = c;
				i++;
			}
			yytext[i]=0;
			fin.unget();	
			return NUMCONST;
		}
		else 
		{
			yytext[0] = toupper(c);
			int i = 1;
			while ((c = fin.get()) != ' ' && c != '\t' && c != '\n' && c != EOF && c != ':' && c != '(' && c != ')' && c != '+' && c != '-' && c != '*' && c != '/')
			{
				yytext[i] = toupper(c);
				i++;
			}
			yytext[i] = 0; 
			fin.unget();	
			
			if (_stricmp(yytext, "read") == 0)
			{
				return READSY;
			}
			
			if (_stricmp(yytext, "write") == 0)
			{
				return WRITESY;
			}

			return ID;
		}
	}
}
