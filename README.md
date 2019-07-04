#pragma once
#include "Columna.h"
#include "Fila.h"
#include<iomanip>
//ola k ase
//ajjhsadb
using namespace System;
class DF {
	vector<Columna*> vectorC;
	vector<Fila*> vectorF;
public:
	DF() {}
	DF(vector<Columna*> vectorC, vector<Fila*> vectorF) : vectorC(vectorC), vectorF(vectorF) {}
	DF(ifstream& fin, char sep = ',') {
		cargarDeArchivo(fin, sep);
	}
	~DF() {
		for (auto col : vectorC) if (col) {
			delete col; col = nullptr;
		};
		for (auto fila : vectorF) if (fila) {
			delete fila; fila = nullptr;
		};
	}

	std::vector<Columna*>& GetVectorC() { return this->vectorC; }
	std::vector<Fila*>& GetVectorF() { return this->vectorF; }

	void cargarDeArchivo(ifstream& fin, char sep = ',')
	{
		bool nombresLeidos = false;
		string line, word;
		while (getline(fin, line))
		{
			if (nombresLeidos) vectorF.push_back(new Fila(vectorF.size(), vectorC));
			stringstream s(line);
			int j = 0;
			while (getline(s, word, sep))
			{
				if (!nombresLeidos) { vectorC.push_back(new Columna(word)); }
				else
				{
					vectorC[j++]->Añadir(word);
				}
			}
			if (!nombresLeidos) nombresLeidos = true;
		}
	}

	void guardarEnArchivo(ofstream& fout, char sep = ',')
	{
		for (auto col : vectorC) fout << col->getIdentificador() << ",";
		for (auto fila : vectorF)
		{
			fout << "\n";
			for (string s : fila->getValues()) fout << s << sep;
		}
	}
	void imprimir()
	{

		printf("\n\t\t    ==> LISTADO DE DATA FRAME <==\n");

		printf("\n ---------------------------------------------------------------------------------------------------------------------------------\n");
		Console::ForegroundColor = ConsoleColor::DarkRed;
		for (auto col : vectorC) cout  << right << col->getIdentificador()<<" ";
		Console::ForegroundColor = ConsoleColor::White;
		printf("\n ---------------------------------------------------------------------------------------------------------------------------------\n");

		for (auto fila : vectorF)
		{
			cout << "-";
			for (auto col : vectorC) cout << right << col->getData()[fila->id()]<<" ";
			cout << endl << endl;
		}

		printf(" -------------------------------------------------------------------------------------------------------------------------------------\n");

	}

};
