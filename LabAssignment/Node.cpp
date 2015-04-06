
#include "NodeHeader2.h"
#include "y.tab.h"
#include <fstream>
#include <assert.h>

std::ofstream out("generated.c");
int RegIndex  = 0;
int LableIndex = 0;

void SymbolTable::Push()
{
      for(Str_to_Int::iterator it = Table.begin();it != Table.end();it++)
      {
            out<<"\nint "<<it->first<<";";//key
            it->second;//value
      }
}

int ConstantNode::Process(std::string str)
{
      RegIndex++;
      out<<" "<<value<<" ";
      return RegIndex;
}

int SymbolNode::Process(std::string str)
{
      RegIndex++;
      out<<" "<<symbol<<" ";
      return RegIndex;      
}

int OperationNode::Process(std::string str)
{
      switch(operation)
      {
            case IF:
                        if( right->type == Block )
                        {
                              out<<"\nif (";
                              int reg = left->Process(str);
                              out<<" ) \n";
                              right->Process(str);
                              return 0;
                        }
                        else  //right is an else block
                        {
                              assert(right->type == Operation);
                              out<<"\n"<<str<<" if ( ";
                              int reg = left->Process(str);
                              out<<" ) \n";
                              right->left->Process(str);
                              out<<"\n"<<str<<" else \n";                              
                              right->right->Process(str);
                              return 0;
                        }
            case WHILE:
                         {     
                              int L = ++LableIndex; 
                              out<<" while ( ";
                              int reg2 = left->Process(str);  //This is Expression
                              out<<")";
                              int reg1 = right->Process(str); //This is block
                              return 0;
                        }
            case READ:
                        {
                              out<<" scanf(\"%d\", &";right->Process(str);
                              out<<")";
                              //~ assert(0);
                              return 0;
                        }
            case PRINT:
                        {
                              out<<" printf(\"%d\",";right->Process(str);
                              out<<")";
                              return 0;
                        }
            case '+':
                        {
                              int reg1 = left->Process(str);
                              out<<" + ";
                              int reg2 = right->Process(str);
                              RegIndex++;
                              return RegIndex;
                        }
            case '-':
                        {
                              int reg1 = left->Process(str);
                              out<<" - ";
                              int reg2 = right->Process(str);
                              RegIndex++;
                              return RegIndex;
                        }
            case '*':
                        {
                              int reg1 = left->Process(str);
                              out<<" * ";
                              int reg2 = right->Process(str);
                              RegIndex++;
                              return RegIndex;
                        }
            case '/':
                        {
                              int reg1 = left->Process(str);
                              out<<" / ";
                              int reg2 = right->Process(str);
                              RegIndex++;
                              return RegIndex;
                        }
                        
            case '=':
                        {
                              int reg1 = left->Process(str);
                              out<<" = ";
                              int reg2 = right->Process(str);
                              RegIndex++;
                              return RegIndex;
                        }     
            case EQ:
                        {
                              int reg1 = left->Process(str);
                              out<<" == ";
                              int reg2 = right->Process(str);
                              RegIndex++;
                              return RegIndex;
                        }     

            case NEQ:
                        {
                              int reg1 = left->Process(str);
                              out<<" != ";
                              int reg2 = right->Process(str);
                              RegIndex++;
                              return RegIndex;
                        }     

            case GEQ:
                        {
                              int reg1 = left->Process(str);
                              out<<" >= ";
                              int reg2 = right->Process(str);
                              RegIndex++;
                              return RegIndex;
                        }     

            case LEQ:
                        {
                              int reg1 = left->Process(str);
                              out<<" <= ";
                              int reg2 = right->Process(str);
                              RegIndex++;
                              return RegIndex;
                        }     
                        return 0;
      }
      
      yyerror("Syntax/Semantic Error");
}

int BlockNode::Process(std::string str)
{
      if( size == 0 ) return 0;
      out<<"\n"<<str<<"{\n";
      for(int i = 0;i<size;++i)
      {
            out<<str;
            Array[i]->Process(str+"\t");
            out<<";\n";
            RegIndex = 0;
      }     
      out<<str<<"}\n";
      return 0;
}

Node *Create(Node *left,Node *right,int operation)
{
      return new OperationNode(operation,left,right);
}

Node *Create(int value,int type)
{
      switch(type)
      {
            case INTEGER:
                        return new ConstantNode(value);                        
      }
      assert(0);
      return 0;
}

Node *Create(const char *sym)
{
      //printf("\nCreate:%s\n",sym);
      return new SymbolNode(sym);
}
