#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXLINELENGTH 80 //as defined in specs.pg26
#define MAXTAGLENGTH 30

#define DEBUGMODE 1 //debug
/*todo:
 *change COMPILERNAME
 *check if empty tag is checked
 */
int fileReader(char*);
//int parser(char arr[]); //debug:string?
int parser(char *arr); //debug:string?
int length(char arr[]);
int TagChecker(char* str);
int InstructionChecker(char* str);
int TagChecker2(char* str);
int InstructionChecker2(char* str);

int main(int argc, char *argv[])
{
	if(DEBUGMODE) printf("%s\n",__FUNCTION__);
if (!DEBUGMODE) //debug: remove this line
{
	  if(argc==1){ //no command line file variables passed, hence exit
		  printf("Error: Missing Argument. No input file given.\nUsage: COMPILERNAME [YourFileName].");
			exit(1);
	  }


	  fileReader(argv[1]);
}

if(DEBUGMODE) fileReader("/home/victor/workspace/MMN14/Debug/po.as"); //debug: read debug file

  return 0;
}

int fileReader(char *filename)
{
	if(DEBUGMODE) printf("%s \n",__FUNCTION__);
	//reads the file into a string, calls the parser for each line
	FILE *fp;

//if opening the command line argument file then exit.
		if(DEBUGMODE) printf("file name rxd: %s\n",filename);
	  if((fp = fopen(filename, "r"))==NULL) {
	    printf("Error: Cannot open file.\n");
	    exit(1);
	  }

	  char str[MAXLINELENGTH]; //buffer


	  while(!feof(fp)) {
	    if(fgets(str, MAXLINELENGTH-2, fp)){
	    		parser(str);
	        //read strings
	    }
	  }

	  fclose(fp);
	  return 0;
}

int parser(char line[])
{
	if(DEBUGMODE) printf("%s\n",__FUNCTION__);
	if(DEBUGMODE) printf("Args: %s\n",line);
	/*check if the instruction is one of the following:
	 * a. empty,b.  remark(prefixed with ';'discarded),c. legal instruction
	 * or d. compiler instruction(.data,.string,.entry, .extern) might be prefixed with a tag
	 * break each line into it's components: tag and opcode
	 * check if opcode and tag are legal using TagChecker() and InstructionChecker(), respectively
	 * generates opcode if both legal
	 */

	/*todo:
	 * check if token has spaces with strtok
	 */

	char* tag;
	char* op1;
	char* op2;
	char* instr;

	if (length(line)<=1) //empty line.
	{
			if(DEBUGMODE) printf("empty line");
			return(0);}
	if (line[0]==';') //remark
	{	if(DEBUGMODE) printf("remark line");
		return(0);}
	if (length(line)<3) //not empty, yet too short for legal command
	{					//shortest commands are hlt or rts without tag.
			if(DEBUGMODE) printf("error: too short for legal command");{
			return(-1);}
	}

char * pch;
pch=strtok(line,": ,");
	int partcounter=1;
	while (pch!=NULL)
	{

		switch(partcounter)
		{
		case 1:
			printf("%d. ",partcounter);
			strcpy(tag,pch);
		break;
		case 2:
			printf("%d. ",partcounter);
			strcpy(instr,pch);
		break;
		case 3:
			printf("%d. ",partcounter);
			strcpy(op1,pch);

		break;
		case 4:
			printf("%d. ",partcounter);
			strcpy(op2,pch);
		break;
		}

		pch=strtok(NULL,": ,");
		partcounter++;
	}
//	printf("********** blat: %s %s\n",tag,instr);

	if (TagChecker(tag)<=0){
			return (-1); //invalid tag
	}

	strcpy(instr,strtok(line," ")); //get first part of command

	if(InstructionChecker(instr)<=0){
		return (-1); //invalid command
	}


	return (0);
}


int parserold(char line[])
{
	if(DEBUGMODE) printf("%s\n",__FUNCTION__);
	if(DEBUGMODE) printf("Args: %s\n",line);
	/*check if the instruction is one of the following:
	 * a. empty,b.  remark(prefixed with ';'discarded),c. legal instruction
	 * or d. compiler instruction(.data,.string,.entry, .extern) might be prefixed with a tag
	 * break each line into it's components: tag and opcode
	 * check if opcode and tag are legal using TagChecker() and InstructionChecker(), respectively
	 * generates opcode if both legal
	 */

	/*todo:
	 * check if token has spaces with strtok
	 */
	char* tag, op1, op2,instr;

	if (length(line)<=1) //empty line. debug: <1 or <=1 with null\CR?
	{
			if(DEBUGMODE) printf("empty line");
			return(0);}
	if (line[0]==';') //remark
	{	if(DEBUGMODE) printf("remark line");
		return(0);}
	if (length(line)<3) //not empty, yet too short for legal command
	{
			if(DEBUGMODE) printf("error: too short for legal command");{
			return(-1);}
	}

	//get the tag:

	strcpy(tag,strtok(line,":")); //search for tag delimiter

	if (TagChecker(tag)<=0){
			return (-1); //invalid tag
	}

	strcpy(instr,strtok(line," ")); //get first part of command

	if(InstructionChecker(instr)<=0){
		return (-1); //invalid command
	}


	return (0);
}

