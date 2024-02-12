//Joy Chakraborty CS280 Section 008
#include <iostream>
#include <cctype>
#include <regex>
#include <string>
#include "lex.h" 
using namespace std;

regex regexIF(R"rgx(^(if)$)rgx");
regex regexWRITELN(R"rgx(^(writeln)$)rgx");
regex regexELSE(R"rgx(^(else)$)rgx");
regex regexIDENT(R"rgx(^(\w)+((\w)|(\d))*$)rgx");
regex regexSIDENT(R"rgx(^(@)(\w)+((\w)|(\d))*$)rgx");
regex regexNIDENT(R"rgx(^(\$)(\w)+((\w)|(\d))*$)rgx");

LexItem id_or_kw(const string& lexeme, int linenum)
{
    Token LexItemToken;
    
    if(regex_match(lexeme, regexIDENT))
    {
        LexItemToken=IDENT;
    }
    if(regex_match(lexeme, regexSIDENT))
    {
        LexItemToken=SIDENT;
    }
    else if(regex_match(lexeme, regexNIDENT))
    {
        LexItemToken=NIDENT;
    }
    
    if(regex_match(lexeme, regexIF))
    {
        LexItemToken=IF;
    }
    else if(regex_match(lexeme, regexWRITELN))
    {
        LexItemToken=WRITELN;
    }
    else if(regex_match(lexeme, regexELSE))
    {
        LexItemToken=ELSE;
    }
    
    LexItem tester=LexItem(LexItemToken, lexeme, linenum);
    return tester;
}

ostream& operator<<(ostream& out, const LexItem& luthor)
{
    Token token=luthor.GetToken();
	string lexeme=luthor.GetLexeme();
    int line=luthor.GetLinenum();
    
    // Keywords
    if(token==WRITELN)
    {
    	out << "WRITELN\n";
	}
	if(token==IF)
	{
		out << "IF\n";
	}
	if(token==ELSE)
	{
    	out << "ELSE\n";
	}
    // Identifiers
    if(token==IDENT)
    {
		out << "IDENT(" << lexeme << ")\n";
	}
    if(token==NIDENT)	
	{
		out << "NIDENT(" << lexeme << ")\n";
	}
    if(token==SIDENT)
    {
		out << "SIDENT(" << lexeme << ")\n";
	}
    // Constants
    if(token==ICONST)
    {
    	out << "ICONST(" << lexeme << ")\n";
	}
	if(token==RCONST)
	{
    	out << "RCONST(" << lexeme << ")\n";
	}
	if(token==SCONST)
	{
    	out << "SCONST(" << lexeme << ")\n";
    }
    // Operators
    if(token==PLUS)
    {
    	out << "PLUS\n";
    }
    if(token==MINUS)
    {
    	out << "MINUS\n";
    }
    if(token==MULT)
    {
    	out << "MULT\n";
    }
    if(token==DIV)
    {
    	out << "DIV\n";
	}
    if(token==EXPONENT)
    {
    	out << "EXPONENT\n";
	}
    if(token==ASSOP)
    {
        out << "ASSOP\n";
	}
	if(token==NEQ)
	{
		out << "NEQ\n";
	}
    if(token==NGTHAN)
    {
    	out << "NGTHAN\n";
	}
	if(token==NLTHAN)
	{
		out << "NLTHAN\n";
	}
    if(token==CAT)
    {
    	out << "CAT\n";
	}
    if(token==SREPEAT)
    {
    	out << "SREPEAT\n";
	}
    if(token==SEQ)
    {
    	out << "SEQ\n";
	}
    if(token==SLTHAN)
    {
    	out << "SLTHAN\n";
	}
    if(token==SGTHAN)
    {
    	out << "SGTHAN\n";
	}
    // Delimeters (still labeled as "Operators")
    if(token==COMMA)
    {
    	out << "COMMA\n";
	}
    if(token==SEMICOL)
    {
    	out << "SEMICOL\n";
	}
    if(token==LPAREN)
    {
    	out << "LPAREN\n";
	}
    if(token==RPAREN)
    {
    	out << "RPAREN\n";
	}
    if(token==LBRACES)
    {
    	out << "LBRACES\n";
	}
    if(token==RBRACES)
    {
    	out << "RBRACES\n";
	}
    // ERROR
   if(token==ERR)
    {
    	cout << "Error in line " << line << " (" << lexeme << ")" << endl;
        exit(1);
	}
    if(token==DONE)
    {
        exit(0);
    }
    
    return out;
}

