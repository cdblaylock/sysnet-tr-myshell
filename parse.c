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
	printf ("InputRedirect: [%s]\n",
	  (param->inputRedirect != NULL) ? param->inputRedirect:"NULL");
	printf ("OutputRedirect: [%s]\n",
	  (param->outputRedirect != NULL) ? param->outputRedirect:"NULL");
	printf ("Background: [%d]\n", param->background);
	printf ("ArgumentCount: [%d]\n", param->argumentCount);
	for (i = 0; i < param->argumentCount; i++)
		printf("ArgumentVector[%2d]: [%s]\n", i, param->argumentVector[i]);
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
	for(i = 0; i < param->argumentCount; i++)
	{
		param->argumentVector[i] = NULL;
	}       
	/*Set the background and argument count to 0*/
	param->background = 0;             
	param->argumentCount = 0;          
}