/*Tagchecker returns:
 * -1 - illegal tag
 * 1 - legal tag
 * 0 - error
 */
int TagChecker(char* partstr)
{
	if(DEBUGMODE){ printf(__FUNCTION__);printf("\n");}
	if(DEBUGMODE) printf("Args: %s\n",partstr);
	/*ILLEGAL names for tags:
	 * 1. tags not including characters other than ':'
	 * 2. tags whose name is a command.
	 * 3. a tag that has already been used.
	 * 4. maximal length of tag: 30 chars.
	 */

	if (length(partstr)>MAXTAGLENGTH)
	{
			if(DEBUGMODE) printf("error: tag too long");
			return -1; //tag too long
	}
	else
	{

		//check if tag is a command or register (illegal)
		if (!strcmp(partstr,"mov")||!strcmp(partstr,"cmp")||!strcmp(partstr,"add")||!strcmp(partstr,"sub")||!strcmp(partstr,"ror")||!strcmp(partstr,"shr")||!strcmp(partstr,"lea")||
				!strcmp(partstr,"inc")||!strcmp(partstr,"dec")||!strcmp(partstr,"jmp")||!strcmp(partstr,"bne")||!strcmp(partstr,"red")||!strcmp(partstr,"prn")||!strcmp(partstr,"jsr")||
				!strcmp(partstr,"hlt")||!strcmp(partstr,"rts")||!strcmp(partstr,"r0")||!strcmp(partstr,"r1")||!strcmp(partstr,"r2")||!strcmp(partstr,"r3")||!strcmp(partstr,"r4")||
				!strcmp(partstr,"r5")||!strcmp(partstr,"r6")||!strcmp(partstr,"r7"))
		{

			if(DEBUGMODE) printf("error: tag can't be a command or a register");
			return -1;//tag can't be a command or register. specs.pg 27
		}
		if ((partstr[0]>='a' && partstr[0]<='z')|| (partstr[0]>='A' && partstr[0]<='Z')) //first char of tag is a letter
		{	 //debug: check if shouldn't copystr(tag,partstr); or tag=partstr
			return(1);
		}
		else
		{
			if(DEBUGMODE) printf("error: first char of tag isn't a letter");
			return (-1); //first char isn't a letter, thus error. specs.pg 27
		}
	}
	//return 0;
}

int InstructionChecker(char* partstr)
{
	if(DEBUGMODE) printf("%s\n",__FUNCTION__);
	if(DEBUGMODE) printf("Args: %s\n",partstr);
	/*valid(legal) commands:
	 * 1. right number of operands for instruction
	 * no operand instructions: rts, hlt
	 * one operand instructions: inc, dec, jmp, bne, red, prn, jsr
	 * two operand instructions: mov,vmp, add, sub, ror, shr, lea,
	 *
	 * 2.  one of 15 authorized commands (see spec.pg19-20)
	 */
	//command opcodes in specs.pg 19-20
	//no opreator req. commands:


	if(!strcmp(partstr,"rts"))
		return (14); //opcode for rts = 14
	else if(!strcmp(partstr,"hlt"))
			return (15); //opcode for hlt = 15
	else if(!strcmp(partstr,"inc")||!strcmp(partstr,"dec")||!strcmp(partstr,"jmp")||!strcmp(partstr,"bne")||!strcmp(partstr,"red")||!strcmp(partstr,"prn")||!strcmp(partstr,"jsr"))
	{
		//partstr=strtok(",",partstr); debug: use this
		if(!partstr) //no comma means there's no second operand, hence error
		{ if(DEBUGMODE) printf("second operand required\n");
			return (-1);
		}
		if(DEBUGMODE) printf("two operand instruction detected\n");

	}
	else if (!strcmp(partstr,"mov")||!strcmp(partstr,"cmp")||!strcmp(partstr,"add")||!strcmp(partstr,"sub")||!strcmp(partstr,"ror")||!strcmp(partstr,"shr")||!strcmp(partstr,"lea"))
	{
		if(DEBUGMODE) printf("one operand instruction detected\n");
			//two op req.
	}
	//one op. req.:


	else
	{
				if(DEBUGMODE) printf("error: not a valid command\n");
				return (-1); //not a valid command
	}

	if(DEBUGMODE) printf("end of function\n");
	return 0;
}

int length(char string[]) {

    int index;

    for (index = 0; string[index] != '\0'; ++index)
        continue;
    return (index);
}
