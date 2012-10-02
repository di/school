/**********************************************************************
 * graph.c - this is just a sample, for the sake of the makefile
 *
 * Kurt Schmidt
 */

#include <stdio.h>

int main( int argc, char *argv[] )
{
	int i;

	printf( "\nYou want %s to read these files:\n", argv[0] );
	for( i=1; i<argc; ++i )
		printf( "\t%s\n", argv[i] );

	printf( "\n" );

	return( 0 );
}
