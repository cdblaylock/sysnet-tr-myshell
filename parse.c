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
<<<<<<< HEAD
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include "parse.h"

// Breaks String into Tokens
int tokenizer(char *str, Param_t * param)
{
	int foundError = 0;
	int i = 0;
	
	// Stores the Tokens & Delimiters
	char *token[MAXARGS];
	char *separators = "' ''\n''\t'";

	// Break Text into Tokens
	token[i] = strtok(str, separators);
	while(token[i] != NULL)
	{
		i++;
		// Get a New Token
	   	token[i] = strtok(NULL, separators);
  	}
	
	// Store the Tokens into the Param
	foundError = storeTokens(param, i, token);
	
	if(foundError != 0)
		return -1;
	
	return 0;
}

int errorChecker(Param_t * param, int numOftokens, char **token)
{
	
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
			// Store in ArgumentVector
			param->argumentVector[param->argumentCount] = token[j]; 
			param->argumentCount++;
			
			// Error Checking Prevent Arguments
			if( (param->inputRedirect != NULL) || (param->outputRedirect != NULL) )
			{
				foundError = backgroundChecker(param, j, numOftokens, token[j]);
				
				// Found Background Break
				if(param->background == 1)
					break;
				else
				{
					// Detected Argument After <Input or >Output
					printError(0, 0);
					return -1;
				}
			}
			foundError = backgroundChecker(param, j, numOftokens, token[j]);
				
			// Found Background Break
			if(param->background == 1)
				break;
		}
		
		if(foundError != 0)
				return -1;
	
		j++;
	}
	
	if(foundError != 0)
		return -1;
	
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
			
		token++;
		
		// Error Space After Output Redirection Character [< filename]
		if(token[0] == '\0')
			return printError(0, 3);
			
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
			
		param->inputRedirect = token;
	}
	return 0;
}

