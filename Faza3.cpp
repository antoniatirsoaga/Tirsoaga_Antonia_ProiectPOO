#include <iostream>

using namespace std;


class Frigider {
private:
	const int id;
	float pret;
	string model;
	int nrRafturi;
	float* dimensiuneRaft;
	static string clasaEnergetica;
public:
	Frigider() :id(1) {
		this->pret = NULL;
		this->model = "-";
		this->nrRafturi = 0;
		this->dimensiuneRaft = NULL;
	}

	Frigider(int idNou, float pret, string model) :id(idNou) {
		this->pret = pret;
		this->model = model;
		this->nrRafturi = 0;
		this->dimensiuneRaft = NULL;
	}

	Frigider(int idNou, float pret, string model, int nrRafturi, float* dimensiuneRaft) :id(idNou) {
		this->pret = pret;
		this->model = model;
		this->nrRafturi = nrRafturi;
		this->dimensiuneRaft = new float[nrRafturi];
		for (int i = 0; i < nrRafturi; i++)
		{
			this->dimensiuneRaft[i] = dimensiuneRaft[i];
		}

	}

	Frigider(const Frigider& frigider) :id(frigider.id) {
		this->pret = frigider.pret;
		this->model = frigider.model;
		this->nrRafturi = frigider.nrRafturi;
		this->dimensiuneRaft = new float[nrRafturi];
		for (int i = 0; i < nrRafturi; i++)
			this->dimensiuneRaft[i] = frigider.dimensiuneRaft[i];
	}

	Frigider& operator=(const Frigider& f) {
		if (this != &f) {
			this->pret = f.pret;
			this->model = f.model;
			this->nrRafturi = f.nrRafturi;
			if (this->dimensiuneRaft != NULL) {
				delete[]this->dimensiuneRaft;
			}
			this->dimensiuneRaft = new float[this->nrRafturi];
			for (int i= 0; i < this->nrRafturi; i++)
				this->dimensiuneRaft[i] = f.dimensiuneRaft[i];

		}
		return *this;
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

	float* getDimensiuneRaft() {
		return this->dimensiuneRaft;
	}


	void setPret(float pret) {
		if (pret >= 0)
			this->pret = pret;
		else cout << "Pretul nu poate fi negativ";
	}

	void setModel(string model) {
		if (model.length() > 1)
			this->model = model;
	}

	void setNrRafturi(int nrRafturi, float* dimensiune) {
		if (nrRafturi > 0) {
			this->nrRafturi = nrRafturi;
			if (this->dimensiuneRaft != NULL) {
				delete[]this->dimensiuneRaft;
			}
			dimensiuneRaft = new float[this->nrRafturi];
			for (int i = 0; i < nrRafturi; i++)
				this->dimensiuneRaft[i] = dimensiune[i];
		}
	}

	int getDimensiuneRaft(int index) {
		if (index >= 0 && index <= nrRafturi) {
			return this->dimensiuneRaft[index];
		}
	}

	Frigider operator+(Frigider f) {
		Frigider aux = *this;
		aux.nrRafturi=this->nrRafturi + f.nrRafturi;
		if (aux.dimensiuneRaft != NULL)
			delete[]aux.dimensiuneRaft;
		aux.dimensiuneRaft = new float[aux.nrRafturi];
		for (int i = 0; i < this->nrRafturi; i++)
			aux.dimensiuneRaft[i] = this->dimensiuneRaft[i];
		for (int i = this->nrRafturi; i < aux.nrRafturi; i++)
			aux.dimensiuneRaft[i] = f.dimensiuneRaft[i - this->nrRafturi];
		return aux;

	}

	Frigider operator+(float pretPlus) const {
		Frigider aux = *this;
		aux.pret = this->pret + pretPlus;
		return aux;
	}

	friend ostream& operator<<(ostream& out, const Frigider& f);

};
string Frigider::clasaEnergetica = "A+";

ostream& operator<<(ostream& out, const Frigider& f) {
	out << "ID: " << f.id << endl;
	out << "Pret: " << f.pret << endl;
	out << "Model: " << f.model << endl;
	out << "Numar rafturi: " << f.nrRafturi << endl;
	if (f.nrRafturi == 0)
		out << "Niciun raft";
	else
	{		out << "Dimensiuni rafturi: ";
	for (int i = 0; i < f.nrRafturi; i++)
		out << f.dimensiuneRaft[i] << ", ";
}
	out << endl;
	out << "Clasa energetica: " << f.clasaEnergetica << endl;
	return out;
}

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

	MasinaSpalat(int anNou, string model, int RPM) :anFabricatie(anNou) {
		this->model = model;
		this->RPM = RPM;
		this->nrVanzari = 0;
		this->luniVanzari = NULL;
	}

	MasinaSpalat(int anNou,string model, int RPM, int nrVanzari, string* luniVanzari) :anFabricatie(anNou) {
		this->model = model;
		this->RPM = RPM;
		this->nrVanzari = nrVanzari;
		this->luniVanzari = new string[nrVanzari];
		for (int i = 0; i < nrVanzari; i++) {
			this->luniVanzari[i] = luniVanzari[i];
		}
	}

