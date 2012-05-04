#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

class PROGRAM
{
	int RAM[1000];
	int Reg[10];
	int * RAMptr;
	
public:
	
	PROGRAM();
	void Fill_Memory();
	void Display_Memory(int Max=1000);
	void Display_Registers();
	void Run();
	void Comando_0(char d, char s); //Goto
	void Comando_1(char a, char b); //Halt
	void Comando_2(char d, char n); //set register d to n (between 0 and 9)
	void Comando_3(char d, char n); //add n to register d
	void Comando_4(char d, char n); //multiply register d by n
	void Comando_5(char d, char s); //set register d to the value of register s
	void Comando_6(char d, char s); //add the value of register s to register d
	void Comando_7(char d, char s); //multiply register d by the value of register s
	void Comando_8(char d, char a); //set register d to the value in RAM whose address is in register a
	void Comando_9(char s, char a); //set the value in RAM whose address is in register a to the value of register s
};

class SPLIT_WORD
{
public:
	char hunds;
	char tens;
	char units;

	SPLIT_WORD(int x);
	void Display();
};

SPLIT_WORD::SPLIT_WORD(int x)
{
	hunds=x/100;
	tens=(x%100)/10;
	units=(x%100)%10;
	//	printf("%d: %d,%d,%d",x,hunds,tens,units);
}

void SPLIT_WORD::Display()
{
	printf("%c%c%c\n",hunds+'0',tens+'0',units+'0');
}


void PROGRAM::Comando_0(char d, char s) //Goto
{
	if(Reg[s])
	RAMptr=RAM+Reg[d]-1;
}

void PROGRAM::Comando_1(char a, char b) //Halt
{
	if(a==0 && b==0)
	RAMptr=RAM+1000;
}

void PROGRAM::Comando_2(char d, char n) //set register d to n (between 0 and 9)
{
	Reg[d]=(int)n;
}

void PROGRAM::Comando_3(char d, char n) //add n to register d
{
	Reg[d]+=(int)n;
	Reg[d]%=1000;
}

void PROGRAM::Comando_4(char d, char n) //multiply register d by n
{
	Reg[d]*=(int)n;
	Reg[d]%=1000;
}

void PROGRAM::Comando_5(char d, char s) //set register d to the value of register s
{
	Reg[d]=Reg[s];
}

void PROGRAM::Comando_6(char d, char s) //add the value of register s to register d
{
	Reg[d]+=Reg[s];
	Reg[d]%=1000;
}

void PROGRAM::Comando_7(char d, char s) //multiply register d by the value of register s
{
	Reg[d]*=Reg[s];
	Reg[d]%=1000;
}

void PROGRAM::Comando_8(char d, char a) //set register d to the value in RAM whose address is in register a
{
	Reg[d]=RAM[Reg[a]];
}

void PROGRAM::Comando_9(char s, char a) //set the value in RAM whose address is in register a to the value of register s
{
	RAM[Reg[a]]=Reg[s];
}

PROGRAM::PROGRAM()
{
	RAMptr=RAM;
	memset(RAM,0,sizeof(RAM));
	memset(Reg,0,sizeof(Reg));
}

void PROGRAM::Fill_Memory()
{
	char input[100];
	RAMptr=RAM;
	while(RAMptr<RAM+1000)
	{
		gets(input);
		if(*input=='\0')
		break;
		*RAMptr=atoi(input);
		RAMptr++;
	}
}

void PROGRAM::Display_Registers()
{
	printf("REG:  ");
	for(int j=0; j<10; j++)
	printf("%03d\t",Reg[j]);
	printf("\n");
}

void PROGRAM::Display_Memory(int Max)
{
	RAMptr=RAM;
	for(int i=0; i<Max; RAMptr+=10, i+=10)
	{
		printf("%03d:  ",i);
		for(int j=0; j<10; j++)
		printf("%03d\t",*(RAMptr+j));
		printf("\n");
	}
}

void PROGRAM::Run()
{
	int exec=0;


	for(RAMptr=RAM; RAMptr<RAM+1000; RAMptr++)
	{
		SPLIT_WORD w(*RAMptr);
		//Display_Registers();
		//printf("Procesando: ");
		//w.Display();

		switch(w.hunds)
		{
		case 0:
			Comando_0(w.tens,w.units);
			break;
		case 1:
			Comando_1(w.tens,w.units);
			break;
		case 2:
			Comando_2(w.tens,w.units);
			break;
		case 3:
			Comando_3(w.tens,w.units);
			break;
		case 4:
			Comando_4(w.tens,w.units);
			break;
		case 5:
			Comando_5(w.tens,w.units);
			break;
		case 6:
			Comando_6(w.tens,w.units);
			break;
		case 7:
			Comando_7(w.tens,w.units);
			break;
		case 8:
			Comando_8(w.tens,w.units);
			break;
		case 9:
			Comando_9(w.tens,w.units);
			break;
		}
		
		//		sleep(1);
		exec++;
	}
	printf("%d\n",exec);
}

int main()
{
	PROGRAM * p;
	int i=0;
	char input[128];

	gets(input);
	i=atoi(input);
	printf("\n");

	p=new PROGRAM[i];
	for(int x=0; x<i; x++)
	p[x].Fill_Memory();
	for(int x=0; x<i; x++)
	{
		p[x].Run();
		printf("\n");
	}

	delete p;
	
	return(0);
}