int printError(int type, number)
{
	if(type == 0)
	{
		fprintf(stderr,"myshell: incorrect command format: ");
		
		switch(number)
		{
			case 0:
				fprintf(stderr,"Can only have |&| AFTER input redirection |<| OR output redirection |>|.");
				break;
			case 1:
				fprintf(stderr,"MULTIPLE |>| output redirections.");
				break;
			case 2:
				fprintf(stderr,"MULTIPLE |<| input redirections.");
				break;
			case 3:
				fprintf(stderr,"Spaces NOT allowed after |>|.");
				break;
			case 4:
				fprintf(stderr,"Output redirection |>| detected BEFORE input redirection |>|.");
				break;
			case 5:
				fprintf(stderr,"|&| Can be used ONCE, and it must be the LAST argument.");
				break;
		}
		fprintf(stderr,"\n");
	}
	
	if(type == 1)
	{
		switch(number)
		{
			case 0:
				fprintf(stderr,"myshell: Process Forking: Forking has FAILED. Terminating...\n");
			case 1:
		}
		fprintf(stderr,"\n");
		return 0;
	}
	
	return -1;
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

// Function Prints the Parameters of the Structure to the Screen
void printParams(Param_t * param)
{
	int i = 0;
	
	// Prints the Structure
=======
#include "parse.h"

/*Creates a new structure for the data*/
Param_t* newParam()
{
/* Allocating space for struct*/
    Param_t* param = malloc (sizeof(Param_t));
/*returns the new struct*/
    return param;
}

/*Breaks the enter string into tokens*/
void tokenizer(char *entry, Param_t * param)
{
	/*Varibles that are used as counters*/
	int counter = 0, i = 0;
	/*stores the tokens*/
	char *token[MAXARGS];
	/*token seperators*/
	char *seperators = "' ''\n''\t'";

	/*Using strtok to break text into tokens*/
	token[i] = strtok(entry, seperators);
	while(token[i] != NULL)
	{
		/*counter used to increment through tokens*/
		i++;
		/*counter used to keep track of the number of tokens*/
		counter++;
	   	token[i] = strtok(NULL, seperators);
  	}
	/*storing the number of tokens created*/
	param->argumentCount = counter;
	/*function call for the function that stores tokens in correct area*/
	storeTokens (param, counter, token);
}

/*Function used to store the tokens in the correct part of the struct*/
void storeTokens(Param_t * param, int counter, char **token)
{
	/*variables used as incrementers*/
	int j = 0, k = 0;
	/*loop used to store the tokens in the correct space*/
	while (token[j] != NULL)
	{
		/*checks to see if tokens should be stored in output or input redirect*/
		if (token[j][0] == '>' || token[j][0] == '<')
			tokenChecker(token[j], param);
		/*checks to see if token should be stored in the argument vector*/
		else 
		{
			if (j == counter -1 && *token[counter-1] == '&')
				break;//exits if the '&' is the last token
			/*stores the token in the vector*/ 
			param->argumentVector[k] = token[j];
			/*keeps track of where next token will go in the argument vector*/
			k++;
		}
		/*Incrementing throught the tokens*/
		j++;
	}
	/*if the last token is '&' sets the background to 1*/
	if (*token[counter-1] == '&')
		param->background = 1;

}

/*Checks to see if the token should go in the output or the input redirect*/
void tokenChecker (char *token, Param_t * param)
{
	/*calls function to drop '>' and stores the token in outputRedirect*/
	if (token[0] == '>')
		param->outputRedirect = tokenCpy(token, param);
	/*calls function to drop '<' and stores the token in inputRedirect*/
	else if (token[0] == '<')
		param->inputRedirect = tokenCpy(token, param);
		
}

/*Function to drop '<' or '>' in token*/
char* tokenCpy(char *token, Param_t * param)
{
	/*variables to copy tokens*/
	int i = 0, j = 1;
	/*allocates space to copy string*/
	char *copy= malloc (sizeof(char)*20);
	/*if '<' or '>' has no characters following it: return NULL*/
	if (token[1] == '\0')
		return NULL;
	/*copy string until terminating character is reached*/
	while (token[j] != '\0')
	{
		copy[i] = token[j];
		j++;
		i++;
	}
	/*return the copied string*/
	return copy;
}

/*Function to print the structure to the screen*/
void printParams(Param_t * param)
{
	/*used as an incrementer*/
	int i;
	/*Prints everything to the screen*/
>>>>>>> origin/master
	printf ("InputRedirect: [%s]\n",
	  (param->inputRedirect != NULL) ? param->inputRedirect:"NULL");
	printf ("OutputRedirect: [%s]\n",
	  (param->outputRedirect != NULL) ? param->outputRedirect:"NULL");
	printf ("Background: [%d]\n", param->background);
	printf ("ArgumentCount: [%d]\n", param->argumentCount);
	for (i = 0; i < param->argumentCount; i++)
		printf("ArgumentVector[%2d]: [%s]\n", i, param->argumentVector[i]);
<<<<<<< HEAD
	
	return;
}

// Function to Execute the Command
void executeCommand(Param_t *param)
{
	// Redirects Input to Filename
	if(param->inputRedirect != NULL)
		freopen(param.inputRedirect, "r", stdin);
	
	// Redirects Output to Filename
	if(param->outputRedirect != NULL)
	{
		freopen(param->outputRedirect, "w", stdout);
		freopen(param->outputRedirect, "w", stderr);
	}
	
	execvp(param->argumentVector[0], param->argumentVector);
	
	// Command Did Not Execute Successfully (Terminate Process)
	fprintf(stderr,"myshell: command not found.\n");
	
	return;
}

// Function to Wait on Children
int waitOnChildren()
{
	// PID & Status of PID
	pid_t pid;
	int status;
	
	printf("Waiting for children...\n");
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
	return 0;
}

// Function Resets All Values of the Structure to NULL or 0.
void setToNull(Param_t * param)
{
	int i;
	
	param->inputRedirect = NULL;    
	param->outputRedirect = NULL;
	
=======
}

/*Function to set all the values in the struct to NULL or 0*/
void setToNull(Param_t * param)
{
	/*incrementer*/
	int i;
	/*set input and output redirect to NULL*/
	param->inputRedirect = NULL;    
	param->outputRedirect = NULL;
	/*Set all the values in the argument vector to NULL*/
>>>>>>> origin/master
	for(i = 0; i < param->argumentCount; i++)
	{
		param->argumentVector[i] = NULL;
	}       
<<<<<<< HEAD
	
	param->background = 0;             
	param->argumentCount = 0;   

	return;
}
=======
	/*Set the background and argument count to 0*/
	param->background = 0;             
	param->argumentCount = 0;          
}
>>>>>>> origin/master