	MasinaSpalat(const MasinaSpalat& masina) :anFabricatie(masina.anFabricatie) {
		this->model = masina.model;
		this->RPM = masina.RPM;
		this->nrVanzari = masina.nrVanzari;
		this->luniVanzari = new string[nrVanzari];
		for (int i = 0; i < nrVanzari; i++)
			this->luniVanzari[i] = masina.luniVanzari[i];

	}

	MasinaSpalat& operator=(const MasinaSpalat& m) {
		if (this != &m) {
			this->model = m.model;
			this->RPM = m.RPM;
			this->nrVanzari = m.nrVanzari;
			if (this->luniVanzari != NULL)
				delete[]this->luniVanzari;
			this->luniVanzari = new string[this->nrVanzari];
			for (int i = 0; i < nrVanzari; i++)
				this->luniVanzari[i] = m.luniVanzari[i];
		}
		return *this;
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
			this->RPM = RPM;
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

	MasinaSpalat operator+=(const MasinaSpalat& m) {
		int auxNrVanzari = this->nrVanzari + m.nrVanzari;
		string* auxLuniVanzari = new string[auxNrVanzari];
		for (int i = 0; i < this->nrVanzari; i++)
			auxLuniVanzari[i] = this->luniVanzari[i];
		for (int i = this->nrVanzari; i < auxNrVanzari; i++)
			auxLuniVanzari[i] = m.luniVanzari[i - this->nrVanzari];
		this->nrVanzari = auxNrVanzari;
		if (this->luniVanzari != NULL)
			delete[]this -> luniVanzari;
		this->luniVanzari = auxLuniVanzari;
		return *this;
	}

	friend MasinaSpalat operator+(int RPM, const MasinaSpalat& m) {
		MasinaSpalat aux = m;
		aux.RPM = m.RPM + RPM;
		return aux;
	}

	bool operator>(MasinaSpalat m) {
		return this->RPM > m.RPM;
	}

	friend void afisareVanzari(const MasinaSpalat& m);
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
		this->nrModele = 0;
		this->putere = 0;
		this->pret = NULL;
		this->brand = "-";

	}

	Microunde(int idNou, string brand, int putere) :id(idNou) {
		this->putere = putere;
		this->brand = brand;
		this->nrModele = nrModele;
		this->pret = NULL;
		;
	}

