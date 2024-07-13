/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2024
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
#
# ECHO "=---------------------------------------="
# ECHO "|  COMPILERS - ALGONQUIN COLLEGE (S24)  |"
# ECHO "=---------------------------------------="
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ?
# ECHO "    @@                             @@    ?
# ECHO "    @@           %&@@@@@@@@@@@     @@    ?
# ECHO "    @@       @%% (@@@@@@@@@  @     @@    ?
# ECHO "    @@      @& @   @ @       @     @@    ?
# ECHO "    @@     @ @ %  / /   @@@@@@     @@    ?
# ECHO "    @@      & @ @  @@              @@    ?
# ECHO "    @@       @/ @*@ @ @   @        @@    ?
# ECHO "    @@           @@@@  @@ @ @      @@    ?
# ECHO "    @@            /@@    @@@ @     @@    ?
# ECHO "    @@     @      / /     @@ @     @@    ?
# ECHO "    @@     @ @@   /@/   @@@ @      @@    ?
# ECHO "    @@     @@@@@@@@@@@@@@@         @@    ?
# ECHO "    @@                             @@    ?
# ECHO "    @@         S O F I A           @@    ?
# ECHO "    @@                             @@    ?
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ?
# ECHO "                                         "
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/

/*
************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 ?Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2024
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 13

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	INL_T,		/*  2: Integer literal token */
	STR_T,		/*  3: String literal token */
	LPR_T,		/*  4: Left parenthesis token */
	RPR_T,		/*  5: Right parenthesis token */
	LBR_T,		/*  6: Left brace token */
	RBR_T,		/*  7: Right brace token */
	KW_T,		/*  8: Keyword token */
	EOS_T,		/*  9: End of statement (semicolon) */
	RTE_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	CMT_T		/* 12: Comment token */
};

