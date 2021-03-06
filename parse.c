/** @file   parse.c
 *  @brief  Implements the functions of parse.h.
 *
 *  @author Paul Davila (pjd10)
 *  @author Christopher Blaylock (cdb56)
 *
 *  @bug    No known bugs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include "parse.h"

// Breaks String into Tokens
int tokenizer(char *str, char **token)
{
	// Delimiters
	char *separators = "' ''\n''\t'";
	int i = 0;
	
	// Break Text into Tokens
	token[i] = strtok(str, separators);
	while(token[i] != NULL)
	{
		i++;
	   	token[i] = strtok(NULL, separators);
  	}
	
	// Return the Number of Tokens
	return i;
}

// Function Stores the Tokens in the Param
int storeTokens(Param_t * param, int numOftokens, char **token)
{
	int foundError = 0;
	int j = 0;
	
	// Loop to Store the Tokens
	while (token[j] != NULL)
	{
		// Output or Input Redirect
		if (token[j][0] == '>' || token[j][0] == '<')
			foundError = tokenChecker(param, token[j]);
		else
		{
			if (token[j][0] != '&')
			{
				// Store in ArgumentVector
				param->argumentVector[param->argumentCount] = token[j]; 
				param->argumentCount++;
			}
			// Error Checking Prevent Arguments
			if( (param->inputRedirect != NULL) || (param->outputRedirect != NULL) )
			{
				foundError = backgroundChecker(param, j, numOftokens, token[j]);
				
				// Found Background Break
				if(param->background == 1)
					break;
				else
					// Detected Argument After <Input or >Output
					return printError(0, 0);
			}
			//calls the function to check if '&' is the last token
			foundError = backgroundChecker(param, j, numOftokens, token[j]);
				
			// Found Background Break
			if(param->background == 1)
				break;
		}
		//if an error was found
		if(foundError != 0)
				return -1;
		//token is incremented
		j++;
	}
	//if an error was found
	if(foundError != 0)
		return -1;
	//if there were no errors
	return 0;
}

// Determines Token Input or Output Redirect or &
int tokenChecker (Param_t * param, char *token)
{
	// Output Redirection Detected
	if (token[0] == '>')
	{
		// Error Multiple Output Redirections
		if(param->outputRedirect != NULL)
			return printError(0, 1);
			
		// Increment Token
		token++;
		
		// Error Space After Output Redirection Character [< filename]
		if(token[0] == '\0')
			return printError(0, 3);
			
		// Insert Token into Structure
		param->outputRedirect = token;
	}
	// Input Redirection Detected
	else if (token[0] == '<')
	{
		// Error Checking
		if( (param->outputRedirect != NULL) || (param->inputRedirect != NULL) )
		{
			// Error Output Redirection Before Input Redirection
			if(param->outputRedirect != NULL)
				return printError(0, 4);
			// Error Multiple Input Redirections
			else
				return printError(0, 2);
		}
		token++;
		
		// Error Space After Input Redirection Character [< filename]
		if(token[0] == '\0')
			return printError(0, 3);
			
		// Insert Token into Structure
		param->inputRedirect = token;
	}
	// Function was Successful
	return 0;
}

// Function to Determine If We Detected Background
int backgroundChecker(Param_t * param, int index, int numOftokens, char *token)
{
	// Detected Background
	if(token[0] == '&')
	{
		// Error Background is Not Last Argument
		if(index != numOftokens - 1)
			return printError(0, 5);
		
		// Last Token is '&' Set Background
		param->background = 1;
	}
	return 0;
}

// Print the Errors Detected & Return Appropriate Values
int printError(int type, int num)
{
	//If the error has to do with invalid input.
	if(type == 0)
	{
		fprintf(stderr,"myshell: incorrect command format: ");
		
		switch(num)
		{
			case 0:
				fprintf(stderr,"can only have |&| after input redirection |<| or output redirection |>|.");
				break;
			case 1:
				fprintf(stderr,"multiple |>| output redirections.");
				break;
			case 2:
				fprintf(stderr,"multiple |<| input redirections.");
				break;
			case 3:
				fprintf(stderr,"spaces not allowed after |>| or |<|.");
				break;
			case 4:
				fprintf(stderr,"output redirection |>| detected before input redirection |>|.");
				break;
			case 5:
				fprintf(stderr,"|&| can be used once, and it must be the last argument.");
				break;
		}
		fprintf(stderr,"\n");
	}
	//If the error message has to do with failed forking or child termination.
	if(type == 1)
	{
		switch(num)
		{
			case 0:
				fprintf(stderr,"myshell: process forking: forking has failed. Terminating...");
				break;
		}
		fprintf(stderr,"\n");
		return 0;
	}
	
	return -1;
}


// Function Prints the Parameters of the Structure to the Screen
void printParams(Param_t * param)
{
	int i = 0;
	
	// Prints the Structure
	printf ("InputRedirect: [%s]\n",
	  (param->inputRedirect != NULL) ? param->inputRedirect:"NULL");
	printf ("OutputRedirect: [%s]\n",
	  (param->outputRedirect != NULL) ? param->outputRedirect:"NULL");
	printf ("Background: [%d]\n", param->background);
	printf ("ArgumentCount: [%d]\n", param->argumentCount);
	for (i = 0; i < param->argumentCount; i++)
		printf("ArgumentVector[%2d]: [%s]\n", i, param->argumentVector[i]);
	
	return;
}

// Function to Execute the Command
int executeCommand(Param_t *param)
{
	// Redirects Input to Filename
	if(param->inputRedirect != NULL)
		freopen(param->inputRedirect, "r", stdin);
	
	// Redirects Output to Filename
	if(param->outputRedirect != NULL)
	{
		freopen(param->outputRedirect, "w", stdout);
		freopen(param->outputRedirect, "w", stderr);
	}
	//executing the user input
	execvp(param->argumentVector[0], param->argumentVector);
	
	// Command Did Not Execute Successfully (Terminate Process)
	fprintf(stderr,"myshell: command not found.\n");
	
	// Return -1 if exec did not work correctly
	return -1;
}

// Function to Wait on Children
int waitOnChildren()
{
	// PID & Status of PID
	pid_t pid;
	int status;
	
	printf("myshell: waiting for children...\n");
	while(1){
		// Wait for Children
		pid = wait(&status);

		// PID Returned Error
		if(pid == -1)
		{
			// Child Doesn't Exit Terminated Successfully.
			if(errno == ECHILD)
				return 0; 
		}
		else{
			// Children did not terminate successfully.
			if(WEXITSTATUS(status) != 0 || !WIFEXITED(status))
				return -1;
		}
	}
	
	// Function was Successful
	return 0;
}

// Function Resets All Values of the Structure to NULL or 0.
void setToNull(Param_t * param)
{
	int i = 0;
	
	param->inputRedirect = NULL;    
	param->outputRedirect = NULL;
	param->background = 0;             
	param->argumentCount = 0;   
	
	for(i = 0; i < MAXARGS; i++)
		param->argumentVector[i] = NULL;    
	
	return;
}
