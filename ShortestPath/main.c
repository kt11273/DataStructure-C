#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAX 5

typedef struct STACK_HANOI
{
    int *TOWER;
    int TOP;
    int capacity;
}STACK_HANOI;

bool stack_Empty( STACK_HANOI *Tower );
bool stack_Full( STACK_HANOI *Tower );
int stack_Push( STACK_HANOI *Tower, int disk );
int stack_Pop( STACK_HANOI *Tower );

int main()
{
    int disk_num, counter;
    STACK_HANOI Tower_A ;
    STACK_HANOI Tower_B ;
    STACK_HANOI Tower_C ;
    Tower_A.capacity = MAX;
    Tower_B.capacity = MAX;
    Tower_C.capacity = MAX;
    Tower_A.TOWER = (int*)malloc( ( Tower_A.capacity ) * sizeof( int ) );
    Tower_B.TOWER = (int*)malloc( ( Tower_B.capacity ) * sizeof( int ) );
    Tower_C.TOWER = (int*)malloc( ( Tower_C.capacity ) * sizeof( int ) );

    Tower_A.TOP = 0;
    Tower_B.TOP = 0;
    Tower_C.TOP = 0;

    scanf( "%d", &disk_num );
    counter = disk_num;

    while( counter-- )
    {
        stack_Push( &Tower_A, counter + 1 );
    }

    if( disk_num % 2 == 1 )
    {
        for( counter = 1; counter <= ( (int)pow( 2, disk_num ) - 1 ); counter = counter + 1 )
        {

            if( counter % 3 == 1 )
            {

                if( Tower_A.TOWER[ Tower_A.TOP ] < Tower_C.TOWER[ Tower_C.TOP ] || stack_Empty( &Tower_C ) )
                {
                    stack_Push( &Tower_C, stack_Pop( &Tower_A ) );
                    printf( "Move disk %d from A to C\n", Tower_C.TOWER[ Tower_C.TOP ] );
                }
                else
                {
                    stack_Push( &Tower_A, stack_Pop( &Tower_C ) );
                    printf( "Move disk %d from C to A\n", Tower_A.TOWER[ Tower_A.TOP ] );
                }
            }
            else if( counter % 3 == 2 )
            {

               if( Tower_A.TOWER[ Tower_A.TOP ] < Tower_B.TOWER[ Tower_B.TOP ] || stack_Empty( &Tower_B ) )
                {
                    stack_Push( &Tower_B, stack_Pop( &Tower_A ) );
                    printf( "Move disk %d from A to B\n", Tower_B.TOWER[ Tower_B.TOP ] );
                }
                else
                {
                    stack_Push( &Tower_A, stack_Pop( &Tower_B ) );
                    printf( "Move disk %d from B to A\n", Tower_A.TOWER[ Tower_A.TOP ] );
                }
            }
            else
            {

                if( Tower_B.TOWER[ Tower_B.TOP ] < Tower_C.TOWER[ Tower_C.TOP ] || stack_Empty( &Tower_C ) )
                {
                    stack_Push( &Tower_C, stack_Pop( &Tower_B ) );
                    printf( "Move disk %d from B to C\n", Tower_C.TOWER[ Tower_C.TOP ] );
                }
                else
                {
                    stack_Push( &Tower_B, stack_Pop( &Tower_C ) );
                    printf( "Move disk %d from C to B\n", Tower_B.TOWER[ Tower_B.TOP ] );
                }
            }
        }
    }
    else
    {
        for( counter = 1; counter <= ( pow( 2, disk_num ) - 1 ); counter = counter + 1 )
        {
            if( counter % 3 == 1 )
            {
                if( Tower_A.TOWER[ Tower_A.TOP ] < Tower_B.TOWER[ Tower_B.TOP ] || stack_Empty( &Tower_B ) )
                {
                    stack_Push( &Tower_B, stack_Pop( &Tower_A ) );
                    printf( "Move disk %d from A to B\n", Tower_B.TOWER[ Tower_B.TOP ] );
                }
                else
                {
                    stack_Push( &Tower_A, stack_Pop( &Tower_B ) );
                    printf( "Move disk %d from B to A\n", Tower_A.TOWER[ Tower_A.TOP ] );
                }
            }
            else if( counter % 3 == 2 )
            {
                if( Tower_A.TOWER[ Tower_A.TOP ] < Tower_C.TOWER[ Tower_C.TOP ] || stack_Empty( &Tower_C ) )
                {
                    stack_Push( &Tower_C, stack_Pop( &Tower_A ) );
                    printf( "Move disk %d from A to C\n", Tower_C.TOWER[ Tower_C.TOP ] );
                }
                else
                {
                    stack_Push( &Tower_A, stack_Pop( &Tower_C ) );
                    printf( "Move disk %d from C to A\n", Tower_A.TOWER[ Tower_A.TOP ] );
                }
            }
            else
            {
                if( Tower_B.TOWER[ Tower_B.TOP ] < Tower_C.TOWER[ Tower_C.TOP ] || stack_Empty( &Tower_C ) )
                {
                    stack_Push( &Tower_C, stack_Pop( &Tower_B ) );
                    printf( "Move disk %d from B to C\n", Tower_C.TOWER[ Tower_C.TOP ] );
                }
                else
                {
                    stack_Push( &Tower_B, stack_Pop( &Tower_C ) );
                    printf( "Move disk %d from C to B\n", Tower_B.TOWER[ Tower_B.TOP ] );
                }
            }
        }
    }
}

bool stack_Empty( STACK_HANOI *Tower )
{
    if( Tower->TOP == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool stack_Full( STACK_HANOI *Tower )
{
    if( Tower->TOP >= ( Tower->capacity ) - 1 )
    {
        return true;
    }
    else
    {
        return false;
    }
}
int stack_Push( STACK_HANOI *Tower, int disk )
{
    if( stack_Full( Tower ) )
    {
        Tower->TOWER = ( int* )realloc( Tower->TOWER, ( Tower->capacity *= 2 )* sizeof( int ) );
        Tower->TOP = Tower->TOP + 1;
        return Tower->TOWER[ Tower->TOP ] = disk;
    }
    else
    {
        Tower->TOP = Tower->TOP + 1;
        return Tower->TOWER[ Tower->TOP ] = disk;
    }
}
int stack_Pop( STACK_HANOI *Tower )
{
    Tower->TOP = Tower->TOP - 1;
    return Tower->TOWER[ Tower->TOP + 1 ];
}