LexItem getNextToken (istream& in, int& linenumber)
{
    enum TokState{START, INID, INSTRING, ININT, INREAL, INCOMMENT, INSOP, INSREPEAT, INASSOP};
    char character;
    TokState lexstate=START;
    string lexeme;
    while(in.get(character))
    {
        switch(lexstate)
        {
            case START:
            {
                if(character=='\n')
                {
                    linenumber++;
                    break;
                }
                if(isspace(character))
                {
                    break;
                }
                lexeme="";
                lexeme+=character;
                if(character=='\'')
                {
                    lexstate=INSTRING;
                    break;
                }
                if((isalpha(character)) || (character=='_'))
                {
                    lexstate=INID;
                    break;
                }
                if( (character=='@') || (character=='$') )
                {
                    if( (isalpha(char(in.peek()))) || (char(in.peek())=='_') )
                    {
                        lexstate=INID;
                        break;
                    }
                }
                if(isdigit(character))
                {
                    lexstate=ININT;
                    break;
                }
                if(character=='#')
                {
                    lexstate=INCOMMENT;
                    break;
                }
                if(character=='+')
                {
                    return LexItem(PLUS, lexeme, linenumber);
                    break;
                }
                if(character=='-')
                {
                    if( !( ( (char(in.peek())=='e') || char(in.peek())=='E' ) || ( (char(in.peek())=='l') || char(in.peek())=='L' ) || ( (char(in.peek())=='g') || char(in.peek())=='G' ) ) )
                    {
                        return LexItem(MINUS, lexeme, linenumber);
                        break;
                    }
                    else
                    {
                        lexstate=INSOP;
                        break;
                    }
                }
                if(character=='*')
                {
                    lexstate=INSREPEAT;
                    break;
                }
                if(character=='/')
                {
                    return LexItem(DIV, lexeme, linenumber);
                    break;
                }
                if(character=='^')
                {
                    return LexItem(EXPONENT, lexeme, linenumber);
                    break;
                }
                if(character=='=')
                {
                    lexstate=INASSOP;
                    break;
                }
                if(character=='(')
                {
                    return LexItem(LPAREN, lexeme, linenumber);
                    break;
                }
                if(character==')')
                {
                    return LexItem(RPAREN, lexeme, linenumber);
                    break;
                }
                if(character=='{')
                {
                    return LexItem(LBRACES, lexeme, linenumber);
                    break;
                }
                if(character=='}')
                {
                    return LexItem(RBRACES, lexeme, linenumber);
                    break;
                }
                if(character=='.')
                {
                    return LexItem(CAT, lexeme, linenumber);
                    break;
                }
                if(character==',')
                {
                    return LexItem(COMMA, lexeme, linenumber);
                    break;
                }
                if(character==';')
                {
                    return LexItem(SEMICOL, lexeme, linenumber);
                    break;
                }
                if(character=='>')
                {
                    return LexItem(NGTHAN, lexeme, linenumber);
                    break;
                }
                if(character=='<')
                {
                    return LexItem(NLTHAN, lexeme, linenumber);
                    break;
                }
                return LexItem(ERR, lexeme, linenumber);
                break;
            }    
            
            case INID:
            {            
                if( !( (isalpha(character)) || (isdigit(character)) || (character=='_') ) )
                {
                    in.putback(character);
                    lexstate=START;
                    return id_or_kw(lexeme, linenumber);
                    break;
                }
                else
                {
                    lexeme+=character;
                    break;
                }
                return LexItem(ERR, lexeme, linenumber);
                break;
            }
            
            case INSTRING:
            {
                if(character=='\'')
                {
                    lexstate=START;
                    lexeme=lexeme.substr(1);
                    return LexItem(SCONST, lexeme, linenumber);
                    break;
                }
                if(character=='\n')
                {
                    lexstate=START;
                    return LexItem(ERR, lexeme, linenumber);
                    break;
                }
                else
                {
                    lexeme+=character;
                    break;
                }
                return LexItem(ERR, lexeme, linenumber);
                break;
            }
            
            case ININT:
            {
                if(character=='.')
                {
                    lexstate=INREAL;
                    lexeme+=character;
                    break;
                }
                if(isdigit(character))
                {
                    lexeme+=character;
                    break;
                }
                else
                {
                    in.putback(character);
                    lexstate=START;
                    return LexItem(ICONST, lexeme, linenumber);
                    break;
                }
            }
                
            case INREAL:
            {
                if(isdigit(character))
                {
                    lexeme+=character;
                    break;
                }
                else if(character=='.')
                {
                    lexeme+=character;
                    return LexItem(ERR, lexeme, linenumber);
                    break;
                }
                else
                {
                    in.putback(character);
                    lexstate=START;
                    return LexItem(RCONST, lexeme, linenumber);
                    break;
                }
            }
                
            case INCOMMENT:
            {
                if(character=='\n')
                {
                    lexstate=START;
                    linenumber++;
                    break;
                }
                break;
            }
            case INSOP:
            {
                if( (character=='e') || (character=='E') )
                {
                    lexeme+=character;
                    break;
                }
                if( (character=='l') || (character=='L') )
                {
                    lexeme+=character;
                    break;
                }
                if( (character=='g') || (character=='G') )
                {
                    lexeme+=character;
                    break;
                }
                
                if( (lexeme=="-e") || (lexeme=="-E") )
                {
                    if( (character=='q') || (character=='Q') )
                    {
                        lexeme+=character;
                        lexstate=START;
                        return LexItem(SEQ, lexeme, linenumber);
                        break;
                    }
                }
                if( (lexeme=="-l") || (lexeme=="-L") )
                {
                    if( (character=='t') || (character=='T') )
                    {
                        lexeme+=character;
                        lexstate=START;
                        return LexItem(SLTHAN, lexeme, linenumber);
                        break;
                    }
                }
                if( (lexeme=="-g") || (lexeme=="-G") )
                {
                    if( (character=='t') || (character=='T') )
                    {
                        lexeme+=character;
                        lexstate=START;
                        return LexItem(SGTHAN, lexeme, linenumber);
                        break;
                    }
                }
                lexstate=START;
                return LexItem(ERR, lexeme, linenumber);
                break;
            }
            case INSREPEAT:
            {
                if(character=='*')
                {
                    lexeme+=character;
                    lexstate=START;
                    return LexItem(SREPEAT, lexeme, linenumber);
                    break;
                }
                else
                {
                    in.putback(character);
                    lexstate=START;
                    return LexItem(MULT, lexeme, linenumber);
                    break;
                }
            }
            case INASSOP:
            {
                if(character=='=')
                {
                    lexeme+=character;
                    lexstate=START;
                    return LexItem(NEQ, lexeme, linenumber);
                    break;
                }
                else
                {
                    in.putback(character);
                    lexstate=START;
                    return LexItem(ASSOP, lexeme, linenumber);
                    break;
            	}
            }
        }
    }
    return LexItem(DONE, "", linenumber);
}