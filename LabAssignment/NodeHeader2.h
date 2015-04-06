 
#include <stdio.h>      
#include <map>
#include <algorithm>
#include <string>
#include <fstream>

extern std::ofstream out;
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
            }
            void Push();
      };

class Node
{
            public:
            NodeType type;
            Node *left,*right;
            virtual int Process(std::string str) =0;
};

class ConstantNode: public Node
            {                              
                  public:
                  int value;
                  int Process(std::string str);
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
                  int Process(std::string str);
            };
                  
class OperationNode:public Node 
            {
                  public:
                  int operation;
                  int Process(std::string str);
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
                  BlockNode() 
                  {
                        type = Block;
                        left = right = 0;
                        size = 0;
                  }
                  int Process(std::string str);
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
                  SymbolTable sT;
                  void Process()
                  {
                        out<<"#include <stdio.h>\n\n"
                              <<" void main() \n{\n";
                        sT.Push();
                        B[0]->Process("\t");
                        out<<"\n}";
                  }
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
                        sT.AddSymbol(sym);
                  }
            };
