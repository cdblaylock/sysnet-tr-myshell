/** @file   myshell.c
 *  @brief  Main file for the shell
 *
 *  @author Paul Davila (pjd10)
 *  @author Christopher Blaylock (cdb56)
 *
 *  @bug    No known bugs
 */

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
 *	execute the command based on the argument of the
 *	command.
 *
 * @return 	will return 0 upon successful completion of
 *			the program.
 */
int main(int argc, char *argv[])
{
	// Buffer to Hold User Input
	char buffer[BUFFSZE];
	char *token[MAXARGS];
	
	// Create a new Parameter Structure
    Param_t command = {NULL, NULL, 0, 0};
	setToNull(&command);
	
	int exitStatus = 0, error = 0;
	
	// Myshell Command Loop (Terminates when 'exit' is entered)
	while(strcmp(buffer, "exit") != 0)
	{
		int foundError = 0;
		
		// Setup for Forking
		pid_t childPID;
		int status;
		
		// Print the Prompt
		printf ("$$$ ");
		
		// Grab the Command User Input
		fgets(buffer, BUFFSZE, stdin);
		
		// Breaks the Input into Tokens
		foundError = storeTokens(&command, tokenizer(buffer, token), token);
		
		if(command.argumentCount == 0)
		{
			setToNull(&command);
			continue;
		}
		
		// Found Error or No Arguments
		if( (foundError != 0) || (command.argumentCount == 0) )
		{
			if(command.argumentCount != 0)
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
			//waiting on children to terminate
			exitStatus = waitOnChildren();
			//children terminated correctly
			if (exitStatus == 0)
				fprintf(stderr,"myshell: children terminated successfully.\n");
			//there was an error with a child's termination
			else
				fprintf(stderr,"myshell: child did not terminate properly!\n");
			
			// Resets the Structure
			setToNull(&command);
			return 0;
		}
		
		// Fork
		childPID = fork();
		
		// Forked Successfully
		if(childPID >= 0)
		{
			// Child Process executing the entered commands
			if(childPID == 0)
				error = executeCommand(&command);
			//if there was an error with execution return
			if (error == -1)
				return 0;
			else
			{
				// Foreground Process
				if(command.background != 1)
					waitpid(childPID, &status, 0);
			}
		}
		//forking failed print error and return from function
		else 
			return printError(1, 0);
		
		// Resets the Structure
		setToNull(&command);
	}
	return 0;
}
