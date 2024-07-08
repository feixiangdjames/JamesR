/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2024
* Author: Chenglong (James) Wang
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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 ?Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2024
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */




/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */

/* TO_DO: BIT 3: END = End of buffer flag */
#define FLAG_END 0b00001000 /*Hex: 0x08*/
/* TO_DO: BIT 2: REL = Rellocation memory flag */
#define FLAG_REL 0b00000100 /*Hex: 0x04*/
/* TO_DO: BIT 1: FUL = Buffer full flag */
#define FLAG_FUL 0b00000010 /*Hex: 0x02*/
/* TO_DO: BIT 0: EMP = Buffer empty flag */
#define FLAG_EMP 0b00000001 /*Hex: 0x01*/

#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	jamesr_intg mark;			/* the offset to the mark position (in chars) */
	jamesr_intg read;			/* the offset to the get a char position (in chars) */
	jamesr_intg wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	jamesr_string	content;			/* pointer to the beginning of character array (character buffer) */
	jamesr_intg		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	jamesr_intg		increment;			/* character array increment factor */
	jamesr_intg		mode;				/* operational mode indicator */
	jamesr_byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;				/* Offset / position field */
	jamesr_intg		histogram[NCHAR];	/* Statistics of chars */
	jamesr_intg		numReaderErrors;	/* Number of errors from Reader */
} Buffer, *BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer	readerCreate		(jamesr_intg, jamesr_intg, jamesr_intg);
BufferPointer	readerAddChar		(BufferPointer const, jamesr_char);
jamesr_boln		readerClear		    (BufferPointer const);
jamesr_boln		readerFree		    (BufferPointer const);
jamesr_boln		readerIsFull		(BufferPointer const);
jamesr_boln		readerIsEmpty		(BufferPointer const);
jamesr_boln		readerSetMark		(BufferPointer const, jamesr_intg);
jamesr_intg		readerPrint		    (BufferPointer const);
jamesr_intg		readerLoad			(BufferPointer const, FILE* const);
jamesr_boln		readerRecover		(BufferPointer const);
jamesr_boln		readerRetract		(BufferPointer const);
jamesr_boln		readerRestore		(BufferPointer const);
jamesr_void		readerChecksum		(BufferPointer const);
/* Getters */
jamesr_char		readerGetChar		(BufferPointer const);
jamesr_string	readerGetContent	(BufferPointer const, jamesr_intg);
jamesr_intg		readerGetPosRead	(BufferPointer const);
jamesr_intg		readerGetPosWrte	(BufferPointer const);
jamesr_intg		readerGetPosMark	(BufferPointer const);
jamesr_intg		readerGetSize		(BufferPointer const);
jamesr_intg		readerGetInc		(BufferPointer const);
jamesr_intg		readerGetMode		(BufferPointer const);
jamesr_byte		readerGetFlags		(BufferPointer const);
jamesr_void		readerPrintStat		(BufferPointer const);
jamesr_intg		readerNumErrors		(BufferPointer const);

#endif
