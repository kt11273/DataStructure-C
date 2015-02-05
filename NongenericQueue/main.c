# include <stdio.h>
# include <stdlib.h>
# define MAX_NAME 25

typedef struct node
{
   int data;
   struct node *next;
} node;

typedef struct queue
{
    node *front, *rear;
}queue;

void menu_Q();
void Add_Q( queue *q, int value );
void Del_Q( queue *q );
void print_Q( queue *q );

int main()
{
    queue *HW_Q;
    HW_Q = (queue *)malloc( sizeof( queue ) );
    HW_Q->front = (node *)malloc( sizeof( node ) );
    HW_Q->rear = (node *)malloc( sizeof( node ) );
    HW_Q->front = NULL;
    HW_Q->rear = NULL;

    int score;
    char option;

    menu_Q();
    printf( "? " );
    scanf( " %c", &option );
    while( option != 'Q' )
    {
        switch( option )
        {
        case 'A':
        case 'a':
            printf( "ADD: " );
            scanf( "%d", &score );
            Add_Q( HW_Q, score );
            break;
        case 'R':
        case 'r':
            printf( "REMOVE.\n" );
            Del_Q( HW_Q );
            break;
        case 'P':
        case 'p':
            printf( "PRINT.\n" );
            print_Q( HW_Q );
            break;
        default :
            printf( "NO OPTIONS\n" );
            break;
        }
        printf( "? " );
        scanf( " %c", &option );
    }
    return 0;
}

void menu_Q()
{
   printf ( "Enter your choice:\n"
           "   A to add an item to the queue\n"
           "   R to remove an item from the queue\n"
           "   P to print th queue\n"
           "   Q to end\n" );
}

void Add_Q( queue *q, int value )
{
    node *new_node =(node *)malloc( sizeof(node) );
    if( new_node == NULL )
    {
        printf("No Memory available Error\n");
        exit(0);
    }
    new_node->data = value;
    new_node->next = NULL;
    if( q->front == NULL )//if queue is empty
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
    node *temp =(node *)malloc( sizeof(node) );
    if( q->front == NULL )//if queue is empty
    {
        printf( "The queue is empty." );
        exit(1);
    }
    else
    {
        temp->data = q->front->data;
        temp = q->front;
        q->front = q->front->next;
    }
    free( temp );
}

void print_Q( queue *q )
{
    // 依序印出節點內容
    if( q->front == NULL )
    {
        printf( "Queue is empty.\n" );
    }
    else
    {
        printf( "The queue is: " );
        while( q->front != NULL )
        {
            printf( "%d ", q->front->data );
            q->front = q->front->next;
        }
        printf("NULL\n");
    }
}
