#include <iostream>

using namespace std;


class Frigider {
private:
	const int id;
	float pret;
	string model;
	int nrRafturi;
	int* dimensiuneRaft;
	static string clasaEnergetica;
public:
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

	Frigider(const Frigider& frigider) :id(frigider.id) {
		this->pret = frigider.pret;
		this->model = frigider.model;
		this->nrRafturi = frigider.nrRafturi;
		this->dimensiuneRaft = new int[nrRafturi];
		for (int i = 0; i < nrRafturi; i++)
			this->dimensiuneRaft[i] = frigider.dimensiuneRaft[i];
	}

	~Frigider() {
		if (this->dimensiuneRaft != NULL) {
			delete[]this->dimensiuneRaft;
		}
	}

	void afisare()
	{
		cout << "Frigiderul " << model << " are id-ul " << id << ",se incadreaza in clasa energetica " << clasaEnergetica << ", costa " << pret << " lei. Frigiderul are " << nrRafturi << " rafturi de dimensiunile: ";
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

	static string getclasaEnergetica() {
		return Frigider::clasaEnergetica;
	}

	int getId() {
		return this->id;
	}

	float getPret() {
		return this->pret;
	}

	string getModel() {
		return this->model;
	}

	int getNrRafturi() {
		return this->nrRafturi;
	}

	int* getDimensiuneRaft() {
		return this->dimensiuneRaft;
	}


	void setPret(float pret) {
		if (pret >= 0)
			this->pret = pret;
		else cout<<"Pretul nu poate fi negativ";
	}

	void setModel(string model) {
		if (model.length() > 1)
			this->model = model;
	}

	void setNrRafturi(int nrRafturi, int* dimensiune) {
		if (nrRafturi > 0) {
			this->nrRafturi = nrRafturi;
			if (this->dimensiuneRaft != NULL) {
				delete[]this->dimensiuneRaft;
			}
			dimensiuneRaft = new int[this->nrRafturi];
			for (int i = 0; i < nrRafturi; i++)
				this->dimensiuneRaft[i] = dimensiune[i];
		}
	}

	int getDimensiuneRaft(int index) {
		if (index >= 0 && index <= nrRafturi) {
			return this->dimensiuneRaft[index];
		}
	}

};
string Frigider::clasaEnergetica = "A+";

class MasinaSpalat {
private:
	const int anFabricatie;
	static float TVA;
	string model;
	int RPM;
	int nrVanzari;
	string* luniVanzari;
public:
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

	MasinaSpalat(const MasinaSpalat& masina) :anFabricatie(masina.anFabricatie){
		this->model=masina.model;
		this->RPM = masina.RPM;
		this->nrVanzari = masina.nrVanzari;
		this->luniVanzari = new string[nrVanzari];
		for (int i = 0; i < nrVanzari; i++)
			this->luniVanzari[i] = masina.luniVanzari[i];

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

	static float getTVA() {
		return MasinaSpalat::TVA;
	}
	
	int getAnFabricatie() {
		return this->anFabricatie;
	}

	void setModel(string model) {
		if (model.length() > 1)
			this->model = model;
	}

	string getModel() {
		return this->model;
	}

	void setRPM(int RPM) {
		if (RPM > 0) 
			this->RPM=RPM;
	}

	int getRPM() {
		return this->RPM;
	}

	void setNrVanzari(int nrVanzari, string* luni) {
		if (nrVanzari > 0) {
			this->nrVanzari = nrVanzari;
			if (this->luniVanzari != NULL)
				delete[]luniVanzari;
		}
		luniVanzari = new string[this->nrVanzari];
		for (int i = 0; i < nrVanzari; i++)
			this->luniVanzari[i] = luni[i];
	}

	string getLuniVanzari(int index) {
		if (index >= 0 && index <= nrVanzari)
			return this->luniVanzari[index];
	}

};
float MasinaSpalat::TVA = 0.19;

class Microunde {
private:
	const int id;
	static int garantie;
	string brand;
	int nrModele;
	int putere;
	float* pret;
public:
	Microunde() :id(1) {
		this->nrModele= 0;
		this->putere = 0;
		this->pret = NULL;
		this->brand = "-";
	
	}

