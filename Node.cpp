
#include "NodeHeader2.h"
#include "y.tab.h"
#include <fstream>
#include <iostream>
#include <assert.h>

std::ofstream out("Assembly.asm");
int RegIndex  = 0;
int LableIndex = 0;

std::string StrType(int type)
{
      switch(type)
      {
            case DOUBLE:      
                              return " #Double# ";
            case INTEGER:   
                              return " #Integer# ";
            case BYTE:
                              return " #Byte# ";
      }
      return "undef";
}

void SymbolTable::Push()
{
	  if(Table.size())
	  out<<"push		RBP\n"	
		 <<"mov		RBP,RSP\n"
		 <<"sub		RSP,"<<Table.size()*8<<";	Allocating variables\n";	
}

void SymbolTable::Pop()
{
      //~ for(Str_to_Int::iterator it = Table.begin();it != Table.end();it++)
      //~ {
            //~ out<<"pop		rbx\n";//key
            //~ it->second;//value
      //~ }
      if(Table.size())
      out<<"add		RSP,"<<Table.size()*8<<";	Popping Variables\n"
		<<"pop		RBP\n";
}

bool IsSubtype(int t1,int t2)
{
      if( t1 == t2 ) return true;
      switch(t2)
      {
            case DOUBLE: 
                              return true;
            case INTEGER: 
                              return t1 != DOUBLE;
            case BYTE:
                              return false;
      }
      return false;
}

int TypeCheck(int t1,int t2)
{           
      if( IsSubtype(t1,t2) )
            return t2;
      else if( IsSubtype(t2,t1) ) 
            return t1;
      //~ throw warning
      yyerror("Incompatible data type");
      return OBJECT;
}

int ConstantNode::Process()
{
      RegIndex++;
      out<<"mov		rbx, "<<value<<"	;"<<StrType(Return_Type)<<"\n";
      return RegIndex;
}

int SymbolNode::Process()
{
      RegIndex++;
      out<<"mov		rbx, [RBP-"<<pos*8<<"]	;"<<StrType(Return_Type)<<"\n";
      return RegIndex;      
}

