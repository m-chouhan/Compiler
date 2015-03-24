
typedef enum  { Symbol,Constant,Operation,Block } NodeType;

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
                  { value = v;}
            };      

class SymbolNode: public Node
            {
                  public:
                  char Index;
                  SymbolNode( char i )
                  { Index = i;}
                  int Process();
            };
                  
class OperationNode:public Node 
            {
                  public:
                  int operation;
                  int Process();
                  OperationNode(int opr,Node *l,Node *r) 
                  { 
                        operation = opr;
                        left = l;right = r;
                  }    
            };      

class BlockNode:public Node
            {
                  public:
                  int size;
                  BlockNode() { size = 0;}
                  int Process();
                  Node *Array[100];
                  void Add(Node *n)
                  {
                        Array[size++] = n;
                  }
            };
            
Node *Create(Node *left,Node *right,int operation);
Node *Create(int value);

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
                  Node* Pop()
                  {
                        size--;
                        return B[size];
                  }  
                  void Add(Node *n)
                  {
                        B[size-1]->Add(n);
                  }                
            };

extern int symbolTable[50];
