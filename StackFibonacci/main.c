#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_STACK_SIZE 5
#define MAX_FIBON_SIZE 100

int stack[MAX_STACK_SIZE];
int top = -1;

bool StackEmpty();
bool StackFull();
void StackPush( int item );
int StackPop();

int main()
{
    int Fibonacci[MAX_FIBON_SIZE];
    int Ftotal, Count_F = 0;

    Fibonacci[0] = 0;   //F(0) = 0
    Fibonacci[1] = 1;   //F(1) = 1
    StackPush( Fibonacci[0] );
    StackPush( Fibonacci[1] );

    printf( "Number: " );
    scanf( "%d", &Ftotal );

    while( Count_F <= Ftotal )
    {
        Fibonacci[Count_F + 1] = StackPop();
        Fibonacci[Count_F] = StackPop();
        //F(n+2) = F(n+1) + F(n)
        Fibonacci[Count_F + 2] = Fibonacci[Count_F] + Fibonacci[Count_F + 1];
        StackPush( Fibonacci[Count_F + 1] );
        StackPush( Fibonacci[Count_F + 2] );
        Count_F++;
    }
    printf( "Fibonacci:\n" );
    for( Count_F = 0; Count_F <= Ftotal; Count_F++ )
    {
        printf( "F(%d)=%d \n", Count_F, Fibonacci[Count_F] );
    }
    return 0;
}

bool StackEmpty()
{
    if( top < 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool StackFull()
{
    if( top >= MAX_STACK_SIZE )
    {
        return true;
    }
    else
    {
        return false;
    }
}
void StackPush( int item )
{
    if( StackFull() )
    {
        printf( "Full.\n" );
    }
    else
    {
        stack[++top] = item;
    }
}
int StackPop()
{
    if( StackEmpty() )
    {
        printf( "Empty." );
        return -2;
    }
    else
    {
        return stack[top--];
    }
}
