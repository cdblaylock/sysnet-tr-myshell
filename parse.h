/** @file parse.h
 *  @brief Function prototypes for the command line
 *	parser of the shell.
 *
 *  More Descriptions Go Here
 *
 *  @author Christopher Blaylock (cdb56)
 *  @author Paul  (fhacker)
 *  @bug No known bugs.
 */
 
 /* don’t test program with more than this many tokens for input */
#define MAXARGS 32

/* structure to hold input data */
struct PARAM
{
	char *inputRedirect;           	/* file name or NULL */
	char *outputRedirect;  			/* file name or NULL */
	int  background;               	/* either 0 (false) or 1 (true) */
	int  argumentCount;            	/* number of tokens in argument vector */
	char *argumentVector[MAXARGS]; 	/* array of strings */
};
/* a typedef so we don’t need to use "struct PARAM" all the time */
typedef struct PARAM Param_t;

void printParams(Param_t * param)
{
	int i;
	printf ("InputRedirect: [%s]\n",
		(param->inputRedirect != NULL) ? param->inputRedirect:"NULL");
	printf ("OutputRedirect: [%s]\n",
		(param->outputRedirect != NULL) ? param->outputRedirect:"NULL");
	printf ("Background: [%d]\n", param->background);
	printf ("ArgumentCount: [%d]\n", param->argumentCount);
	for (i = 0; i < param->argumentCount; i++)
		printf("ArgumentVector[%2d]: [%s]\n", i, param->argumentVector[i]);
}