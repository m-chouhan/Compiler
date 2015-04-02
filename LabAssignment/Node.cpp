
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

void SymbolTable::Pop()
{
      for(Str_to_Int::iterator it = Table.begin();it != Table.end();it++)
      {
            //out<<"Pop "<<it->first<<"\n";//key
            it->second;//value
      }
}


int ConstantNode::Process()
{
      RegIndex++;
      out<<" "<<value<<" ";
      return RegIndex;
}

int SymbolNode::Process()
{
      RegIndex++;
      out<<" "<<symbol<<" ";
      return RegIndex;      
}

int OperationNode::Process()
{
      switch(operation)
      {
            case IF:
                        if( right->type == Block )
                        {
                              out<<"\nif (";
                              int reg = left->Process();
                              out<<" ) \n";
                              right->Process();
                              return 0;
                        }
                        else  //right is an else block
                        {
                              assert(right->type == Operation);
                              out<<" \nif ( ";
                              int reg = left->Process();
                              out<<" ) \n";
                              right->left->Process();
                              out<<"\nelse \n";                              
                              right->right->Process();
                              return 0;
                        }
            case WHILE:
                         {     
                              int L = ++LableIndex; 
                              out<<"\nwhile ( ";
                              int reg2 = left->Process();  //This is Expression
                              out<<")";
                              int reg1 = right->Process(); //This is block
                              return 0;
                        }
            case READ:
                        {
                              out<<"\nscanf(\"%d\", &";right->Process();
                              out<<")";
                              //~ assert(0);
                              return 0;
                        }
            case '+':
                        {
                              int reg1 = left->Process();
                              out<<" + ";
                              int reg2 = right->Process();
                              RegIndex++;
                              return RegIndex;
                        }
            case '-':
                        {
                              int reg1 = left->Process();
                              out<<" - ";
                              int reg2 = right->Process();
                              RegIndex++;
                              return RegIndex;
                        }
            case '*':
                        {
                              int reg1 = left->Process();
                              out<<" * ";
                              int reg2 = right->Process();
                              RegIndex++;
                              return RegIndex;
                        }
            case '/':
                        {
                              int reg1 = left->Process();
                              out<<" / ";
                              int reg2 = right->Process();
                              RegIndex++;
                              return RegIndex;
                        }
                        
            case '=':
                        {
                              int reg1 = left->Process();
                              out<<" = ";
                              int reg2 = right->Process();
                              RegIndex++;
                              return RegIndex;
                        }     
            case EQ:
                        {
                              int reg1 = left->Process();
                              out<<" == ";
                              int reg2 = right->Process();
                              RegIndex++;
                              return RegIndex;
                        }     

            case NEQ:
                        {
                              int reg1 = left->Process();
                              out<<" != ";
                              int reg2 = right->Process();
                              RegIndex++;
                              return RegIndex;
                        }     

            case GEQ:
                        {
                              int reg1 = left->Process();
                              out<<" >= ";
                              int reg2 = right->Process();
                              RegIndex++;
                              return RegIndex;
                        }     

            case LEQ:
                        {
                              int reg1 = left->Process();
                              out<<" <= ";
                              int reg2 = right->Process();
                              RegIndex++;
                              return RegIndex;
                        }     
                        return 0;
      }
      
      yyerror("Syntax/Semantic Error");
}

int BlockNode::Process()
{
      if( size == 0 ) return 0;
      out<<"\n//~Block\n{\n";
      sT.Push();
      for(int i = 0;i<size;++i)
      {
            Array[i]->Process();
            out<<";\n";
            RegIndex = 0;
      }     
      sT.Pop(); 
      out<<"}\n";
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