	Microunde(int idNou, string brand, int nrModele, int putere, float* pret) :id(idNou) {
		this->brand = brand;
		this->putere = putere;
		this->nrModele = nrModele;
		this->pret = new float[nrModele];
		for (int i = 0; i < nrModele; i++)
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

	Microunde& operator=(const Microunde& m) {
		if (this != &m) {
			this->brand = m.brand;
			this->nrModele = m.nrModele;
			this->putere = m.putere;
			if (this->pret != NULL)
				delete[]this->pret;
			this->pret = new float[this->nrModele];
			for (int i = 0; i < nrModele; i++)
				this->pret[i] = m.pret[i];
		}
		return *this;
	}

	~Microunde() {
		if (this->pret != NULL)
			delete[]this->pret;
	}

	void afisare() {
		cout << "Firma " << id << " de brand " << brand << " are cuptoare cu microunde cu puterea de " << putere << " W. Are " << nrModele << " modele. Preturile cuptoarelor cu microunde sunt: ";
		if (nrModele == 0)
			cout << "-";
		else
			for (int i = 0; i < nrModele; i++)
				cout << this->pret[i] << ", ";
		cout << "Garantia lor este de " << garantie << " ani" << endl;
	}

	static void setGarantie(int garantie) {
		Microunde::garantie = garantie;
	}

	int getId() {
		return this->id;
	}

	static int getGarantie() {
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

	float& operator[](int index) {
		if (index >= 0 && index < this->nrModele)
			return this->pret[index];
	}

	friend istream& operator>>(istream& in, Microunde& mic) {
		cout << "Brand: ";
		in >> mic.brand;
		cout << "\nPutere: ";
		in >> mic.putere;
		cout << "\nNumar de modele: ";
		in >> mic.nrModele;
		if (mic.pret != NULL)
			delete[]mic.pret;
		mic.pret = new float[mic.nrModele];
		for (int i = 0; i < mic.nrModele; i++) {
			cout << "Pretul modelului " << i + 1 << ": ";
			in >> mic.pret[i];
		}
		cout << endl;
		return in;
	}

	friend ostream& operator<<(ostream& out, const Microunde mic) {
		out << "Firma " << mic.id << " de brand " << mic.brand << " are cuptoare cu microunde cu puterea de " << mic.putere << " W. Are " << mic.nrModele << " modele. Preturile cuptoarelor cu microunde sunt: ";
		if (mic.nrModele == 0)
			out << "-";
		else
			for (int i = 0; i < mic.nrModele; i++)
				out << mic.pret[i] << ", ";
		out << "Garantia lor este de " << garantie << " ani" << endl;
		return out;
	}

	friend float calculPretMediu(const Microunde& micro);


};
int Microunde::garantie = 2;



void afisareVanzari(const MasinaSpalat& m) {
	cout << "Numarul de vanzari al masinii de spalat " << m.model << " este: " << m.nrVanzari << endl;
	cout << "Lunile in care s-au vandut produsele: ";
	if (m.nrVanzari == 0)
		cout << "Nicio vanzare";
	else
		for (int i = 0; i < m.nrVanzari; i++) {
			cout << m.luniVanzari[i] << ", ";

		}
}

float calculPretMediu(const Microunde& micro) {
	if (micro.nrModele == 0)
		return 0;
	float s = 0;
	for (int i = 0; i < micro.nrModele; i++)
		s = s + micro.pret[i];
	return s / micro.nrModele;
}


void main() {
	Frigider::setclasaEnergetica("C");

	Frigider frigider1;
	frigider1.afisare();

	float* dimensiuni;
	dimensiuni = new float[3];
	dimensiuni[0] = 67.25;
	dimensiuni[1] = 84.58;
	dimensiuni[2] = 35.43;

	Frigider frigider2(2, 1200.25, "Vortex 5DSL44F");
	frigider2.afisare();

	Frigider frigider3(3, 780.66, "Heinner F76SD", 3, dimensiuni);
	frigider3.afisare();

	Frigider frigider4(frigider3);
	frigider4.afisare();

	cout << endl << frigider3.getclasaEnergetica() << endl;
	cout << frigider1.getId() << endl;
	frigider3.setModel("Bosch");
	cout << frigider3.getModel() << endl;
	frigider3.setPret(799.99);
	cout << frigider3.getPret() << endl;

	float* vectorFrigider = new float[2] {43.12, 39.41};
	frigider3.setNrRafturi(2, vectorFrigider);
	frigider3.afisare();
	delete[]vectorFrigider;
	cout << frigider3.getDimensiuneRaft(0) << endl;

	Frigider frigider5;
	frigider5.operator=(frigider2);
	frigider5.afisare();

	Frigider rezultat = frigider3 + frigider4;
	rezultat.afisare();

	Frigider fPretAdaugat = frigider2 + 100;
	fPretAdaugat.afisare();

	cout << frigider3 << endl;

	MasinaSpalat::setTVA(0.21);

	MasinaSpalat masina1;
	masina1.afisare();

	MasinaSpalat masina2(2020, "Whirlpool", 1000);
	masina2.afisare();

	string* luniVanz = new string[5];
	luniVanz[0] = "ianuarie";
	luniVanz[1] = "martie";
	luniVanz[2] = "iunie";
	luniVanz[3] = "iulie";
	luniVanz[4] = "octombrie";

	MasinaSpalat masina3(2023,"Samsung", 1300, 5, luniVanz);
	masina3.afisare();

	MasinaSpalat masina4(masina3);
	masina4.afisare();

	cout << endl << masina3.getTVA() << endl;
	cout << masina3.getAnFabricatie() << endl;

	masina3.setModel("Electrolux");
	cout << masina3.getModel() << endl;

	masina3.setRPM(1800);
	cout << masina3.getRPM() << endl;

	string* vectorMasina = new string[6]{ "ianuarie","martie","mai","iunie","august","noiembire" };
	masina3.setNrVanzari(6, vectorMasina);

	delete[]vectorMasina;

	cout << masina3.getLuniVanzari(3)<<endl ;
	masina3.afisare();
	cout << endl;

	MasinaSpalat masina5;
	masina5.operator=(masina2);
	masina5.afisare();

	masina3+=masina4;
	masina3.afisare();

	MasinaSpalat masina6;
	masina6 = 200 + masina2;
	masina6.afisare();

	if (masina6 > masina3)
		cout << "Masina 6 are mai multe RPM decat masina 3"<<endl;
	else
		cout << "Masina 3 are mai multe RPM decat masina 6"<<endl;
	cout << "Masina 3: " << masina3.getRPM()<<" RPM"<<endl;
	cout << "Masina 6: " << masina6.getRPM()<<" RPM"<<endl;

	afisareVanzari(masina3);


	Microunde::setGarantie(3);

	Microunde micro1;
	micro1.afisare();

	float* preturi = new float[4];
	preturi[0] = 250.75;
	preturi[1] = 420;
	preturi[2] = 310.15;
	preturi[3] = 199.99;

	Microunde micro2(2, "Samsung", 4, 800, preturi);
	micro2.afisare();

	Microunde micro3(3, "LG", 750);
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

	cout << micro2.getPret(2) << endl;

	Microunde micro5;
	micro5.operator=(micro2);
	micro5.afisare();

	cin >> micro3;
	cout << micro3 << endl;

	float pretMediu = calculPretMediu(micro3);
	cout << "Pretul mediu al microundelor este: " << pretMediu << endl;
	cout << "Al 3-lea microunde are pretul de: "<<micro3[2] << endl;


}
