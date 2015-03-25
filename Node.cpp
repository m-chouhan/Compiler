
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
      for(int i = 0;i<Table.size();++i)
            out<<"Pop\n";
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
      out<<"Load  R"<<RegIndex<<" , "<<"search["<<symbol<<"];\n";
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
                              out<<"BEQZ R"<<reg<<" , "<<"Lable"<<L<<"\n";
                              right->Process();
                              out<<"Lable"<<L<<":\n";
                              break;
                        }
                        else  //right is an else block
                        {
                              int reg = left->Process();
                              int L1 = ++LableIndex;
                              int L2 = ++LableIndex;
                              
                              out<<"BEQZ R"<<reg<<" , "<<"Lable"<<L1<<"\n";
                              right->left->Process();
                              out<<"JUMP Lable"<<L2<<"\n";
                              out<<"Lable"<<L1<<":\n";                              
                              right->right->Process();
                              out<<"Lable"<<L2<<": \n";
                        }
                        break;
            //~ case ELSE:
                        //~ break;
            case WHILE:
                         {     
                              int L = ++LableIndex; 
                              out<<"LOOP"<<L<<": \n";
                              int reg1 = right->Process(); //This is block
                              int reg2 = left->Process();  //This is Expression
                              out<<"BEQZ R"<<reg2<<" , "<<"LOOP"<<L<<"\n";
                              break;
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
                              return 0;
                        break;
      }
}

int BlockNode::Process()
{
      out<<"\n#Block\n";
      sT.Push();
      for(int i = 0;i<size;++i)
      {
            Array[i]->Process();
            RegIndex = 0;
      }     
      sT.Pop(); 
      out<<"#\n";
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

Node *Create(char *sym)
{
      printf("\nCreate:%s\n",sym);
      return new SymbolNode(sym);
}
