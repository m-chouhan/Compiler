
typedef enum  { Symbol,Constant,Operation,Block } NodeType;

typedef struct Node Node;

typedef struct ConstantNode
            {
                  int value;
                  int Process();
                  //~ ConstantNode(int v)
                  //~ { value = v;}
            }ConstantNode;      

typedef struct SymbolNode
            {
                  char Index;
                  //~ SymbolNode( char i )
                  //~ { Index = i;}
                  int Process();
            }SymbolNode;
                  
typedef struct OperationNode 
            {
                  int operation;
                  int Process();
                  //~ OperationNode(int opr,Node *l,Node *r) 
                  //~ { 
                        //~ operation = opr;
                        //~ left = l;right = r;
                  //~ }    
                  Node *left,*right;
            }OperationNode;      

typedef struct BlockNode
            {
                  int size;
                  int Process();
                  Node *Array[100];
                  void Add(Node *n)
                  {
                        Array[size++] = n;
                  }
            }BlockNode;


struct Node
            {
                  NodeType type;
                  Node *left,*right;
                  Node(NodeType t)  { type = t;}
                  union
                  {
                        ConstantNode cN;
                        SymbolNode    sN;
                        OperationNode oN;
                        BlockNode bN;
                  }Val;
                  int Process()
                  {
                        switch(type)
                        {
                                    case Symbol:
                                                return Val.sN.Process();
                                    case Constant:
                                                return Val.cN.Process();
                                    case Operation:
                                                return Val.oN.Process();
                                    case Block: 
                                                return Val.bN.Process();
                        }
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
                  void Push()
                  {
                        size++;
                  }
                  Node* Pop()
                  {
                        return B[size--];
                  }
                  
            }St;

extern int symbolTable[50];
