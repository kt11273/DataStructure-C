# include <stdio.h>
# include <stdlib.h>
# define MAX_NAME 25 //name 的最大字數
//node
typedef struct node
{
   void *data;
   struct node *next;
} node;
//將所有要輸入的元素組成 struct: element
typedef struct element
{
    char name[ MAX_NAME ];
    int score;
}element;
//queue 的頭、尾指標
typedef struct queue
{
    node *front, *rear;
}queue;

void Add_Q( queue *q, void *e  );   //Insert node
void Del_Q( queue *q );             //Delete node
void print_Q( node *q );            //Print queue

int main()
{
    queue *HW_Q;
    HW_Q = (queue *)malloc( sizeof( queue ) );
    HW_Q->front = NULL;
    HW_Q->rear = NULL;
    char option;

    printf( "Generic Queue in linking list: (Name & score)\n"
            "  A/a Insert node.\n"
            "  R/r Remove node.\n"
            "  P/p Print the list\n"
            "  Q   Exit the program.\n");
    scanf( " %c", &option );
    while( option != 'Q' )
    {
        element *HW_E;
        switch( option )
        {
        case 'A':
        case 'a':
            HW_E = (element *)malloc( sizeof( element ) );
            scanf( "%s", &HW_E->name );
            scanf( "%d", &HW_E->score );
            Add_Q( HW_Q, HW_E );
            break;
        case 'R':
        case 'r':
            Del_Q( HW_Q );
            break;
        case 'P':
        case 'p':
            print_Q( HW_Q->front );
            break;
        default :
            printf( "NO OPTIONS\n" );
            break;
        }
        scanf( " %c", &option );
    }
    free( HW_Q );
    return 0;
}

void Add_Q( queue *q, void *e )
{
    node *new_node =(node *)malloc( sizeof(node) );
    new_node->data = e;
    new_node->next = NULL;
    if( q->front == NULL )
    {
        q->front = new_node;
    }
    else
    {
        q->rear->next = new_node;
    }
    q->rear = new_node;
}
void Del_Q( queue *q )
{
    node *temp = (node *)malloc( sizeof(node) );
    if( q->front == NULL )
    {
        q->rear = NULL;
    }
    else
    {
        temp = q->front;
        q->front = q->front->next;
        free( temp );
    }
}
void print_Q( node *f )
{
    queue *q_temp = (queue *)malloc( sizeof(queue) );
    q_temp->front = f;
    if( q_temp->front == NULL )
    {
        printf( "Queue is empty.\n" );
    }
    else
    {
        while( q_temp->front != NULL )
        {
            element e_temp = *(element*)q_temp->front->data;
            printf( "%s %d\n", e_temp.name, e_temp.score );
            q_temp->front = q_temp->front->next;
        }
        printf( "\n" );
    }
}
