//Joy Chakraborty CS280 Section 008
#include "RA5.h"
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[])
{
	LexItem item;
	ifstream reader;
    bool v=false; 
	bool ident=false; 
	bool nconst=false;
	bool sconst=false;
    int lines=1, tokens=0, ids=0, nums=0, strings=0;
    vector<LexItem> vectorTotal;
    vector<LexItem> vectorIdent;
    vector<LexItem> vectorNumbers;
    vector<LexItem> vectorStrings;
    string filename;
    
	
	if (argc == 1)
    {
		cerr << "NO SPECIFIED INPUT FILE." << endl;
		exit(1);
	}
    filename=argv[1];
    reader.open(filename);
    if(!(reader.is_open()))
    {
        cerr<<"CANNOT OPEN THE FILE " <<filename<<endl;
        exit(1);
    }
    if(reader.peek()==EOF)
    {
        cout<<"Lines: 0"<<endl;
        cout<<"Empty File."<<endl;
        exit(0);
    }
    if(argc>2){   
        for(int i=2; i<argc; i++){            
            string flag=argv[i];
            if(flag[0] != '-'){
                cerr<< "ONLY ONE FILE NAME IS ALLOWED."<<endl;
                exit(1);
            }
            if(flag == "-v"){
                v=true;
            }
            else if(flag =="-ident"){
                ident=true;
            }
            else if(flag == "-nconst"){
                nconst=true;
            }
            else if(flag == "-sconst"){
                sconst=true;
            }
            else{
                cerr<<"UNRECOGNIZED FLAG {"<<flag<<"}"<<endl;
                exit(1);
            }
        }
    }
    while(1>0)
    {
        item=getNextToken(reader, lines);
		Token tt=item.GetToken();
        if(tt==DONE) 
        {
            break;
        }
        tokens++;
        vectorTotal.push_back(item);
        if( (tt==IDENT) || (tt==NIDENT) || (tt==SIDENT) )
        {
            vectorIdent.push_back(item);
            ids++;
        }
        if( (tt==ICONST) || (tt==RCONST) )
        {
            vectorNumbers.push_back(item);
            nums++;
        }
        if(tt==SCONST)
        {
            vectorStrings.push_back(item);
            strings++;
        }
        if(tt==ERR)
        {
            break;
        }
    }
    //Converts vectorIdent into ordered, unique, string vector
    set<string> setIdent;
    int size=vectorIdent.size();
    for(int i=0; i<size; i++)
    {
        string lexeme=vectorIdent[i].GetLexeme();
        setIdent.insert(lexeme);
    }
    vector<string> lexemeIdent;
    lexemeIdent.assign(setIdent.begin(), setIdent.end());
    ids=lexemeIdent.size();
    
    
    set<double> setNumbers;
    size=vectorNumbers.size();
    for(int i=0; i<size; i++)
    {
        string lexeme=vectorNumbers[i].GetLexeme();
        double x=stod(lexeme);
        setNumbers.insert(x);
    }
    vector<double> lexemeNumbers;
    lexemeNumbers.assign(setNumbers.begin(), setNumbers.end());
    nums=lexemeNumbers.size();
    
    
    set<string> setStrings;
    size=vectorStrings.size();
    for(int i=0; i<size; i++)
    {
        string lexeme=vectorStrings[i].GetLexeme();
        setStrings.insert(lexeme);
    }
    vector<string> lexemeStrings;
    lexemeStrings.assign(setStrings.begin(), setStrings.end());
    strings=lexemeStrings.size();
    
    
    if(v==true){
        for(int i=0; i<tokens; i++){
            cout << vectorTotal[i];
        }
    }
    
    lines--;
    cout << "\nLines: " << lines << endl;
    cout << "Total Tokens: " << tokens << endl;
    cout << "Identifiers: " << ids << endl;
    cout << "Numbers: " << nums << endl;
    cout << "Strings: " << strings << endl;
    
    if(ident==true)
    {
        cout << "IDENTIFIERS:" << endl;
        cout << lexemeIdent[0];
        for(int i=1; i<ids; i++)
        {
            cout << ", " << lexemeIdent[i];
        }
        cout<<endl;
    }
    if(nconst==true)
    {
        
        cout << "NUMBERS:" << endl;
        for(int i=0; i<nums; i++)
        {
            cout << lexemeNumbers[i] << endl;
        }
	}
    if(sconst==true)
    {
        cout << "STRINGS:" << endl;
        for(int i=0; i<strings; i++)
        {
            cout << '\'' << lexemeStrings[i] << '\'' << endl;
        }
    }
}

