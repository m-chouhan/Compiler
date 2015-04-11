 
#include <stdio.h>      
#include <map>
#include <utility>
#include <algorithm>
#include <string>
#include <fstream>

extern void yyerror(const char *);
extern void yywarning(const char *);
extern int yylineno;
extern std::ofstream out;

typedef enum  { Symbol,Constant,Operation,Block } NodeType;
typedef std::pair<int,int> Tuple;
typedef std::map<std::string, Tuple > Str_to_Int;

class SymbolTable
      {
            public:
            Str_to_Int Table;
            int index;
            SymbolTable() :index(1) {}
            void AddSymbol(std::string str,int type )
            {
                  if( Table.count(str) == 0 )  //Symbol doesnot exist
                        Table[str] = Tuple(index++,type);
                  else
                  {
                        str = "Multiple Declaration of symbol "+str;
                        yyerror(str.c_str());
                  }
            }
            Tuple FindSymbol( char *ptr )
            {
                  if(Table.count(ptr))
                        return Table[ptr];
                  return Tuple(-1,0);
            }
            int size()
            {
                  return Table.size();
            }
            void Push();
            void Pop();
      };

int TypeCheck(int t1,int t2);

class Node
{
            public:
            NodeType type;
            int Return_Type;
            Node *left,*right;
            virtual int Process() =0;
};

class ConstantNode: public Node
            {                              
                  public:
                  double value;
                  int Process();
                  ConstantNode(double v,int Rtype)
                  { 
                        type = Constant;
                        left = right = 0;
                        value = v;
                        Return_Type = Rtype;
                  }
            };      

class SymbolNode: public Node
            {
                  public:
                  std::string symbol;
                  int pos;
                  SymbolNode( const char *i,Tuple p ) :symbol(i),pos(p.first)
                  { 
                        type = Symbol;
                        Return_Type = p.second;
                        left = right = 0;
                  }
                  int Process();
            };
                  
class OperationNode:public Node 
            {
                  public:
                  int operation;
                  int Process();
                  OperationNode(int opr,Node *l,Node *r) 
                  { 
                        type = Operation;
                        operation = opr;
                        left = l;right = r;
                  }    
            };      

class BlockNode:public Node
            {
                  public:
                  int size;
                  SymbolTable sT;
                  BlockNode() 
                  {
                        type = Block;
                        left = right = 0;
                        size = 0;
                  }
                  int Process();
                  Node *Array[100];
                  int LineNumber[100];
                  void Add(Node *n,int lineno)
                  {
                        LineNumber[size] = lineno;
                        Array[size++] = n;
                  }
            };
            
Node *Create(Node *left,Node *right,int operation);
Node *Create(double value,int type);
Node *Create(const char *sym,Tuple pos);

struct Stack
            {
                  public:
                  BlockNode *B[100];
                  int size;
                  Stack() 
                  { 
                        size = 0;
                        B[size++] = new BlockNode();                        
                  }
                  void Push()
                  {
                        B[size++] = new BlockNode();
                  }
                  BlockNode* Pop()
                  {
                        size--;
                        return B[size];
                  }  
                  void Add(Node *n,int lineno)
                  {
                        B[size-1]->Add(n,lineno);
                  }                
                  void AddSymbols(int type,Node *list)
                  {
                        if( list == NULL) return;
                        if( list->type == Symbol )
                        {
                              SymbolNode *sn = dynamic_cast<SymbolNode *>( list);
                              B[size-1]->sT.AddSymbol(sn->symbol,type);
                              return;
                        }
                        AddSymbols(type,list->left);
                        AddSymbols(type,list->right);
                  }
				  void Process()
				  {
						out<<"        global  main\n"
						   <<"\textern  printf\n"
						   <<"        section .text\n"
						   <<"main:\npush rbx\n";
						B[0]->Process();
						out<<"pop rbx\nret\n"
						   <<"format:\n"
						   <<"        db \"%d\", 10 , 0\n";
						
				  }
                  Tuple FindSymbol(char *sym)
                  {
                        int offset = 0;
                        for(int i = size -1;i>=0;--i)
                        {
                              Tuple index = B[i]->sT.FindSymbol(sym);
                              if( index.first == -1 )  continue;
                              return Tuple(index.first,size - 1 - i); 
                        }
                        std::string str("Undeclared variable:");
                        str += sym;
                        yyerror(str.c_str());
                  }
            };
