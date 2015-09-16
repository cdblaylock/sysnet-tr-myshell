/** @file   parse.h
 *  @brief  Function prototypes for the command line parser of the shell.
 *
 *  @author Paul Davila (pjd10)
 *  @author Christopher Blaylock (cdb56)
 *
 *  @bug    No known bugs
 */

 // Include Definitions
#ifndef _PARSE_H_
#define _PARSE_H_

// Custom Definitions
#define MAXARGS 32
#define BUFFSZE	1024
#define MAXPROC	200

/*
 * Parameter Structure
 */
struct PARAM
{
	char *inputRedirect;           /* file name or NULL*/
	char *outputRedirect;          /* file name or NULL*/
	int background;                /* either 0 (false) or 1 (true)*/
	int argumentCount;             /* number of tokens in each argument vector*/
	char *argumentVector[MAXARGS]; /* array of strings*/
};

/*
 * TypeDef for Structure PARAM
 */
typedef struct PARAM Param_t;

/**
 *@brief       			Breaks entered text into tokens.
 *
 *@param entry 			The entered text from the command line.
 *@param param 			The structure that the tokens will be stored.
 */
int tokenizer(char *str, Param_t *param);

/**
 *@brief         		Stores the tokens into the correct place in the struct.
 *               		This function is called in the tokenizer function.
 *
 *@param param   		The structure that the tokens will be stored.
 *@param counter 		The number of tokens that were created.
 *@param token   		The tokens that are being stored in the struct.
 *
 *@return 				0 on successfully completion. -1 when error is detected.
 */
int storeTokens(Param_t *param, int counter, char **token);

/**
 *@brief       			Checks to see if the token should be stored in outputRedirect or inputRedirect.  
 *             			This function is called in the storeTokens function.
 *
 *@param token 			The token that is being compared.
 *@param param 			The structure that the token is being stored in.
 *
 *@return 				0 on successfully completion. -1 when error is detected.
 */
int tokenChecker (Param_t * param, char *token);


/**
 *@brief       			Checks to see if the token passed into the function is 
 *             			the '&' character indicated we have found the Background
 *						setting. If the background is not the last token we spit out
 *						an error.
 *
 *@param param 			The structure that the token is being stored in.
 *@param token 			The token that is being compared.
 *@param index			The current token we are on.
 *@param numOftokens	Number of tokens total.
 *
 *@return 		0 on successfully completion. -1 when error is detected.
 */
int backgroundChecker(Param_t * param, int index, int numOftokens, char *token);

/**
 *@brief      			Prints the structure when the program is booted in -Debug mode.
 *
 *@param param 			The structure that is being printed to the screen.
 */
void printParams(Param_t *param);


/**
 *@brief      			Function will wait on children
 *
 *@return				The structure that is being printed to the screen.
 */
int waitOnChildren();

/**
 *@brief      			Sets all the values in the structure back to the default state (either NULL or 0).
 *
 *@param param 			The structure that is being reset.
 */
void setToNull(Param_t *param);

#endif