int OperationNode::Process()
{
      switch(operation)
      {
			case PRINT:
						{
							right->Process();
							out <<"mov 		rsi,rbx\n"
								<<"mov		rdi,format\n"
								<<"xor		rbx,rbx\n"
								<<"call		printf\n";
							return 0;	
						}
            case IF:
                        if( right->type == Block )
                        {
                              int reg = left->Process();
                              int L = ++LableIndex;
                              out<<"cmp		rbx,0\n"
								<<"jz ELSE"<<L<<"\n";
                              right->Process();
                              out<<"ELSE"<<L<<":\n";
                              return 0;
                        }
                        else  //right is an else block
                        {
                              assert(right->type == Operation);
                              int reg = left->Process();
                              int L1 = ++LableIndex;
                              //~ int L2 = ++LableIndex;
                              out<<"cmp		rbx,0\n"
								<<"jz ELSE"<<L1<<"\n";
                              right->left->Process();
                              out<<"jmp IF"<<L1<<"\n";
                              out<<"ELSE"<<L1<<":\n";                              
                              right->right->Process();
                              out<<"IF"<<L1<<": \n";
                              return 0;
                        }
            case WHILE:
                         {     
                              int L = ++LableIndex; 
                              out<<"LOOP"<<L<<": \n";
                              
                              int reg2 = left->Process();  //This is Expression
                              out<<"cmp		rbx,0\n"
								<<"jz EXIT_LOOP"<<L<<"\n";
							  int reg1 = right->Process(); //This is block
                              out<<"jmp LOOP"<<L<<"\n";
                              
                              out<<"EXIT_LOOP"<<L<<":\n";
                              return 0;
                        }
            case '+':
                        {
                              int reg1 = right->Process();
                              
                              out<<"push\t\trbx\n";
                              
                              int reg2 = left->Process();
                              
                              Return_Type = TypeCheck(left->Return_Type,right->Return_Type);                              
                              RegIndex++;
                              out<<"add		rbx,[RSP]	;\n";
                              out<<"add		RSP,8		; Popping Stack\n";
                              return RegIndex;
                        }
            case '-':
                        {
                              int reg1 = right->Process();
                              
                              out<<"push\t\trbx\n";
                              
                              int reg2 = left->Process();
                              
                              Return_Type = TypeCheck(left->Return_Type,right->Return_Type);                              
                              RegIndex++;
                              out<<"sub		rbx,[RSP]	;\n";
                              out<<"add		RSP,8		; Popping Stack\n";
                              return RegIndex;
                        }
            case '*':
                        {
                              int reg1 = right->Process();
                              int reg2 = left->Process();
                              Return_Type = TypeCheck(left->Return_Type,right->Return_Type);
                              RegIndex++;
                              out<<"MUL R"<<RegIndex<<StrType(Return_Type)
                                    <<" , R"<<reg1<<StrType(right->Return_Type)
                                    <<" , R"<<reg2<<StrType(left->Return_Type)<<" ;\n";
                              return RegIndex;
                        }
            case '/':
                        {
                              int reg1 = right->Process();
                              int reg2 = left->Process();
                              Return_Type = TypeCheck(left->Return_Type,right->Return_Type);
                              RegIndex++;
                              out<<"DIV R"<<RegIndex<<StrType(Return_Type)
                                    <<" , R"<<reg1<<StrType(right->Return_Type)
                                    <<" , R"<<reg2<<StrType(left->Return_Type)<<" ;\n";
                              return RegIndex;
                        }
            case '>':
                        {
                              int reg1 = right->Process();
                              int reg2 = left->Process();
                              Return_Type = BYTE;
                              RegIndex++;
                              out<<"CMP R"<<RegIndex<<StrType(Return_Type)
                                    <<" , R"<<reg1<<StrType(right->Return_Type)
                                    <<" , R"<<reg2<<StrType(left->Return_Type)<<" ;\n";
                              return RegIndex;
                        }
            case '<':
                        {
                              int reg1 = right->Process();
                              int reg2 = left->Process();
                              Return_Type = BYTE;
                              RegIndex++;
                              out<<"CMP R"<<RegIndex<<StrType(Return_Type)
                                    <<" , R"<<reg2<<StrType(left->Return_Type)
                                    <<" , R"<<reg1<<StrType(right->Return_Type)<<" ;\n";
                              return RegIndex;
                        }
            case LEQ:
                        {
                              int reg1 = right->Process();
                              int reg2 = left->Process();
                              Return_Type = BYTE;
                              RegIndex++;
                              out<<"CMP R"<<RegIndex<<StrType(Return_Type)
                                    <<" , R"<<reg1<<StrType(right->Return_Type)
                                    <<" , R"<<reg2<<StrType(left->Return_Type)<<" ;\n";
                              return RegIndex;
                        }
            case GEQ:
                        {
                              int reg1 = right->Process();
                              int reg2 = left->Process();
                              Return_Type = BYTE;
                              RegIndex++;
                              out<<"CMP R"<<RegIndex<<StrType(Return_Type)
                                    <<" , R"<<reg1<<StrType(right->Return_Type)
                                    <<" , R"<<reg2<<StrType(left->Return_Type)<<" ;\n";
                              return RegIndex;
                        }
                        
            case '=':
                        {
                              assert(left->type == Symbol);
                              SymbolNode *sN = dynamic_cast<SymbolNode *> (left);
                              int reg1 = right->Process();
                              if(! IsSubtype(right->Return_Type,left->Return_Type))
                              {
                                    std::string str  = "unable to cast  from" + StrType(right->Return_Type) + " to " + StrType(left->Return_Type);
                                    yywarning(str.c_str());
                              }
                              int p = sN->pos;
                              out<<"mov		[RBP-"<<p*8<<"],rbx;	"<<StrType(right->Return_Type)
                              <<" , ["<<sN->symbol<<" , "<<p<<","<<StrType(left->Return_Type)<<"] ;\n";
                              return reg1;                              
                        }     
            case EQ:
                        {
                              int reg1 = right->Process();
                              int reg2 = left->Process();
                              Return_Type = BYTE;
                              RegIndex++;
                              out<<"EQ "<<RegIndex<<StrType(Return_Type)
                                    <<" , R"<<reg1<<StrType(right->Return_Type)
                                    <<" , R"<<reg2<<StrType(left->Return_Type)<<" ;\n";
                              return RegIndex;
                        }
            case NEQ:
                        {
                              int reg1 = right->Process();
                              int reg2 = left->Process();
                              Return_Type = BYTE;
                              RegIndex++;
                              out<<"NEQ "<<RegIndex<<StrType(Return_Type)
                                    <<" , R"<<reg1<<StrType(right->Return_Type)
                                    <<" , R"<<reg2<<StrType(left->Return_Type)<<" ;\n";
                              return RegIndex;
                        }
      }
      
      yyerror("Syntax/Semantic Error");
}

int BlockNode::Process()
{
      if( size == 0 ) return 0;
      out<<"\n;Block\n";
      sT.Push();
      for(int i = 0;i<size;++i)
      {
            yylineno = LineNumber[i];
            Array[i]->Process();
            RegIndex = 0;
      }     
      sT.Pop(); 
      out<<"\n";
      return 0;
}

Node *Create(Node *left,Node *right,int operation)
{
      return new OperationNode(operation,left,right);
}

Node *Create(double value,int type)
{
      switch(type)
      {
            case INTEGER:
                        return new ConstantNode(value,type);
            case DOUBLE:
                        return new ConstantNode(value,type);
            case BYTE:
                        return new ConstantNode(value,type);
      }
      assert(0);
      return 0;
}

Node *Create(const char *sym,Tuple pos)
{
      //printf("\nCreate:%s\n",sym);
      return new SymbolNode(sym,pos);
}
