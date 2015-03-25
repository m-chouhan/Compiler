
#include "NodeHeader2.h"
#include "y.tab.h"
#include <fstream>

std::ofstream out("Assembly.asm");
int RegIndex  = 0;
int LableIndex = 0;

int ConstantNode::Process()
{
      RegIndex++;
      out<<"Load  R"<<RegIndex<<" , "<<value<<";\n";
      return RegIndex;
}

int SymbolNode::Process()
{
      RegIndex++;
      out<<"Load  R"<<RegIndex<<" , "<<"symbolTable["<<(int)Index<<"];\n";
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
      for(int i = 0;i<size;++i)
      {
            sT.Process();
            Array[i]->Process();
            RegIndex = 0;
      }      
}

Node *Create(Node *left,Node *right,int operation)
{
      return new OperationNode(operation,left,right);
}

Node *Create(int value,int type)
{
      Node *ptr = 0;
      switch(type)
      {
            case ALPHA:
                        ptr = new SymbolNode(value);
                        break;
            case INTEGER:
                        ptr = new ConstantNode(value);
                        break;
      }
      return ptr;
}

Node *Create(char *sym)
{
}
