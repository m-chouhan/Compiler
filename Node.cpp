
#include "NodeHeader2.h"
#include "y.tab.h"
#include <fstream>
#include <assert.h>

std::ofstream out("Assembly.asm");
int RegIndex  = 0;
int LableIndex = 0;

void SymbolTable::Push()
{
      for(Str_to_Int::iterator it = Table.begin();it != Table.end();it++)
      {
            out<<"Push "<<it->first<<"\n";//key
            it->second;//value
      }
}

void SymbolTable::Pop()
{
      for(Str_to_Int::iterator it = Table.begin();it != Table.end();it++)
      {
            out<<"Pop "<<it->first<<"\n";//key
            it->second;//value
      }
}


int ConstantNode::Process()
{
      RegIndex++;
      out<<"Load  R"<<RegIndex<<" , "<<value<<";\n";
      return RegIndex;
}

int SymbolNode::Process()
{
      RegIndex++;
      out<<"Load  R"<<RegIndex<<" , "<<"mem["<<symbol<<","<<pos<<"];\n";
      return RegIndex;      
}

int OperationNode::Process()
{
      switch(operation)
      {
            case IF:
                        if( right->type == Block )
                        {
                              int reg = left->Process();
                              int L = ++LableIndex;
                              out<<"BEQZ R"<<reg<<" , "<<"ELSE"<<L<<"\n";
                              right->Process();
                              out<<"ELSE"<<L<<":\n";
                              return 0;
                        }
                        else  //right is an else block
                        {
                              assert(right->type == Operation);
                              int reg = left->Process();
                              int L1 = ++LableIndex;
                              int L2 = ++LableIndex;
                              
                              out<<"BEQZ R"<<reg<<" , "<<"ELSE"<<L1<<"\n";
                              right->left->Process();
                              out<<"JUMP IF"<<L2<<"\n";
                              out<<"ELSE"<<L1<<":\n";                              
                              right->right->Process();
                              out<<"IF"<<L2<<": \n";
                              return 0;
                        }
            //~ case ELSE:
                        //~ break;
            case WHILE:
                         {     
                              int L = ++LableIndex; 
                              out<<"LOOP"<<L<<": \n";
                              int reg1 = right->Process(); //This is block
                              int reg2 = left->Process();  //This is Expression
                              out<<"BEQZ R"<<reg2<<" , "<<"LOOP"<<L<<"\n";
                              return 0;
                        }
            case '+':
                        {
                              int reg1 = right->Process();
                              int reg2 = left->Process();
                              RegIndex++;
                              out<<"ADD R"<<RegIndex<<" , R"<<reg1<<" , R"<<reg2<<" ;\n";
                              return RegIndex;
                        }
                        
            case '=':
                        {
                              assert(left->type == Symbol);
                              SymbolNode *sN = dynamic_cast<SymbolNode *> (left);
                              int reg1 = right->Process();
                              int p = sN->pos;
                              out<<"STORE R"<<reg1<<" , mem["<<sN->symbol<<" , "<<p<<"] ;\n";
                              return reg1;                              
                        }     
      }
      yyerror("Syntax/Semantic Error");
}

int BlockNode::Process()
{
      if( size == 0 ) return 0;
      out<<"\n#Block\n";
      sT.Push();
      for(int i = 0;i<size;++i)
      {
            Array[i]->Process();
            RegIndex = 0;
      }     
      sT.Pop(); 
      out<<"#\n";
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

Node *Create(const char *sym,int pos)
{
      //printf("\nCreate:%s\n",sym);
      return new SymbolNode(sym,pos);
}
