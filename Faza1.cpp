#include <iostream>

using namespace std;


class Frigider {
public:
	const int id;
	float pret;
	string model;
	int nrRafturi;
	int* dimensiuneRaft;
	static string clasaEnergetica;

	Frigider() :id(1) {
		this->pret = NULL;
		this->model = "-";
		this->nrRafturi=0;
		this->dimensiuneRaft = NULL;
	}

	Frigider(int idNou,float pret,string model):id(idNou) {
		this->pret = pret;
		this->model = model;
		this->nrRafturi=0;
		this->dimensiuneRaft=NULL;
	}

	Frigider(int idNou,float pret,string model, int nrRafturi, int* dimensiuneRaft):id(idNou) {
		this->pret = pret;
		this->model = model;
		this->nrRafturi = nrRafturi;
		this->dimensiuneRaft = new int[nrRafturi];
		for (int i = 0; i < nrRafturi; i++)
		{
			this->dimensiuneRaft[i] = dimensiuneRaft[i];
		}
		
	}

	~Frigider() {
		if (this->dimensiuneRaft != NULL) {
			delete[]this->dimensiuneRaft;
		}
	}

	void afisare()
	{
		cout << "Frigiderul " << model << " are id-ul " << id << ",se inacdreaza in clasa energetica" << clasaEnergetica << ", costa " << pret << " lei. Frigiderul are " << nrRafturi << " de dimensiunile: ";
		if (nrRafturi == 0)
			cout << "-";
		else
			for (int i = 0; i < nrRafturi; i++)
				cout << this->dimensiuneRaft[i] << ", ";
		cout << endl;
	}

	static void setclasaEnergetica(string clasaEnergetica) {
		Frigider::clasaEnergetica = clasaEnergetica;
	}


};
string Frigider::clasaEnergetica = "A+";

class MasinaSpalat {
public:
	const int anFabricatie;
	static float TVA;
	string model;
	int RPM;
	int nrVanzari;
	string* luniVanzari;

	MasinaSpalat() :anFabricatie(2019) {
		this->model = "-";
		this->RPM = 0;
		this->nrVanzari = 0;
		this->luniVanzari = NULL;
	}

	MasinaSpalat(int anNou,string model, int RPM) :anFabricatie(anNou) {
		this->model = model;
		this->RPM = RPM;
		this->nrVanzari = 0;
		this->luniVanzari = NULL;
	}

	MasinaSpalat(string model, int RPM, int nrVanzari, string* luniVanzari) :anFabricatie(2022) {
		this->model = model;
		this->RPM = RPM;
		this->nrVanzari = nrVanzari;
		this->luniVanzari = new string[nrVanzari];
		for (int i = 0; i < nrVanzari; i++) {
			this->luniVanzari[i] = luniVanzari[i];
		}
	}

	~MasinaSpalat() {
		if (this->luniVanzari != NULL)
			delete[]this->luniVanzari;
	}

	void afisare() {
		cout << "Masina de spalat " << model << " fabricata in anul " << anFabricatie << " are " << RPM << " rotatii pe minut. Numarul vanzarilor a fost de: " << nrVanzari << " in lunile: " << endl;
		if (nrVanzari == 0)
			cout << "-";
		else
			for (int i = 0; i < nrVanzari; i++)
				cout << this->luniVanzari[i] << ",";
		cout << "TVA-ul este de " << TVA * 100 << "%." << endl;
	}

	static void setTVA(float TVA) {
		MasinaSpalat::TVA = TVA;
	}

};
float MasinaSpalat::TVA = 0.19;

class Microunde {
public:
	const int id;
	static int garantie;
	string brand;
	int nrModele;
	int putere;
	float* pret;

	Microunde() :id(1) {
		this->nrModele= 0;
		this->putere = 0;
		this->pret = NULL;
		this->brand = "-";
	
	}

	Microunde(string brand,int putere) :id(2) {
		this->putere = putere;
		this->brand = brand;
		this->nrModele = nrModele;
		this->pret = NULL;
		;
	}

	Microunde(int idNou,string brand,int nrModele,int putere,float* pret):id(idNou){
		this->brand = brand;
		this->putere = putere;
		this->nrModele = nrModele;
		this->pret = new float[nrModele];
		for (int i = 0; i < nrModele;i++)
			this->pret[i] = pret[i];
	}

	~Microunde() {
		if (this->pret!=NULL)
			delete[]this->pret;
	}

	void afisare() {
		cout << "Firma "<<brand << " are cuptoare cu microunde cu puterea de " << putere<<" W. Are "<<nrModele << " modele. Preturile cuptoarelor cu microunde sunt: ";
		if (nrModele == 0)
			cout << "-";
		else
			for (int i = 0; i < nrModele; i++)
				cout << this->pret[i]<<", ";
		cout << "Garantia lor este de " << garantie << " ani" << endl;
	}

	static void setGarantie(int garantie) {
		Microunde::garantie = garantie;
	}
};
int Microunde::garantie = 2;

void main() {
	Frigider frigider1;
	frigider1.afisare();

	int* dimensiuni;
	dimensiuni = new int[3];
	dimensiuni[0] = 67;
	dimensiuni[1] = 84;
	dimensiuni[2] = 35;

	Frigider frigider2(2, 1200.25 ,"Vortex 5DSL44F");
	frigider2.afisare();

	Frigider frigider3(3,780.66,"Heinner F76SD",3,dimensiuni );
	frigider3.afisare();

	MasinaSpalat::setTVA(0.21);

	MasinaSpalat masina1;
	masina1.afisare();

	MasinaSpalat masina2(2020,"Whirlpool", 1000);
	masina2.afisare();

	string* luniVanz = new string[5];
	luniVanz[0] = "ianuarie";
	luniVanz[1] = "martie";
	luniVanz[2] = "iunie";
	luniVanz[3] = "iulie";
	luniVanz[4] = "octombrie";

	MasinaSpalat masina3("Samsung",1300,5,luniVanz);
	masina3.afisare();
	

	Microunde::setGarantie(3);

	Microunde micro1;
	micro1.afisare();

	float* preturi = new float[4];
	preturi[0] = 250.75;
	preturi[1] = 420;
	preturi[2] = 310.15;
	preturi[3] = 199.99;

	Microunde micro2(2,"Samsung", 4, 800, preturi);
	micro2.afisare();

	Microunde micro3("LG", 750);
	micro3.afisare();

	

}	