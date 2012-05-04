#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class FIELD
{
	char * M;
	int n;
	int m;

	FIELD * ant;
	FIELD * sig;
	
public:

	FIELD(int col, int lin);
	~FIELD();
	void Fill();
	void Display();
	void Resolve();
	FIELD * Next();
	FIELD * Previous();
	void SetNext(FIELD * x);
	void SetPrevious(FIELD * x);
};

class FIELD_LIST
{
	FIELD * x;
	
public:
	FIELD_LIST();
	~FIELD_LIST();
	bool Add(int col, int lin);
	void Fill_current();
	void Go_First();
	void Go_Last();
	void Resolve_Fields();
	void Display_Fields();
};


FIELD_LIST::FIELD_LIST()
{
	x=NULL;
}

FIELD_LIST::~FIELD_LIST()
{
	FIELD * aux;
	Go_First();
	while(x)
	{
		aux=x->Next();
		delete(x);
		x=aux;
	}
}

bool FIELD_LIST::Add(int col, int lin)
{
	FIELD * aux;
	
	Go_Last();
	aux=new FIELD(col,lin);
	if(!aux)
	return(false);
	if(x)
	{
		aux->SetPrevious(x);
		x->SetNext(aux);
		x=x->Next();
	}
	else
	x=aux;
	return(true);
}

void FIELD_LIST::Fill_current()
{
	x->Fill();
}

void FIELD_LIST::Go_First()
{
	if(x)
	while(x->Previous()!=NULL)
	x=x->Previous();
}

void FIELD_LIST::Go_Last()
{
	if(x)
	while(x->Next()!=NULL)
	x=x->Next();
}

void FIELD_LIST::Resolve_Fields()
{
	Go_First();
	if(x)
	{
		while(x->Next()!=NULL)
		{
			x->Resolve();
			x=x->Next();
		}
		x->Resolve();
	}
}

void FIELD_LIST::Display_Fields()
{
	int i=0;
	Go_First();
	if(x)
	{
		while(x->Next()!=NULL)
		{
			printf("\n\nField #%d:",++i);
			x->Display();
			x=x->Next();
		}
		printf("\n\nField #%d:",++i);
		x->Display();
	}
}


FIELD::FIELD(int lin, int col)
{
	ant=NULL;
	sig=NULL;
	n=col;
	m=lin;
	M=new char[n*m];
	
	if(!M)
	{
		printf("No hay Memoria!!!\n");
		return;
	}

	memset(M,0,sizeof(char)*n*m);
}

FIELD::~FIELD()
{
	if(M)
	delete(M);
}

FIELD * FIELD::Next()
{
	return sig;
}

FIELD * FIELD::Previous()
{
	return ant;
}

void FIELD::SetNext(FIELD * x)
{
	sig=x;
}

void FIELD::SetPrevious(FIELD * x)
{
	ant=x;
}

void FIELD::Fill()
{
	if(!M)
	{
		printf("No existe campo!!!\n");
		return;
	}
	
	for(int j=0; j<m; j++)
	for(int i=0; i<n; i++)
	{
		//			if(i==0)
		//				printf("\n");
		while(1)
		{
			M[j*n+i]=getchar();
			if(M[j*n+i] == '.' || M[j*n+i] == '*')
			break;
			//				else
			//					putchar('\b');
		}
	}
}

void FIELD::Display()
{
	if(!M)
	{
		printf("No existe campo!!!\n");
		return;
	}

	for(int j=0; j<m; j++)
	for(int i=0; i<n; i++)
	{
		if(i==0)
		putchar('\n');
		putchar(M[j*n+i]);
	}
}

void FIELD::Resolve()
{
	for(int j=0; j<m; j++)
	for(int i=0; i<n; i++)
	{
		char x=0;
		char * ptr=M+j*n+i;
		if(*ptr=='.')
		{
			if(j)
			{
				if(i && *(ptr-n-1)=='*')
				x++;
				if(*(ptr-n)=='*')
				x++;
				if(n-i-1 && *(ptr-n+1)=='*')
				x++;
			}
			
			if(i && *(ptr-1)=='*')
			x++;
			if(n-i-1 && *(ptr+1)=='*')
			x++;
			
			if(m-j-1)
			{
				if(i && *(ptr+n-1)=='*')
				x++;
				if(*(ptr+n)=='*')
				x++;
				if(n-i-1 && *(ptr+n+1)=='*')
				x++;
			}
			*ptr=x+'0';
		}
	}
}

int main(void)
{

	FIELD_LIST campos;

	while(1)
	{
		int f,c;
		scanf("%d %d",&f,&c);
		if(f==0 && c==0)
		break;
		if(f==0 || c==0 || c>100)	
		{
			printf("Datos invalidos, vuelva a ingresar!!!\n");
			continue;
		}
		
		campos.Add(f,c);
		campos.Fill_current();
	}
	
	campos.Resolve_Fields();
	campos.Display_Fields();
	printf("\n");

	return(0);
}

