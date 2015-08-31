/** @file   parse.h
 *  @brief  Function prototypes for the command line parser of the shell.
 *
 *  @author Paul Davila (pjd10)
 *  @author Christopher Blaylock (cdb56)
 *
 *  @bug    No known bugs
 */

#ifndef _PARSE_H_
#define _PARSE_H_

/*Maimum number of tokens allowed*/
#define MAXARGS 32

/*Structure to hold input data*/
struct PARAM
{
	char *inputRedirect;           /* file name or NULL*/
	char *outputRedirect;          /* file name or NULL*/
	int background;                /* either 0 (false) or 1 (true)*/
	int argumentCount;             /* number of tokens in each argument vector*/
	char *argumentVector[MAXARGS]; /* array of strings*/
};

/* a typedef so that we don't need to use "struct PARAM" all the time */
typedef struct PARAM Param_t;

/**
 *@brief  Allocates the space for the structure.
 *
 *@return returns the new structure.
 */
Param_t* newParam();

/**
 *@brief       Breaks entered text into tokens.
 *
 *@param entry The entered text from the command line.
 *@param param The structure that the tokens will be stored.
 */
void tokenizer(char *entry, Param_t * param);

/**
 *@brief         Stores the tokens into the correct place in the struct.
 *               This function is called in the tokenizer function.
 *
 *@param param   The structure that the tokens will be stored.
 *@param counter The number of tokens that were created.
 *@param token   The tokens that are being stored in the struct.
 */
void storeTokens(Param_t * param, int counter, char **token);

/**
 *@brief       Checks to see if the token should be stored in outputRedirect or inputRedirect.  
 *             This function is called in the storeTokens function.
 *
 *@param token The token that is being compared.
 *@param param The structure that the token is being stored in.
 */
void tokenChecker (char *token, Param_t * param);

/**
 *@brief       Copies the token into outputRedirect or inputRedirect and removes the '<' or '>'
 *             symbol. This function is called in the tokenChecker function.
 *
 *@param token The token that is being copied.
 *@param param The structure that the token is being stored in. 
 */
char* tokenCpy(char *token, Param_t * param);

/**
 *@brief       Prints the structure when the program is booted in -Debug mode.
 *
 *@param param The structure that is being printed to the screen.
 */
void printParams(Param_t * param);

/**
 *@brief       Sets all the values in the structure back to the default state (either NULL or 0).
 *
 *@param param The structure that is being reset.
 */
void setToNull(Param_t * param);

#endif
