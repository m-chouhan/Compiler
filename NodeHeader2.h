
typedef enum  { Symbol,Constant,Operation,Block } NodeType;

class Node
{
            NodeType type;
            Node *left,*right;
            virtual int Process() =0;
};

class ConstantNode: public Node
            {
                  int value;
                  int Process();
                  //~ ConstantNode(int v)
                  //~ { value = v;}
            };      

class SymbolNode: public Node
            {
                  char Index;
                  //~ SymbolNode( char i )
                  //~ { Index = i;}
                  int Process();
            };
                  
class OperationNode:public Node 
            {
                  int operation;
                  int Process();
                  //~ OperationNode(int opr,Node *l,Node *r) 
                  //~ { 
                        //~ operation = opr;
                        //~ left = l;right = r;
                  //~ }    
                  //~ Node *left,*right;
            };      

class BlockNode:public Node
            {
                  int size;
                  int Process();
                  Node *Array[100];
                  void Add(Node *n)
                  {
                        Array[size++] = n;
                  }
            };
            
Node *Create(Node *left,Node *right,int operation);
Node *Create(int value);
/*
int ProcessNode(Node *node);
int ProcessConstantNode(ConstantNode *cn);
int ProcessSymbolNode(SymbolNode *sn);
int ProcessOperationNode(OperationNode *on);
int ProcessBlockNode(BlockNode *bn);
*/
struct Stack
            {
                  
                  Node *B[100];
                  int size;
                  //~ void Push()
                  //~ {
                        //~ size++;
                  //~ }
                  //~ Node* Pop()
                  //~ {
                        //~ return B[size--];
                  //~ }
                  
            }St;

extern int symbolTable[50];
