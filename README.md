# SIC-XE-assembler
A cross assembler for a subset of the SIC/XE assembler, written in C/C++, producing code for the absolute loader used in SIC/XE programming.

#Requirement Specification:
It is required to implement Phase-1 of a (cross) Assembler for (a subset of) SIC/XE machines.
Phase-1 specification requires that an entity is to be designed as follows:

#Input
Source file name "src.txt" via a (.exe).

#Process
The input source file is parsed in order to produce the output.
Parsing process handles the following:
a) Source lines that are (instructions, storage declarations, comments, and assembler directives).
b) Errors and unhandled directives are handled with warnings and error messages.
c) For instructions, the parser is to minimally be capable of decoding 2, 3 and 4-byte instructions as follows:

2-byte with 1 or 2 symbolic register reference (e.g., TIXR A, ADDR S,A) 

RSUB (ignoring any operand or perhaps issuing a warning).
  
  3-byte PC-relative with symbolic operand to include immediate, indirect, and indexed addressing.
  
  3-byte absolute with non-symbolic operand to include immediate, indirect, and indexed addressing. 

4-byte absolute with symbolic or non-symbolic operand to include immediate, indirect, and indexed addressing.
The parser is to handle all storage directives (BYTE, WORD, RESW, and RESB).

#Output
a) The symbol table.

b) The source program in a format similar to a listing file ,also A meaningful error message is printed below the line in which an error occurred.


#Design
Pass-1 assembler:
- Source lines are read in sequence.
- The lines are passed to a parser method.
- There are two kinds of parsers
o Fixed format parser.
o Free format parser.
- According to the desired parsing criterion a parser method is chosen.
- The parser method mainly performs the following tasks:
o Checks for line syntax and detect errors.
o Create an Entry object to be added to the list file.
o Add labels to the symbol table.
- As these processes are performed methods implemented in the class are used to complement the required functionalities.
These methods are thoroughly described in the Algorithms description section.
