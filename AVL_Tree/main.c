#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int key;
}element;

typedef struct treeNode *treePointer;
typedef struct treeNode
{
    element data;
    int height;                 //Node hight
    treePointer leftChild;      //left subtree
    treePointer rightChild;     //right subtree
}treeNode;

//node
typedef struct Qnode
{
   void *data;
   struct Qnode *next;
} Qnode;

typedef struct queue
{
    int Qsize;
    Qnode *front, *rear;
}queue;

void menu();

int max(int a, int b);
int height( treePointer *Tnode );
int getBalance( treePointer *Tnode );

void R_Rotation( treePointer *parent );
void L_Rotation( treePointer *parent );

void avlInsert( treePointer *parent, element x, int* Rotation );
void avlDelet( treePointer *parent, element x, int* Rotation );
treePointer minValueNode( treePointer node );

//Level Order
void Add_Q( queue *q, void *e );
void * Del_Q( queue *q );
void LevelOrder( treePointer root );

int main()
{
    treePointer root =  NULL;
    element treeData;
    int* Rotation = (int*)malloc( sizeof(int) );
    *Rotation = 0;
    char options;

    menu();
    printf( "\n? " );
    scanf( " %c", &options );
    while( options != 'Q' )
    {
        switch( options )
        {
        case 'I':
        case 'i':
            scanf( "%d", &treeData.key );
            avlInsert( &root, treeData, Rotation );
            if( *Rotation == 1 )        //if rotated, print
            {
                LevelOrder( root );
                *Rotation = 0;
            }
            break;
        case 'D':
        case 'd':
            scanf( "%d", &treeData.key );
            avlDelet( &root, treeData, Rotation );
            if( *Rotation == 1 )        //if rotated, print
            {
                LevelOrder( root );
                *Rotation = 0;
            }
            break;
        case 'P':
        case 'p':
            LevelOrder( root );
            break;
        default:
            break;
        }
        printf( "? " );
        scanf( " %c", &options );
    }
    free( Rotation );
    return 0;
}
/*Menu*/
void menu()
{
    printf( "AVL Tree:\n"
            "I/i to insert an data to the AVL tree.\n"
            "D/d to delete an data from the AVL tree.\n"
            "P/p can print the AVL tree.\n"
            "Q/q can end the program.\n");
}
/*Prepare to caculate height*/
int max( int leftChild, int rightChild )
{
    return ( leftChild > rightChild ) ? leftChild : rightChild;
}
/*Return node height*/
int height( treePointer *Tnode )
{
    if( *Tnode == NULL )
    {
        return 0;
    }
    else
    {
        return (*Tnode)->height;
    }
}
/*Return balance factoey*/
int getBalance( treePointer *Tnode )
{
    if( *Tnode == NULL )
    {
        return 0;
    }
    else
    {
        return height( &(*Tnode)->leftChild ) - height( &(*Tnode)->rightChild );
    }
}
/*Right Rotation*/
void R_Rotation( treePointer *parent )
{
    treePointer Child;
    Child = (*parent)->leftChild;
    (*parent)->leftChild = Child->rightChild;
    Child->rightChild = *parent;
    (*parent)->height = max( height( &(*parent)->leftChild ), height( &(*parent)->rightChild ) ) + 1;
    (*parent) = Child;
}
/*Left Rotation*/
void L_Rotation( treePointer *parent )
{
    treePointer Child;
    Child = (*parent)->rightChild;
    (*parent)->rightChild = Child->leftChild;
    Child->leftChild = *parent;
    (*parent)->height = max( height( &(*parent)->leftChild ), height( &(*parent)->rightChild ) ) + 1;
    (*parent) = Child;
}
void avlInsert( treePointer *parent, element x, int* Rotation )
{
    int balance;
    /*If the tree is empty, and insert target to tree*/
    if( !*parent )
    {
        *parent = malloc( sizeof( treeNode ) );
        (*parent)->leftChild = (*parent)->rightChild = NULL;
        (*parent)->data = x;
        (*parent)->height = 1;       // The hight of node is 1
    }
    /*target < parent's data*/
    else if( x.key < (*parent)->data.key )
    {
        avlInsert( &(*parent)->leftChild, x, Rotation );
    }
    /*target > parent's data*/
    else if( x.key > (*parent)->data.key )
    {
        avlInsert( &(*parent)->rightChild, x, Rotation );
    }
    /*If target has been inserted*/
    else
    {
        printf( "%d has already been stored.\n\n", (*parent)->data.key );
    }

    /*Update the node hight, and get balance*/
    (*parent)->height = max( height( &(*parent)->leftChild ), height( &(*parent)->rightChild ) ) + 1;
    balance = getBalance( &(*parent) );

    /*Rotation*/
    if( balance > 1 && x.key < (*parent)->leftChild->data.key )            //LL
    {
        printf( "LL Adjustment\n" );
        R_Rotation( &(*parent) );
        *Rotation = 1;
    }
    else if( balance > 1 && x.key > (*parent)->leftChild->data.key )       //LR
    {
        printf( "LR Adjustment\n" );
        L_Rotation( &(*parent)->leftChild );
        R_Rotation( &(*parent) );
        *Rotation = 1;
    }
    if( balance < -1 && x.key > (*parent)->rightChild->data.key )          //RR
    {
        printf( "RR Adjustment\n" );
        L_Rotation( &(*parent) );
        *Rotation = 1;
    }
    else if( balance < -1 && x.key < (*parent)->rightChild->data.key )     //RL
    {
        printf( "RL Adjustment\n" );
        R_Rotation( &(*parent)->rightChild );
        L_Rotation( &(*parent) );
        *Rotation = 1;
    }
    (*parent)->height = max( height( &(*parent)->leftChild ), height( &(*parent)->rightChild ) ) + 1;   //Updata height again
}
void avlDelet( treePointer *parent, element x, int* Rotation )
{
    int balance;
    /*If target can not find*/
    if( !*parent )
    {
        printf( "The key can not find.\n\n" );
    }
    /*target < parent's data*/
    else if( x.key < (*parent)->data.key )
    {
        avlDelet( &(*parent)->leftChild, x, Rotation );
    }
    /*target > parent's data*/
    else if( x.key > (*parent)->data.key )
    {
        avlDelet( &(*parent)->rightChild, x, Rotation );
    }
    /*Delete target from tree*/
    else
    {
        /*Node with only one child or no child*/
        if( (*parent)->leftChild == NULL || (*parent)->rightChild == NULL )
        {
            (*parent) = (*parent)->leftChild ? (*parent)->leftChild : (*parent)->rightChild;
        }
        /*Node with two children, two child case*/
        else
        {
            treePointer temp = minValueNode( (*parent)->rightChild );
            (*parent)->data = temp->data;
            avlDelet( &(*parent)->rightChild, temp->data, Rotation );
        }
    }

    /*Update the node hight, and get balance*/
    if ( (*parent) != NULL ) {
        (*parent)->height = max( height( &(*parent)->leftChild ), height( &(*parent)->rightChild ) ) + 1;
        balance = getBalance( &(*parent) );
        /*Rotation*/
        if( balance > 1 && getBalance( &(*parent)->leftChild ) >= 0 )       //R0 R1
        {
            if( getBalance( &(*parent)->leftChild ) == 0 )
            {
                printf( "R0 Adjustment\n" );
            }
            else
            {
                printf( "R1 Adjustment\n" );
            }
            R_Rotation( &(*parent) );
            *Rotation = 1;
        }
        else if( balance > 1 && getBalance( &(*parent)->leftChild ) < 0 )        //R-1
        {
            printf( "R-1 Adjustment\n" );
            L_Rotation( &(*parent)->leftChild );
            R_Rotation( &(*parent) );
            *Rotation = 1;
        }
        if( balance < -1 && getBalance( &(*parent)->rightChild ) <= 0 )     //L0 L-1
        {
            if( getBalance( &(*parent)->rightChild ) == 0 )
            {
                printf( "L0 Adjustment\n" );
            }
            else
            {
                printf( "L-1 Adjustment\n" );
            }
            L_Rotation( &(*parent) );
            *Rotation = 1;
        }
        else if( balance < -1 && getBalance( &(*parent)->rightChild ) > 0 )      //L1
        {
            printf( "L1 Adjustment\n" );
            R_Rotation( &(*parent)->rightChild );
            L_Rotation( &(*parent) );
            *Rotation = 1;
        }
        (*parent)->height = max( height( &(*parent)->leftChild ), height( &(*parent)->rightChild ) ) + 1;   //Updata height again
    }
}
/*Find smallest target in the right subtree*/
treePointer minValueNode( treePointer node )
{
    treePointer minNode = node;
    /*Loop down to find the leftmost leaf*/
    while( minNode->leftChild != NULL )
    {
        minNode = minNode->leftChild;
    }
    return minNode;
}
void Add_Q( queue *q, void *e )
{
    Qnode *new_node = (Qnode *)malloc( sizeof(Qnode) ); //creat a new node
    new_node->data = e;                                 //add an element
    new_node->next = NULL;                              //next of the last node is null

    if( q->front == NULL )                              //if queue is empty
    {
        q->front = new_node;                            //The new node is first
    }
    else
    {
        q->rear->next = new_node;                       //Insert new node, The next node is new node
    }
    q->rear = new_node;                                 //Insert new node, The rear node is new node
    q->Qsize += 1;                                      //Add 1 to Qsize
}
void* Del_Q( queue *q )
{
    Qnode *temp;                                        //creat a temp node
    void *data = NULL;

    if( q->front == NULL )                              //if queue is empty
    {
        return NULL;
    }
    else
    {
        temp = q->front;                                //move the link of the target to temp node
        data=temp->data;
        q->front = q->front->next;
        free(temp);                                     //free temp node
        q->Qsize -= 1;                                  //Sub 1 from Qsize
    }
    return data;
}
void LevelOrder( treePointer root )
{
    queue *HW_Q = (queue *)malloc( sizeof( queue ) );   //creat queue
    HW_Q->front = NULL;                                 //creat queue
    HW_Q->rear = NULL;                                  //creat queue
    HW_Q->Qsize = 0;
    int count;                                          //make tree newline

    if( root == NULL ) return;
    Add_Q( HW_Q, root );
    count = HW_Q->Qsize;
    for( ;; )
    {
        treePointer Qtemp = (treePointer)Del_Q( HW_Q );
        count -= 1;
        if( Qtemp != NULL )
        {
            printf( "%d", Qtemp->data.key );
            if( Qtemp->leftChild != NULL )
            {
                Add_Q( HW_Q, Qtemp->leftChild );
            }
            if( Qtemp->rightChild != NULL )
            {
                Add_Q( HW_Q, Qtemp->rightChild );
            }
            if( count == 0 )
            {
                puts( "" );
                count = HW_Q->Qsize;
            }
            else
            {
                printf( " " );
            }
        }
        else break;
    }
    //puts( "" );
}
