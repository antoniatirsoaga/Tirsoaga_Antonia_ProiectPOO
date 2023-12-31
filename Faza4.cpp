#include <iostream>
#include <fstream>
#include <string>

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
			for (int i = 0; i < this->nrRafturi; i++)
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
		aux.nrRafturi = this->nrRafturi + f.nrRafturi;
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

	friend istream& operator>>(istream& in, Frigider& f) {
		cout << "Model: ";
		in >> f.model;
		cout << "Pret: ";
		in >> f.pret;
		cout << "Numar de rafturi: ";
		in >> f.nrRafturi;
		if (f.dimensiuneRaft != NULL)
			delete[]f.dimensiuneRaft;
		f.dimensiuneRaft = new float[f.nrRafturi];
		for (int i = 0; i < f.nrRafturi; i++) {
			cout << "Dimensiunea raftului " << i + 1 << ": ";
			in >> f.dimensiuneRaft[i];
		}
		cout << endl;
		return in;
	}

	void scriereBinarFrigider(fstream& f) {
		int lungimeModel = model.length();
		f.write((char*)&lungimeModel, sizeof(int));
		f.write(model.c_str(), lungimeModel + 1);
		f.write((char*)&this->pret, sizeof(float));
		f.write((char*)&this->nrRafturi, sizeof(int));
		for (int i = 0; i < nrRafturi; i++) {
			f.write((char*)&this->dimensiuneRaft[i], sizeof(float));
		}
	}

	void citireBinarFrigider(fstream& f) {
		int lungime;
		f.read((char*)&lungime, sizeof(int));
		char* bufferModel = new char[lungime + 1];
		f.read(bufferModel, lungime + 1);
		this->model = bufferModel;
		delete[]bufferModel;
		f.read((char*)&this->pret, sizeof(float));
		f.read((char*)&this->nrRafturi, sizeof(int));
		if (this->dimensiuneRaft != NULL) {
			delete[]this->dimensiuneRaft;
		}
		this->dimensiuneRaft = new float[nrRafturi];
		for (int i = 0; i < nrRafturi; i++)
		{
			f.read((char*)&this->dimensiuneRaft[i], sizeof(float));
		}
	}


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
	{
		out << "Dimensiuni rafturi: ";
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

	MasinaSpalat(int anNou, string model, int RPM, int nrVanzari, string* luniVanzari) :anFabricatie(anNou) {
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
			delete[]this->luniVanzari;
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

	friend istream& operator>>(istream& in, MasinaSpalat& m) {
		cout << "Model: ";
		in >> m.model;
		cout << "RPM: ";
		in >> m.RPM;
		cout << "Numar vanzari: ";
		in >> m.nrVanzari;
		if (m.luniVanzari != NULL)
			delete[]m.luniVanzari;
		m.luniVanzari = new string[m.nrVanzari];
		for (int i = 0; i < m.nrVanzari; i++) {
			cout << "A " << i + 1 << "-a luna de vanzare: ";
			in >> m.luniVanzari[i];
		}
		cout << endl;
		return in;
	}

	friend ostream& operator<<(ostream& out, const MasinaSpalat& m) {
		out << "Model: " << m.model << endl;
		out << "RPM: " << m.RPM << endl;
		out << "Numar vanzari: " << m.nrVanzari << endl;
		if (m.nrVanzari == 0)
			out << "Nicio vanzare";
		else
		{
			out << "Lunile in care s-au vandut: ";
			for (int i = 0; i < m.nrVanzari; i++)
				out << m.luniVanzari[i] << ", ";
		}
		out << endl;
		out << "An fabricatie: " << m.anFabricatie << endl;
		out << "TVA: " << m.TVA << endl;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, MasinaSpalat& m);

};
float MasinaSpalat::TVA = 0.19;

ifstream& operator>>(ifstream& in, MasinaSpalat& m) {
	in >> m.model;
	in >> m.RPM;
	in >> m.nrVanzari;
	if (m.luniVanzari != NULL)
		delete[]m.luniVanzari;
	m.luniVanzari = new string[m.nrVanzari];
	for (int i = 0; i < m.nrVanzari; i++)
		in >> m.luniVanzari[i];
	return in;

}

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
		cout << "Putere: ";
		in >> mic.putere;
		cout << "Numar de modele: ";
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

	friend ostream& operator<<(ostream& out, const Microunde& mic) {
		out << "ID: " << mic.id << endl;
		out << "Brand: " << mic.brand << endl;
		out << "Putere: " << mic.putere << endl;
		out << "Numar de modele: " << mic.nrModele << endl;
		if (mic.nrModele == 0)
			out << "Nu exista modele";
		else
		{
			out << "Preturi: ";
			for (int i = 0; i < mic.nrModele; i++)
				out << mic.pret[i] << ", ";
		}
		out << endl;
		out << "Garantie: " << mic.garantie << " ani" << endl;
		return out;
	}


	friend float calculPretMediu(const Microunde& micro);

	friend ifstream& operator>>(ifstream& in, Microunde& m) {
		in >> m.brand;
		in >> m.putere;
		in >> m.nrModele;
		if (m.pret != NULL)
			delete[]m.pret;
		m.pret = new float[m.nrModele];
		for (int i = 0; i < m.nrModele; i++) {
			in >> m.pret[i];
		}
		return in;
	}

	friend ofstream& operator<<(ofstream& out, const Microunde& mic) {
		out << endl << mic.brand << endl << mic.putere << endl << mic.nrModele << endl;
		for (int i = 0; i < mic.nrModele; i++)
			out << mic.pret[i] << " ";
		out << endl;
		return out;
	}

	void scriereBinarMicrounde(fstream& f) {
		int lungimeBrand = brand.length();
		f.write((char*)&lungimeBrand, sizeof(int));
		f.write(brand.c_str(), lungimeBrand + 1);
		f.write((char*)&this->putere, sizeof(int));
		f.write((char*)&this->nrModele, sizeof(int));
		for (int i = 0; i < nrModele; i++) {
			f.write((char*)&this->pret[i], sizeof(float));
		}
	}

	void citireBinarMicrounde(fstream& f) {
		int lungime;
		f.read((char*)&lungime, sizeof(int));
		char* bufferBrand = new char[lungime + 1];
		f.read(bufferBrand, lungime + 1);
		this->brand = bufferBrand;
		delete[]bufferBrand;
		f.read((char*)&this->putere, sizeof(int));
		f.read((char*)&this->nrModele, sizeof(int));
		if (this->pret != NULL) {
			delete[]this->pret;
		}
		this->pret = new float[nrModele];
		for (int i = 0; i < nrModele; i++)
		{
			f.read((char*)&this->pret[i], sizeof(float));
		}
	}


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


class MagazinElectrocasnice {
private:
	const int id;
	int nrFrigidere;
	Frigider* frigider;
	MasinaSpalat masinaSpalat;
	Microunde microunde;
	string numeMagazin;
public:
	MagazinElectrocasnice() :id(0) {
		this->numeMagazin = "-";
		this->frigider = NULL;

	}

	MagazinElectrocasnice(int id, string numeMagazin, int nrFrigidere, Frigider* frigider, MasinaSpalat masinaSpalat, Microunde microunde) :id(id) {
		this->numeMagazin = numeMagazin;
		this->masinaSpalat = masinaSpalat;
		this->microunde = microunde;
		this->nrFrigidere = nrFrigidere;
		this->frigider = new Frigider[nrFrigidere];
		for (int i = 0; i < nrFrigidere; i++) {
			this->frigider[i] = frigider[i];
		}
	}

	~MagazinElectrocasnice() {
		if (this->frigider != NULL) {
			delete[]this->frigider;
		}
	}

	MagazinElectrocasnice& operator=(const MagazinElectrocasnice& me) {
		if (this != &me) {
			if (this->frigider != NULL) {
				delete[]this->frigider;
			}
			this->numeMagazin = me.numeMagazin;
			this->masinaSpalat = me.masinaSpalat;
			this->microunde = me.microunde;
			this->nrFrigidere = me.nrFrigidere;
			this->frigider = new Frigider[nrFrigidere];
			for (int i = 0; i < nrFrigidere; i++) {
				this->frigider[i] = me.frigider[i];
			}
		}
		return *this;
	}

	int getId() {
		return this->id;
	}

	void setNumeMagazin(string numeMagazin) {
		this->numeMagazin = numeMagazin;
	}

	string getNumeMagazin() {
		return this->numeMagazin;
	}

	void setNrFrigidere(int nrFrigidere, Frigider* frigider) {
		if (nrFrigidere > 0) {
			this->nrFrigidere = nrFrigidere;
			if (this->frigider != NULL) {
				delete[]this->frigider;
			}
			this->frigider = new Frigider[nrFrigidere];
			for (int i = 0; i < nrFrigidere; i++)
				this->frigider[i] = frigider[i];
		}
	}

	int getNrFrigidere() {
		return this->nrFrigidere;
	}

	Frigider* getFrigider() {
		return this->frigider;
	}

	void setMasinaSpalat(const MasinaSpalat& masinaSpalat) {
		this->masinaSpalat = masinaSpalat;
	}

	MasinaSpalat getMasinaSpalat() {
		return this->masinaSpalat;
	}

	void setMicrounde(const Microunde& microunde) {
		this->microunde = microunde;
	}

	Microunde getMicrounde() {
		return this->microunde;
	}


	void afisare() {
		cout << "Magazinul de electrocasnice cu id-ul " << id << " se numeste " << numeMagazin << ". Acesta are in stoc " << nrFrigidere << " frigidere. Frigiderele sunt: " << endl;
		if (nrFrigidere == 0)
			cout << "-";
		else
			for (int i = 0; i < nrFrigidere; i++)
				cout << frigider[i];
		cout << "Mai are de asemenea microunde " << endl << microunde << endl;
		cout << " si masini de spalat " << endl << masinaSpalat << endl;

	}

	Frigider& operator[](int index) {
		if (index >= 0 && index < nrFrigidere) {
			return this->frigider[index];
		}
	}

	bool operator>(MagazinElectrocasnice magazin) {
		return this->nrFrigidere > magazin.nrFrigidere;
	}

	friend ostream& operator<<(ostream& out, const MagazinElectrocasnice& me) {
		out << "ID:" << me.id << endl;
		out << "Nume magazin: " << me.numeMagazin << endl;
		out << endl << "Masina de spalat: " << me.masinaSpalat << endl;
		out << "Cuptor cu microunde: " << me.microunde << endl;
		out << "Numar frigidere: " << me.nrFrigidere << endl;
		if (me.nrFrigidere == 0)
			out << "Niciun frigider.";
		else {
			out << "Frigiderele: ";
			for (int i = 0; i < me.nrFrigidere; i++)
				out << me.frigider[i] << "\n";
		}

		return out;
	}

	friend istream& operator>>(istream& in, MagazinElectrocasnice& me) {
		cout << "Nume magazin: ";
		in >> me.numeMagazin;
		cout << "Masina de spalat: ";
		in >> me.masinaSpalat;
		cout << "Cuptor cu microunde: ";
		in >> me.microunde;
		cout << "Numar frigidere: ";
		in >> me.nrFrigidere;
		if (me.frigider != NULL) {
			delete[]me.frigider;
		}
		me.frigider = new Frigider[me.nrFrigidere];
		for (int i = 0; i < me.nrFrigidere; i++) {
			cout << "Frigiderul " << i + 1 << ": ";
			in >> me.frigider[i];
		}
		cout << endl;
		return in;
	}

	friend ofstream& operator<<(ofstream& out, const MagazinElectrocasnice& me) {
		out << me.numeMagazin << endl << me.masinaSpalat << endl << me.microunde << endl << me.nrFrigidere << endl;
		for (int i = 0; i < me.nrFrigidere; i++)
			out << me.frigider[i] << " ";
		return out;
	}


};

class FrigiderSmart :public Frigider {
private:
	char* numeTehnologie;
	int temperaturaMinima;
public:
	FrigiderSmart() :Frigider() {
		this->numeTehnologie = new char[strlen("Control temperatura de la distanta") + 1];
		strcpy_s(this->numeTehnologie, strlen("Control temperatura de la distanta") + 1, "Control temperatura de la distanta");
		this->temperaturaMinima = 0;
	}

	FrigiderSmart(int idNou, float pret, string model, int temperaturaMinima, const char* numeTehnologie) :Frigider(idNou, pret, model) {
		this->temperaturaMinima = temperaturaMinima;
		this->numeTehnologie = new char[strlen(numeTehnologie) + 1];
		strcpy_s(this->numeTehnologie, strlen(numeTehnologie) + 1, numeTehnologie);
	}

	FrigiderSmart(int idNou, float pret, string model, int nrRafturi, float* dimensiuneRaft, int temperaturaMinima, const char* numeTehnologie) :Frigider(idNou, pret, model, nrRafturi, dimensiuneRaft) {
		this->temperaturaMinima = temperaturaMinima;
		this->numeTehnologie = new char[strlen(numeTehnologie) + 1];
		strcpy_s(this->numeTehnologie, strlen(numeTehnologie) + 1, numeTehnologie);
	}

	FrigiderSmart(const FrigiderSmart& fs) :Frigider(fs) {
		this->temperaturaMinima = fs.temperaturaMinima;
		this->numeTehnologie = new char[strlen(fs.numeTehnologie) + 1];
		strcpy_s(this->numeTehnologie, strlen(fs.numeTehnologie) + 1, fs.numeTehnologie);

	}

	friend ostream& operator<<(ostream& out, const FrigiderSmart& fs) {
		out << endl;
		out << (Frigider)fs;
		out << "Nume tehnologie: " << fs.numeTehnologie << " ";
		out << "\nTemperatura minima: " << fs.temperaturaMinima << " grade Celsius." << endl;
		return out;

	}

	FrigiderSmart operator=(const FrigiderSmart& fs) {
		if (this != &fs) {
			Frigider::operator=(fs);
			this->temperaturaMinima = fs.temperaturaMinima;
			if (this->numeTehnologie) {
				delete[]this->numeTehnologie;
			}
			this->numeTehnologie = new char[strlen(fs.numeTehnologie) + 1];
			strcpy_s(this->numeTehnologie, strlen(fs.numeTehnologie) + 1, fs.numeTehnologie);
		}
		return *this;
	}

	~FrigiderSmart() {
		if (this->numeTehnologie) {
			delete[]this->numeTehnologie;
		}
	}

	void setNumeTehnologie(const char* numeTehnologie) {
		if (strlen(numeTehnologie) > 0) {
			if (this->numeTehnologie) {
				delete[]this->numeTehnologie;
			}
			this->numeTehnologie = new char[strlen(numeTehnologie) + 1];
			strcpy_s(this->numeTehnologie, strlen(numeTehnologie) + 1, numeTehnologie);	
		}
	}

	const char* getNumeTehnologie() {
		return this->numeTehnologie;
	}

	void setTemperaturaMinima(int temperaturaMinima) {
		this->temperaturaMinima = temperaturaMinima;
	}

	int getTemperaturaMinima() {
		return this->temperaturaMinima;
	}


};


class MasinaSpalatCuUscare :public MasinaSpalat {
private:
	char* tipUscare;
	int capacitate;
public:
	MasinaSpalatCuUscare() :MasinaSpalat(2023, "Bosch", 1600) {
		this->capacitate = 4;
		this->tipUscare = new char[strlen("Uscare cu aer cald")+1];
		strcpy_s(this->tipUscare, strlen("Uscare cu aer cald") + 1, "Uscare cu aer cald");
	}

	MasinaSpalatCuUscare(int capacitate, const char* tipUscare) :MasinaSpalat() {
		this->capacitate = capacitate;
		this->tipUscare = new char[strlen(tipUscare) + 1];
		strcpy_s(this->tipUscare, strlen(tipUscare) + 1, tipUscare);
	}

	MasinaSpalatCuUscare(int anNou, string model, int RPM, int nrVanzari, string* luniVanzari, int capacitate, const char* tipUscare) :MasinaSpalat(anNou, model, RPM, nrVanzari, luniVanzari) {
		this->capacitate = capacitate;
		this->tipUscare = new char[strlen(tipUscare) + 1];
		strcpy_s(this->tipUscare, strlen(tipUscare) + 1, tipUscare);
	}

	MasinaSpalatCuUscare(const MasinaSpalatCuUscare& msu):MasinaSpalat(msu) {
		this->capacitate = msu.capacitate;
		this->tipUscare = new char[strlen(msu.tipUscare) + 1];
		strcpy_s(this->tipUscare, strlen(msu.tipUscare) + 1, msu.tipUscare);
	}

	MasinaSpalatCuUscare operator=(const MasinaSpalatCuUscare& msu) {
		if (this != &msu) {
			MasinaSpalat::operator=(msu);
			this->capacitate = msu.capacitate;
			if (this->tipUscare) {
				delete[]this->tipUscare;
			}
			this->tipUscare = new char[strlen(msu.tipUscare) + 1];
			strcpy_s(this->tipUscare, strlen(msu.tipUscare) + 1, msu.tipUscare);
		}
		return *this;
	}

	~MasinaSpalatCuUscare() {
		if (this->tipUscare) {
			delete[]this->tipUscare;
		}
	}

	void setTipUscare(const char* tipUscare) {
		if (strlen(tipUscare) > 0) {
			if (this->tipUscare) {
				delete[]this->tipUscare;
			}
			this->tipUscare = new char[strlen(tipUscare) + 1];
			strcpy_s(this->tipUscare, strlen(tipUscare) + 1, tipUscare);
		}
	}

	const char* getTipUscare() {
		return this->tipUscare;
	}

	void setCapacitate(int capacitate) {
		this->capacitate = capacitate;
	}

	int getCapacitate() {
		return this->capacitate;
	}


	friend ostream& operator<<(ostream& out, const MasinaSpalatCuUscare& msu) {
		out << endl;
		out << (MasinaSpalat)msu;
		out << "Tip uscare: " << msu.tipUscare << " ";
		out << "\nCapacitate de incarcare: " << msu.capacitate << " kg." << endl;
		return out;

	}

	friend istream& operator>>(istream& in, MasinaSpalatCuUscare& msu) {
		in >> (MasinaSpalat&)msu;
		cout << "Capacitate de incarcare: ";
		in >> msu.capacitate;
		if (msu.tipUscare) {
			delete[]msu.tipUscare;
		}
		cout << "Tip uscare: ";
		char buffer[30];
		in >> buffer;
		msu.tipUscare = new char[strlen(buffer) + 1];
		strcpy_s(msu.tipUscare, strlen(buffer) + 1, buffer);
		return in;
	}

};



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
	frigider5 = frigider2;
	frigider5.afisare();

	Frigider rezultat = frigider3 + frigider4;
	rezultat.afisare();

	Frigider fPretAdaugat = frigider2 + 100;
	fPretAdaugat.afisare();

	cout << frigider3 << endl;

	/*int nrFrigidere;
	cout << "Introduceti numarul de frigidere: ";
	cin >> nrFrigidere;
	Frigider* vectorFrigidere = new Frigider[nrFrigidere];

	for (int i = 0; i < nrFrigidere; i++) {
		cout << "Detalii frigider " << i + 1 <<":" <<endl;
		cin >> vectorFrigidere[i];
	}

	for (int i = 0; i < nrFrigidere; i++) {
		cout << vectorFrigidere[i] << endl;
	}

	delete[]vectorFrigidere;*/


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

	MasinaSpalat masina3(2023, "Samsung", 1300, 5, luniVanz);
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

	cout << masina3.getLuniVanzari(3) << endl;
	masina3.afisare();
	cout << endl;

	MasinaSpalat masina5;
	masina5 = masina2;
	masina5.afisare();

	masina3 += masina4;
	masina3.afisare();

	MasinaSpalat masina6;
	masina6 = 200 + masina2;
	masina6.afisare();

	if (masina6 > masina3)
		cout << "Masina 6 are mai multe RPM decat masina 3" << endl;
	else
		cout << "Masina 3 are mai multe RPM decat masina 6" << endl;
	cout << "Masina 3: " << masina3.getRPM() << " RPM" << endl;
	cout << "Masina 6: " << masina6.getRPM() << " RPM" << endl;

	afisareVanzari(masina3);
	cout << endl;

	/*int nrMasini;
	cout << "Inroduceti numarul de masini de spalat: ";
	cin >> nrMasini;

	MasinaSpalat* vectormasini = new MasinaSpalat[nrMasini];
	for (int i = 0; i < nrMasini; i++) {
		cout << "Detalii masina de spalat " << i + 1 << ": "<<endl;
		cin >> vectormasini[i];
	}

	for (int i = 0; i < nrMasini; i++) {
		cout << vectormasini[i] << endl;
	}

	delete[]vectormasini;*/


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
	micro5 = micro2;
	micro5.afisare();

	/*cin >> micro3;
	cout << micro3 << endl;

	float pretMediu = calculPretMediu(micro3);
	cout << "Pretul mediu al microundelor este: " << pretMediu << endl;
	cout << "Primul microunde are pretul de: "<<micro3[0] << endl;*/

	//int nrMicro;
	//cout << "Introduceti numarul de cuptoare cu microunde: ";
	//cin >> nrMicro;
	//Microunde* vectorMicro=new Microunde[nrMicro];
	//for (int i = 0; i < nrMicro; i++) {
	//	cout << "Detalii cuptor cu microunde " << i + 1 << ": " << endl;
	//	cin >> vectorMicro[i];
	//}

	//for (int i = 0; i < nrMicro; i++) {
	//	cout << vectorMicro[i]<<endl;
	//}
	//
	//delete[]vectorMicro;

	//int nrLinii, nrColoane;
	//cout << "Introduceti numarul de linii a matricei de obiecte a clasei Frigider: ";
	//cin >> nrLinii;
	//cout<<"Introduceti numarul de coloane a matricei de obiecte a clasei Frigider: ";
	//cin >> nrColoane;
	//Frigider** matriceF = new Frigider* [nrLinii];
	//for (int i = 0; i < nrLinii; i++) {
	//	matriceF[i] = new Frigider[nrColoane];
	//}

	//for (int i = 0; i < nrLinii; i++) {
	//	for (int j = 0; j < nrColoane; j++) {
	//		cout << "Introduceti detaliile frigiderului [" << i + 1 << "][" << j + 1 << "]:\n";
	//		cin >> matriceF[i][j];

	//	}
	//}

	//for (int i = 0; i < nrLinii; i++) {
	//	for (int j = 0; j < nrColoane; j++) {
	//		cout << "Frigider [" << i + 1 << "][" << j + 1 << "]:\n";
	//		cout << matriceF[i][j];
	//	}
	//}

	MagazinElectrocasnice me1;
	me1.afisare();

	Frigider* frigidere = new Frigider[2]{ frigider3,frigider4 };
	MagazinElectrocasnice me2(1, "Flanco", 2, frigidere, masina3, micro2);
	me2.afisare();

	MagazinElectrocasnice me3;
	me3 = me2;
	me3.afisare();

	cout << "Id magazin: " << me2.getId() << endl;
	me2.setNumeMagazin("Altex");
	cout << "Nume magazin: " << me2.getNumeMagazin() << endl;
	me2.setMasinaSpalat(masina2);
	cout << "Masina de spalat: " << endl << me2.getMasinaSpalat() << endl;
	me2.setMicrounde(micro3);
	cout << "Cuptorul cu microunde: " << endl << me2.getMicrounde() << endl;
	Frigider* vectF = new Frigider[3]{ frigider2,frigider3,frigider4 };
	me2.setNrFrigidere(3, vectF);
	cout << "Frigiderul 1: " << endl << me2.getFrigider()[0] << endl;
	cout << "Frigiderul 2: " << endl << me2.getFrigider()[1] << endl;
	cout << "Frigiderul 3: " << endl << me2.getFrigider()[2] << endl;

	if (me1 > me2) {
		cout << "Magazinul 1 are mai multe frigidere decat magazinul 2" << endl;
	}
	else {
		cout << "Magazinul 2 are mai multe frigidere decat magazinul 1" << endl;
	}
	cout << endl;

	delete[]vectF;


	/*ifstream m("MasiniDeSpalat.txt", ios::in);
	MasinaSpalat m1;
	m >> m1;
	cout << m1;
	m.close();*/

	/*ofstream mic("microunde.txt", ios::out);
	cin >> micro2;
	mic << micro2;
	mic.close();*/

	/*ifstream mic2("microunde.txt", ios::in);
	Microunde mCitit;
	mic2 >> mCitit;
	cout << mCitit;
	mic2.close();*/

	//Frigider f1;
	//cin >> f1;
	//fstream fisfrigider("frigidere.bin", ios::binary | ios::out);
	//f1.scriereBinarFrigider(fisfrigider);
	//fisfrigider.close();

	/*fstream fis2frigider("frigidere.bin", ios::binary | ios::in);
	Frigider fCitit;
	fCitit.citireBinarFrigider(fis2frigider);
	cout << fCitit;
	fis2frigider.close();*/

	/*Microunde mic1;
	cin >> mic1;
	fstream fismic1("Microunde.bin", ios::out | ios::binary);
	mic1.scriereBinarMicrounde(fismic1);
	fismic1.close();*/

	/*fstream fismic2("Microunde.bin", ios::in | ios::binary);
	Microunde micCitit;
	micCitit.citireBinarMicrounde(fismic2);
	cout << micCitit;
	fismic2.close();*/

	/*ofstream fismag("magazinElectrocasnice.txt", ios::out);
	MagazinElectrocasnice magazin1;
	cin >> magazin1;
	fismag << magazin1;
	fismag.close();*/

	FrigiderSmart fs1;
	cout << fs1;

	FrigiderSmart fs2(10, 2499.99, "Gorenje", 3, "Ecran tactil integrat pe usa");
	cout << fs2;

	fs2.setNumeTehnologie("Ajustare temperatura din aplicatie mobila");
	cout << "\nNume tehnologie actualizat: " << fs2.getNumeTehnologie() << endl;
	fs2.setTemperaturaMinima(2);
	cout << "Temperatura minima actualizata: " << fs2.getTemperaturaMinima() << endl;
	cout << fs2;

	float* dimRafturi;
	dimRafturi = new float[4];
	dimRafturi[0] = 68.55;
	dimRafturi[1] = 80.58;
	dimRafturi[2] = 71.43;
	dimRafturi[3] = 75;
	FrigiderSmart fs3(11, 2350, "Whirlpool", 4, dimRafturi, 4, "Monitorizare stoc alimente");
	cout << fs3;

	
	FrigiderSmart fs4(fs3);
	cout << fs4;

	FrigiderSmart fs5;
	fs5 = fs3;
	cout << fs5;

	MasinaSpalatCuUscare msu1;
	cout << msu1;

	MasinaSpalatCuUscare msu2(5, "Uscare prin condensare");
	cout << msu2;

	string* luniMSU;
	luniMSU = new string[4]{ "ianuarie","martie","septembrie","decembrie"};
	MasinaSpalatCuUscare msu3(2022, "Whirlpool", 1400, 4, luniMSU, 8, "Uscare cu pompa de caldura");
	cout << msu3;

	msu3.setTipUscare("Uscare cu aer cald");
	cout << "\nTip uscare actualizat: " << msu3.getTipUscare() << endl;
	msu3.setCapacitate(9);
	cout << "Capacitate de incarcare actualizata: " << msu3.getCapacitate() << endl;

	MasinaSpalatCuUscare msu4;
	cin >> msu4;
	cout << msu4;

	MasinaSpalatCuUscare msu5(msu3);
	cout << msu5;

	MasinaSpalatCuUscare msu6;
	msu6 = msu3;
	cout << msu6;
}
