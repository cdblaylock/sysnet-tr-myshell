/** @file   myshell.c
 *  @brief  Main file for the shell
 *
 *  @author Paul Davila (pjd10)
 *  @author Christopher Blaylock (cdb56)
 *
 *  @bug    No known bugs
 */

<<<<<<< HEAD
 // Library Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

// Parse Include
#include "parse.h"

/** @brief myshell entry point.
 *  
 *  This is the entry point for myshell where
 *	we will prompt the user to enter any command
 *  tokenize the input create a new process and 
 *	eixexecute the command based on the argument of the
 *	command.
 *
 * @return 	will return 0 upon successful completion of
 *			the program.
 */
int main(int argc, char *argv[])
{
	// Buffer to Hold User Input
	char buffer[BUFFSZE];
	
	// Create a new Parameter Structure
    Param_t command = {NULL, NULL, 0, 0};
	
	int exitStatus = 0;
	
	// Myshell Command Loop (Terminates when 'exit' is entered)
	while(strcmp(buffer, "exit") != 0)
	{
		int foundError = 0;
		
		// Setup for Forking
		pid_t childPID;
		
		// Print the Prompt
		printf ("$$$ ");
		
		// Grab the Command User Input
		fgets(buffer, BUFFSZE, stdin);
		
		// Breaks the Input into Tokens
		foundError = tokenizer(buffer, &command);
		
		// Tokenizer Returned an Error Get a New Command
		if(foundError != 0)
		{
			fprintf(stderr,"myshell: Format: command [argument1] [argument2] [<inputfile] [>outputfile] [&]\n");
			setToNull(&command);
			continue;
		}
		
		// Is Program in Debug Mode?
		if (argv[1] != NULL)
		{
			// Prints the Structure
			if (strcmp(argv[1],"-Debug") == 0)
				printParams(&command);
		}
	
		// Exit Before Forking Again
		if( strcmp(command.argumentVector[0], "exit") == 0)
		{
			exitStatus = waitOnChildren();
			
			if (exitStatus == 0)
				printf("Children Terminated Successfully. \n");
			else
				fprintf(stderr,"Child did not terminate properly!\n");
			
			// Resets the Structure
			setToNull(&command);
			return 0;
		}
		
		// Fork
		childPID = fork();
		
		// Forked Successfully?
		if(childPID >= 0)
		{
			// Child Process
			if(childPID == 0)
				executeCommand(&command);
			// Parent Process
			else
			{
				// Foreground Process
				if(command.background != 1)
					waitpid(childPID, NULL, 0);
			}
		}
		// Fork Has Failed. Terminate
		else 
			return printError(1, 0);
		
		// Resets the Structure
		setToNull(&command);
	}
	return 0;
}
=======
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
>>>>>>> origin/master
