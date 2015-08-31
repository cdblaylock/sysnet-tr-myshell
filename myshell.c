/** @file   myshell.c
 *  @brief  Main file for the shell
 *
 *  @author Paul Davila (pjd10)
 *  @author Christopher Blaylock (cdb56)
 *
 *  @bug    No known bugs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

int main(int argc, char *argv[])
{
	/*Maximum characters in entry*/
	char entry[256];
	/*Creating the new structure*/
    Param_t *param = NULL;
    param = newParam();
	/*Runs the program until exit is entered*/
	while(strcmp(entry, "exit") != 0)
	{
		/*prints the prompt to the screen*/
		printf ("$$$ ");
		/*gets user entry from the command line*/
		fgets(entry, 256, stdin);
		/*calls the function to break the entry into tokens*/
		tokenizer(entry, param);
		/*checks to see if the program was booted in debug mode*/
		if (argv[1] != NULL)
		{
			/*Prints the structure to the screen*/		
			if (strcmp(argv[1],"-Debug") == 0)
				printParams(param);
		}
	/*Sets the structure back to default*/
	setToNull(param);
	}
	/*Frees the allocated data for the struct*/
	free(param);
	return 0;
}