	Microunde(int idNou,string brand,int putere) :id(idNou) {
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

	Microunde(const Microunde& micro) :id(micro.id) {
		this->brand = micro.brand;
		this->nrModele = micro.nrModele;
		this->putere = micro.putere;
		this->pret = new float[nrModele];
		for (int i = 0; i < nrModele; i++)
			this->pret[i] = micro.pret[i];

	}

	~Microunde() {
		if (this->pret!=NULL)
			delete[]this->pret;
	}

	void afisare() {
		cout << "Firma "<<id<<" de brand " << brand << " are cuptoare cu microunde cu puterea de " << putere << " W. Are " << nrModele << " modele. Preturile cuptoarelor cu microunde sunt: ";
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

	int getId() {
		return this->id;
	}

	static int getGarantie(){
		return Microunde::garantie;
	}

	void setBrand(string brand) {
		if (brand.length() > 1)
			this->brand = brand;
	}

	string getBrand() {
		return this->brand;
	}

	void setPutere(int putere) {
		if (putere > 0)
			this->putere = putere;
	}

	int getPutere() {
		return this->putere;
	}

	void setNrModele(int nrModele, float* preturi) {
		if (nrModele > 0)
			this->nrModele = nrModele;
		if (pret != NULL)
			delete[]pret;
		pret = new float[this->nrModele];
		for (int i = 0; i < nrModele; i++)
			this->pret[i] = preturi[i];
	}

	float getPret(int index) {
		if (index >= 0 && index <= nrModele)
			return this->pret[index];
	}
};
int Microunde::garantie = 2;

void main() {
	Frigider::setclasaEnergetica("C");

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

	Frigider frigider4(frigider3);
	frigider4.afisare();

	cout << endl<<frigider3.getclasaEnergetica() << endl;
	cout << frigider1.getId()<<endl;
	frigider3.setModel("Bosch");
	cout << frigider3.getModel() << endl;
	frigider3.setPret(799.99);
	cout << frigider3.getPret()<<endl;

	int* vectorFrigider = new int[2] {43, 39};
	frigider3.setNrRafturi(2, vectorFrigider);
	frigider3.afisare();
	delete[]vectorFrigider;
	cout << frigider3.getDimensiuneRaft(0)<<endl;


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
	
	MasinaSpalat masina4(masina3);
	masina3.afisare();

	cout<<endl<<masina3.getTVA()<<endl;
	cout << masina3.getAnFabricatie() << endl;

	masina3.setModel("Electrolux");
	cout << masina3.getModel()<<endl;

	masina3.setRPM(1800);
	cout << masina3.getRPM()<<endl;

	string* vectorMasina=new string[6]{ "ianuarie","martie","mai","iunie","august","noiembire" };
	masina3.setNrVanzari(6, vectorMasina);
	masina3.afisare();

	delete[]vectorMasina;

	cout << masina3.getLuniVanzari(3)<<endl;



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

	Microunde micro3(3,"LG", 750);
	micro3.afisare();

	Microunde micro4(micro2);
	micro4.afisare();

	cout << endl << micro2.getId() << endl;
	cout << micro2.getGarantie() << endl;

	micro2.setBrand("Toshiba");
	cout << micro2.getBrand() << endl;

	micro2.setPutere(1000);
	cout << micro2.getPutere() << endl;

	float* vectorMicrounde = new float[3] {255.99, 421, 519.99};
	micro2.setNrModele(3, vectorMicrounde);
	micro2.afisare();

	delete[]vectorMicrounde;

	cout << micro2.getPret(2)<<endl;


}	
