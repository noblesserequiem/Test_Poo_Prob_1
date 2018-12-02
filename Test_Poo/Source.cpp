#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

class Lista;
class Produs {
private:
	char *producator,*rezolutia;
	int pret;
	Produs *urm;
public:
	Produs(char *prod, char *rez, int pt)
	{
		producator = new char(sizeof(strlen(prod) + 1));
		rezolutia = new char(sizeof(strlen(rez) + 1));
		strcpy(producator, prod);
		strcpy(rezolutia, rez);
		pret = pt;
	}
	virtual void afisare()
	{
		cout << "--------------------" << endl;
		cout << "Producator:" << producator<<endl;
		cout << "Rezolutia: " << rezolutia << endl;
		cout << "Pret: " << pret<<endl;
	
	}
	friend class Lista;
};

class Rama_Foto:public Produs {
private:
	int diagonala;
	char *format_afisare;
public:
	Rama_Foto(char prod[30], char rez[30], int pt, int diag, char form_afis[30]) :Produs(prod, rez, pt)
	{
		format_afisare = new char(sizeof(strlen(form_afis) + 1));
		strcpy(format_afisare, form_afis);
		diagonala = diag;
	}
	void afisare()
	{
		Produs::afisare();
		cout << "Diagonala: " << diagonala << endl;
		cout << "Format Afisare: " << format_afisare << endl;
	}
	friend class Lista;
};

class Aparat:public Produs {
private:
	char *tip_aparat,*tip_senzor;
public:
	Aparat(char prod[30], char rez[30], int pt, char *tp_ap, char tp_senz[30]) :Produs(prod, rez, pt)
	{
		tip_aparat = new char(sizeof(strlen(tp_ap) + 1));
		tip_senzor = new char(sizeof(strlen(tp_senz) + 1));
		strcpy(tip_aparat, tp_ap);
		strcpy(tip_senzor, tp_senz);
	}
	void afisare()
	{
		Produs::afisare();
		cout << "Tip aparat: " << tip_aparat << endl;
		cout << "Tip senzor: " << tip_senzor << endl;
	}
	friend class Lista;

};
class Lista {
public:
	Produs *head;
	void adaugare(Produs *a);
	void afisare();
	void stergere(char *producator);
};
void Lista::adaugare(Produs *a)
{
	Produs *p;
	p = head;
	if (p == NULL)
	{
		head = a;
	}
	else
	{
		if (strcmp(a->producator, head->producator) < 0)
		{
			a->urm = head;
			head = a;
		}
		else
		{
			while (p->urm != NULL && strcmp(p->urm->producator, a->producator) < 0)
				p = p->urm;
			a->urm = p->urm;
			p->urm = a;
		}
	}
}

void Lista::afisare()
{
	Produs *p;
	p = head;
	while (p != NULL)
	{
		p->afisare();
		p = p->urm;
	}
}
class MyException 
{
public:
	char errorcode[30];
	int pret;
	MyException()
	{
		*errorcode = 0;
		pret = 0;
	}
	MyException(char *er, int pt)
	{
		strcpy(errorcode, er);
		pret = pt;

	}
};
void Lista::stergere(char *producator)
{
	Produs *p;
	Produs *aux;
	p = head;
	if (strcmp(head->producator, producator) == 0)
	{
		aux = head;
		head = head->urm;
		free(aux);
	}
	else
	{
		while (p->urm != NULL && strcmp(p->urm->producator, producator) != 0)
			p = p->urm;
		if (strcmp(p->urm->producator, producator) == 0)
		{
			aux = p->urm;
			p->urm = p->urm->urm;
			free(aux);
		}
	}
	
}
void introducere(Lista &l, int produs)
{
	Produs *p;
	char Producator[30];
	char Rezolutie[30];
	int Pret;
	cout << "Producator:";
	cin >> Producator;
	cout << "Rezolutie:";
	cin >> Rezolutie;
	try {
		cout << "Pret:";
		cin >> Pret;

		if (Pret < 0)
		{
			throw MyException((char*)"Pretul este negativ", Pret);
		}
	}
	catch(MyException e)
	{
		do {
			cout << e.errorcode << endl;
			cin >> Pret;
		} while (Pret < 0);
	}
	if (produs == 0)
	{
		int diagonala;
		char format_afisare[30];
		cout << "diagonala: ";
		cin >> diagonala;
		cout << "format afisare:";
		cin>> format_afisare;
		Rama_Foto *r=new Rama_Foto(Producator,Rezolutie,Pret,diagonala,format_afisare);
		p = r;
		l.adaugare(p);
		
	}
	if (produs == 1)
	{
		char Tip_aparat[30], Tip_senzor[30];
		cout << "Tip aparat: ";
		try 
		{
			cin >> Tip_aparat;
			if (strcmp(Tip_aparat, "compact") != 0 && strcmp(Tip_aparat, "dslr") != 0)
			{
				throw Tip_aparat;

			}
		}
		catch (char Tip_ap[30])
		{
			do 
			{
				cout << "Introdu aparat DSLR/compact" << endl;
				cin >> Tip_aparat;
			} while (strcmp(Tip_aparat, "compact") != 0 && strcmp(Tip_aparat, "dslr") != 0);
		}
		cout << "Tip senzor: ";
		cin>> Tip_senzor;
		Aparat *ap = new Aparat(Producator, Rezolutie, Pret, Tip_aparat, Tip_senzor);
		p = ap;
		l.adaugare(p);
	}

}
int main()
{
	Lista l;
	l.head = NULL;
	int opt;
	cout << "1.Introducere Rama\n2.Introducere Aparat\n3.Afisare\n4.Sterge producator\n5.Exit\n";
	do {
		cin >> opt;
		switch(opt)
		{
		case 1:
		{
			introducere(l, 0);
			break;
		}
		case 2:
		{
			introducere(l, 1);
			break;
		}
		case 3:
		{
			l.afisare();
			break;
		}
		case 4:
		{
			char producator[30];
			cin >> producator;
			l.stergere(producator);
			break;
		}
		case 5:
		{
			exit(0);
		}
		default: 
		{
			break;
		}
		}
		
	} while (opt != 5);
	_getch();
	return 0;
}