# SIC-XE-assembler
A cross assembler for a subset of the SIC/XE assembler, written in C/C++, producing code for the absolute loader used in SIC/XE programming.

#Requirement Specification:
-Phase 1
It is required to implement Phase-1 of a (cross) Assembler for (a subset of) SIC/XE machines.
Phase-1 specification requires that an entity is to be designed as follows:

1)Input
Source file name "src.txt" via a (.exe).

2)Process
The input source file is parsed in order to produce the output.
Parsing process handles the following:
a) Source lines that are (instructions, storage declarations, comments, and assembler directives).
b) Errors and unhandled directives are handled with warnings and error messages.
c) For instructions, the parser is to minimally be capable of decoding 2, 3 and 4-byte instructions as follows:
 2-byte with 1 or 2 symbolic register reference (e.g., TIXR A, ADDR S,A)
 RSUB (ignoring any operand or perhaps issuing a warning).
 3-byte PC-relative with symbolic operand to include immediate, indirect, and indexed addressing.
 3-byte absolute with non-symbolic operand to include immediate, indirect, and indexed addressing.
 4-byte absolute with symbolic or non-symbolic operand to include immediate, indirect, and indexed addressing.
 The parser is to handle all storage directives (BYTE, WORD, RESW, and RESB).

-Output
a) The symbol table.

b) The source program in a format similar to a listing file ,also A meaningful error message is printed below the line in which an error occurred.

-phase 2
It is required to implement Phase-2 of a (cross) Assembler for (a subset of) SIC/XE machines.
Phase-2 specification requires the following:

1) Input:
Source file name "src.txt" via a (.exe).

2) Process:
The input source file is parsed in order to produce pass-1, after that the symbol table produced in phase-1 is used while forming phase-2 assembled file and object code.
The assembler for phase-2 should support:
1. EQU and ORG statements.
2. Simple expression evaluation. A simple expression includes simple (A
<op> B) operand arithmetic, where <op> is one of +,-,*,/ and no spaces
surround the operation, eg. A+B.

3) Output:
The output of the assembler should include (at least):
1. Object-code file whose format is the same as the one described in the text
book in section 2.1.1 and 2.3.5.
2. A report at the end of pass2.
Pass1 and Pass2 errors should be included as
part of the assembler report, exhibiting both the offending line of source code and the error.

 


#Design
-Pass-1 assembler:
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

-Pass-2 assembler:
- Source- Source lines are read in sequence.
- The lines are passed to a parser method which supports free formatting.
- The parser method, along with other methods, is used as discussed before to output the pass-1 for the assembler and save the symbol table.
- If pass-1 was performed successfully pass-2 is then executed.
- In pass-2 every line entry is checked for producing the op-code.
- Errors in pass-2 are recorded so as to determine whether the object file will be created or not.
- 

