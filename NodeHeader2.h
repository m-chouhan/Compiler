 
#include <stdio.h>      
#include <map>
#include <algorithm>
#include <string>

extern void yyerror(const char *);

typedef enum  { Symbol,Constant,Operation,Block } NodeType;
typedef std::map<std::string,int> Str_to_Int;

class SymbolTable
      {
            public:
            Str_to_Int Table;
            int index;
            SymbolTable() :index(1) {}
            void AddSymbol( const char *ptr )
            {
                  if( Table.count(ptr) == 0 )  //Symbol doesnot exist
                        Table[ptr] = index++;
                  else yyerror("Multiple declaration ");
            }
            int FindSymbol( char *ptr )
            {
                  return Table.count(ptr);
            }
            int size()
            {
                  return Table.size();
            }
            void Push();
            void Pop();
            
      };

class Node
{
            public:
            NodeType type;
            Node *left,*right;
            virtual int Process() =0;
};

class ConstantNode: public Node
            {                              
                  public:
                  int value;
                  int Process();
                  ConstantNode(int v)
                  { 
                        type = Constant;
                        left = right = 0;
                        value = v;
                  }
            };      

class SymbolNode: public Node
            {
                  public:
                  std::string symbol;
                  int pos;
                  SymbolNode( const char *i,int p ) :symbol(i),pos(p)
                  { 
                        type = Symbol;
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
                  void Add(Node *n)
                  {
                        Array[size++] = n;
                  }
            };
            
Node *Create(Node *left,Node *right,int operation);
Node *Create(int value,int type);
Node *Create(const char *sym,int pos);

struct Stack
            {
                  public:
                  BlockNode *B[100];
                  int size;
                  Stack() { size = 0;}
                  void Push()
                  {
                        B[size++] = new BlockNode();
                  }
                  BlockNode* Pop()
                  {
                        size--;
                        return B[size];
                  }  
                  void Add(Node *n)
                  {
                        B[size-1]->Add(n);
                  }                
                  void AddSymbol(char *sym)
                  {
                        //printf("\nAddSym:%s\n",sym);
                        B[size-1]->sT.AddSymbol(sym);
                  }
                  int FindSymbol(char *sym)
                  {
                        for(int i = size -1;i>=0;--i)
                        {
                              int index = B[i]->sT.FindSymbol(sym);
                              if( index == 1 ) return size - i -1; //return id of stack from top 
                        }
                        std::string str("Undeclared variable:");
                        str += sym;
                        yyerror(str.c_str());
                  }
            };

extern int symbolTable[50];
