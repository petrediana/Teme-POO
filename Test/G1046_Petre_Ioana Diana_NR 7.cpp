// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstring>
using namespace std;

class Folder {
private:
	const int idUnic;
	char *denumire;
	int nrFisiere;
	float *dimensiuneFisiere;
	static int prefix; // initializat -1

public:
	Folder();
	Folder(int v_idUnic, char *v_denumire, int v_nrFisiere, float* v_dimensiuneFisiere);
	Folder(const Folder &copie);
	~Folder();

	Folder &operator =(const Folder &folder);
	friend ostream &operator<<(ostream &out, Folder &folder);
	float &operator[](int index);
	bool operator !();
	Folder &operator +=(float numar);


	char* getDenumire();
	int getNrfisiere();
	int getIdUnic();
	float getDimensiuneFolder();
	static int getPrefix();

	void setDimensiuniFisier(int dim, float *vectFis);
	void setPrefix();
};

int Folder::prefix = -1; //initializat

int main()
{
	Folder f1;
	cout << f1.getDenumire() << endl;
	
	float dimensiuniFisiere[]{ 22.45, 14.4, 2.7, 25.9 };
	char numeF2[100];
	strcpy(numeF2, "Documente");

	Folder f2(12, numeF2, 4, dimensiuniFisiere);
	cout << endl << f2.getNrfisiere();

	Folder f3 = f2;
	cout << endl << f3.getIdUnic();

	f1 = f3;
	f1.setPrefix();
	f3.setPrefix();
	cout << endl << f1.getDimensiuneFolder();

	float vectorFisiere[]{ 2.4, 3.5 };
	f3.setDimensiuniFisier(2, vectorFisiere);

	//Folder::prefix = 0;
	//am inlocuit asta cu o functie set.. in cazul in care egalez 2 obiecte inseamna ca au acelasi nume
	
	cout << f1;
	

	cout << endl << f3[1];

	f3 += 10.9;
	//cout << endl << f3.getDimensiuneFolder(); -> afis 16,8 e ok
	cout << f3;

	if (!f1)
		cout << endl << "Folderul f1 contine fisiere";
	else
		cout << endl << "Folderul f1 nu contine fisiere";
	
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

Folder::Folder():idUnic(1) {
	
	this->denumire = new char[strlen("Folder Nou") + 1];
	strcpy(this->denumire, "Folder Nou");

	this->nrFisiere = 0;
	this->dimensiuneFisiere = NULL;
}

Folder::Folder(int v_idUnic, char *v_denumire, int v_nrFisiere, float* v_dimensiuneFisiere):idUnic(v_idUnic) {
	this->denumire = new char[strlen(v_denumire) + 1];
	if (v_denumire != NULL) {
		strcpy(this->denumire, v_denumire);
	}

	if (v_nrFisiere > 0)
		this->nrFisiere = v_nrFisiere;

	this->dimensiuneFisiere = new float[this->nrFisiere];
	if (v_dimensiuneFisiere != NULL) {
		for (int i = 0; i < this->nrFisiere; i++)
			this->dimensiuneFisiere[i] = v_dimensiuneFisiere[i];
	}
}

Folder::Folder(const Folder &copie) :idUnic(copie.idUnic) {
	this->denumire = new char[strlen(copie.denumire) + 1];
	if (copie.denumire != NULL)
		strcpy(this->denumire, copie.denumire);

	if (copie.nrFisiere > 0)
		this->nrFisiere = copie.nrFisiere;

	this->dimensiuneFisiere = new float[this->nrFisiere];
	if (copie.dimensiuneFisiere != NULL) {
		for (int i = 0; i < this->nrFisiere; i++)
			this->dimensiuneFisiere[i] = copie.dimensiuneFisiere[i];
	}
}

Folder::~Folder() {
	if (this->denumire != NULL)
		delete[] this->denumire;

	if (this->dimensiuneFisiere != NULL)
		delete[] this->dimensiuneFisiere;
}

char *Folder::getDenumire() {
	return this->denumire;
}

int Folder::getNrfisiere() {
	return this->nrFisiere;
}

Folder &Folder::operator=(const Folder &folder) {
	this->denumire = new char[strlen(folder.denumire) + 1];
	if (folder.denumire != NULL)
		strcpy(this->denumire, folder.denumire);

	if (folder.nrFisiere > 0)
		this->nrFisiere = folder.nrFisiere;

	this->dimensiuneFisiere = new float[folder.nrFisiere];
	if (folder.dimensiuneFisiere != NULL) {
		for (int i = 0; i < folder.nrFisiere; i++)
			this->dimensiuneFisiere[i] = folder.dimensiuneFisiere[i];
	}

	return *this;
}

int Folder::getIdUnic() {
	return (-1 * this->idUnic);
}

float Folder::getDimensiuneFolder() {
	float sum = 0;
	for (int i = 0; i < this->nrFisiere; i++)
		sum += this->dimensiuneFisiere[i];

	return sum;
}

void Folder::setDimensiuniFisier(int dim, float *vectFis) {
	if (dim > 0)
		this->nrFisiere = dim;

	this->dimensiuneFisiere = new float[this->nrFisiere];
	if (vectFis != NULL) {
		for (int i = 0; i < this->nrFisiere; i++)
			this->dimensiuneFisiere[i] = vectFis[i];
	}
}

ostream &operator<<(ostream &out, Folder &folder) {
	out << "\n\tAfisare folder:";
	//out << "\nId Unic: " << folder.idUnic;
	
	if(folder.getPrefix() == 0)
		out << "\nDenumire: 0" << folder.denumire;
	else
		out << "\nDenumire: " << folder.denumire;

	out << "\nNr fisiere: " << folder.nrFisiere;
	out << "\nDimensiunea totala: " << folder.getDimensiuneFolder() << " MB";

	out << "\n";

	return out;
}

float &Folder::operator[](int index) {
	if ((index >= 0) && (index < this->nrFisiere) && (this->dimensiuneFisiere != NULL))
		return this->dimensiuneFisiere[index];
}

bool Folder::operator!() {
	if (this->nrFisiere != 0 && this->nrFisiere > 0)
		return true;
	else
		return false;
}

Folder &Folder::operator+=(float numar) {
	float *aux;
	int i;
	aux = new float[this->nrFisiere + 1];
	for (i = 0; i < this->nrFisiere; i++)
		aux[i] = this->dimensiuneFisiere[i];

	aux[this->nrFisiere++] = numar;
	delete[] this->dimensiuneFisiere;
	this->dimensiuneFisiere = new float[this->nrFisiere];
	for (i = 0; i < this->nrFisiere; i++)
		this->dimensiuneFisiere[i] = aux[i];

	delete[]aux;

	return *this;
}

int Folder::getPrefix() {
	return Folder::prefix;
}

void Folder::setPrefix() {
	Folder::prefix = 0;
}