 
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
                  std::string str(ptr);
                  if( Table.count(str) == 0 )  //Symbol doesnot exist
                        Table[str] = index++;
                  else
                  {
                        str = "Multiple Declaration of symbol "+str;
                        //~ yyerror(str.c_str());
                  }
            }
            int FindSymbol( char *ptr )
            {
                  if(Table.count(ptr))
                        return Table[ptr];
                  return -1;
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
                  SymbolNode( const char *i) :symbol(i)
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
Node *Create(const char *sym);

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
                  void Add(Node *n)
                  {
                        B[size-1]->Add(n);
                  }                
                  void AddSymbol(char *sym)
                  {
                        B[size-1]->sT.AddSymbol(sym);
                  }
                  int FindSymbol(char *sym)
                  {
                        int offset = 0;
                        for(int i = size -1;i>=0;--i)
                        {
                              int index = B[i]->sT.FindSymbol(sym);
                              if( index == -1 )  offset += B[i]->sT.size(); //return id of stack from top
                              else return offset+index; 
                        }
                        std::string str("Undeclared variable:");
                        str += sym;
                        //~ yyerror(str.c_str());
                  }
            };