/* TO_DO: Define the list of keywords */
static jamesr_string tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MNID_T",
	"INL_T",
	"STR_T",
	"LPR_T",
	"RPR_T",
	"LBR_T",
	"RBR_T",
	"KW_T",
	"EOS_T",
	"RTE_T",
	"SEOF_T",
	"CMT_T"
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	jamesr_intg codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	jamesr_intg intValue;				/* integer literal attribute (value) */
	jamesr_intg keywordIndex;			/* keyword index in the keyword table */
	jamesr_intg contentString;			/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	jamesr_real floatValue;				/* floating-point literal attribute (value) */
	jamesr_char idLexeme[VID_LEN + 1];	/* variable identifier token attribute */
	jamesr_char errLexeme[ERR_LEN + 1];	/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	jamesr_byte flags;			/* Flags information */
	union {
		jamesr_intg intValue;				/* Integer value */
		jamesr_real floatValue;			/* Float value */
		jamesr_string stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	jamesr_intg code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	jamesr_intg scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */
/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '&'
#define CHRCOL4 '\''
#define CHRCOL6 '#'
#
/* These constants will be used on VID / MID function */
#define MNID_SUF '&'
#define COMM_SYM '#'

/* TO_DO: Error states and illegal state */
#define ESNR	8		/* Error state with no retract */
#define ESWR	9		/* Error state with retract */
#define FS		10		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		20
#define CHAR_CLASSES	12

/* TO_DO: Transition table - type of states defined in separate table */
static jamesr_intg transitionTable[NUM_STATES][CHAR_CLASSES] = {
/*    [A-z],[0-9],  _,    .,   #,    ',     ",    /,     *,      -,    /n,   Others
	  L(0), D(1), U(2), P(3), A(4), Q(5),  R(6) , S(7), W(8),   H(9),  E(10), O(11) */
	{   1,   3,   ESNR,   5,    8,   ESNR,  ESNR,  ESNR, ESNR,  ESNR, ESNR,   ESNR},// S0: NOAS
	{   1,   1,    2,     2,    2,    2,    2,    2,    2,    2,   2,     2},// S1: FSWR
    {   FS,  FS,   FS,   FS,    FS,   FS,   FS,   FS,   FS,   FS,  FS,    FS},// S2: FSWR
    {   4,   1,    4,     5,     4,    4,    4,    4,    4,    4,   4,     4},// S3: NOAS
	{   FS,  FS,   FS,   FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS},// S4: FSWR
	{  ESNR, 6,   ESNR,  ESNR,  ESNR, ESNR, ESNR, ESNR, ESNR, ESNR,ESNR,ESNR},// S5: NOAS
	{   7,   6,     7,     7,    7,     7,   7,     7,    7,   7,  7,  7},// S6: NOAS
	{   FS,  FS,   FS,   FS,    FS,   FS,   FS,   FS,   FS,   FS,  FS,  FS},// S7: FSWR
	{   9,   9,   9,  9,    9,    9,   9,  9, 9,  9, ESNR,9},// S8: NOAS
	{   9,  9,   9,   9,    9,   9,   9,   9,   9,   10, 9},// S9:NOAS
	{   FS,  FS,   FS,   FS,    FS,   FS,   FS,   FS,   FS,   FS,    FS},// S10: FSNR
	{   1,   1,   ESNR,  6,    8,    11,   13,  ESNR, ESNR,  ESNR, ESNR},// S11: NOAS
	{  FS,  FS,   FS,   FS,    FS,   FS,   FS,   FS,   FS,   FS,    FS},// S12: NOAS
	{   1,   1,   ESNR,  6,    8,    11,   13,  ESNR, ESNR,  ESNR, ESNR},// S13: NOAS
	{   FS,  FS,   FS,   FS,    FS,   FS,  FS,   FS,   FS,   FS,    FS},// S14: NOAS
	{   1,   1,   ESNR,  6,    8,    11,   13,  ESNR, ESNR,  ESNR, ESNR},// S15: NOAS
	{   1,   1,   ESNR,  6,    8,    11,   13,  ESNR, ESNR,  ESNR, ESNR},// S16: NOAS
	{   1,   1,   ESNR,  6,    8,    11,   13,  ESNR, ESNR,  ESNR, ESNR},// S17: NOAS
	{   1,   1,   ESNR,  6,    8,    11,   13,  ESNR, ESNR,  ESNR, ESNR},// S18: NOAS
	{   FS,  FS,   FS,   FS,    FS,   FS,  FS,   FS,   FS,   FS,    FS},// S19: NOAS
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static jamesr_intg stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSWR, /* 02 (VID|MET|KEY) -  */
	NOFS, /* 03  */
	FSWR, /* 04 (IL)Integer Literal*/
	NOFS, /* 05*/
	NOFS, /* 06*/
	FSWR, /* 07 (FL)Float Literal*/
	NOFS, /* 08 */
	NOFS, /* 09 */
	FSNR, /* 10 (SCL) single comment line*/
	NOFS, /* 11 */
	FSNR, /* 12 (MID) - Methods */
	FSWR, /* 13 (KEY) */
	NOFS, /* 14 */
	FSNR, /* 15 */
	NOFS, /* 16 */
	FSNR, /* 17  */
	FSNR, /* 18 */
	FSWR  /* 19 */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
jamesr_intg			startScanner(BufferPointer psc_buf);
static jamesr_intg	nextClass(jamesr_char c);					/* character class function */
static jamesr_intg	nextState(jamesr_intg, jamesr_char);		/* state machine function */
jamesr_void			printScannerData(ScannerData scData);
Token				tokenizer(jamesr_void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(jamesr_string lexeme);

/* Declare accepting states functions */
Token funcSL	(jamesr_string lexeme);
Token funcIL	(jamesr_string lexeme);
Token funcID	(jamesr_string lexeme);
Token funcCMT   (jamesr_string lexeme);
Token funcKEY	(jamesr_string lexeme);
Token funcErr	(jamesr_string lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	NULL,		/* -    [06] */
	funcCMT,	/* COM  [07] */
	funcErr,	/* ERR1 [06] */
	funcErr		/* ERR2 [07] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 10

/* TO_DO: Define the list of keywords */
static jamesr_string keywordTable[KWT_SIZE] = {
	"data",		/* KW00 */
	"code",		/* KW01 */
	"int",		/* KW02 */
	"real",		/* KW03 */
	"string",	/* KW04 */
	"if",		/* KW05 */
	"then",		/* KW06 */
	"else",		/* KW07 */
	"while",	/* KW08 */
	"do"		/* KW09 */
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	jamesr_char indentationCharType;
	jamesr_intg indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
jamesr_intg numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
