#include<iostream>

using namespace std;

#pragma once
//bst
/* 
#include <iostream>
#include <functional>
 
using namespace std;
 
class Tree {
private:
    struct Node {
        float elem;
        Node* left;
        Node* right;
 
        Node(float elem, Node* left = nullptr, Node* right = nullptr) : elem(elem), left(left), right(right) {}
    };
    Node* root; //raiz
    int length;
    void destroy(Node* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
    void add(Node*&node, float elem) {
        if (node == nullptr)
            node = new Node(elem);
        else if (elem < node->elem)
            add(node->left, elem);
        else
            add(node->right, elem);
    }
    void InOrder(Node* node, function<void(float)> Bob_DoSomething) {
        if (node != nullptr) {
            InOrder(node->left, Bob_DoSomething);
            Bob_DoSomething(node->elem);
            InOrder(node->right, Bob_DoSomething);
        }
    }
    Node*& max(Node*& node) {
        if (node->right == nullptr)
            return node;
        return max(node->right);
    }
    Node*& min(Node*& node) {
        if (node->left == nullptr)
            return node;
        return min(node->left);
    }
public:
    Tree() :root(nullptr), length(0) {}
    ~Tree() { destroy(root); }
    int Length() { return length; }
    void Add(float elem) {
        add(root, elem);
        ++length;
    }
    void InOrder(function<void(float)> Bob_DoSomething) {
        InOrder(root, Bob_DoSomething);
    }
 
    float Max() {
        if (root != nullptr) {
            return max(root)->elem;
        }
        return -.1;
    }
    float Min() {
        if (root != nullptr) {
            return min(root)->elem;
        }
        return -1;
    }
    //Cuando queramos eliminar, buscamos el maximo hijo de la izquierda o el minimo de la derecha
 
    void Remove(float elem) {
        Node* parent;
        Node* aux = root;
        bool left;
        while (aux != nullptr && elem != aux->elem) {
            parent = aux;
            if (elem < aux->elem) {
                left = true;
                aux = aux->left;
            }
            else {
                left = false;
                aux = aux->right;
            }
        }
        if (aux == nullptr) return;
 
        Node* aux2;
        if (aux->left != nullptr) {
            Node*& cand = max(aux->left);
            aux2 = cand;
            cand = cand->right;
        }
        else if (aux->right != nullptr) {
            Node*& cand = min(aux->right);
            aux2 = cand;
            cand = cand->right;
        }
        else if (aux = root) {
            delete root;
            root = nullptr;
            return;
        }
        else {
            if (left) {
                delete parent->left;
                parent->left = nullptr;
            }
            else {
                delete parent->right;
                parent->right = nullptr;
            }
        }
    }
};
 


int main() {
    int n;
    float e;
    Tree* t = new Tree();
    auto prt = [](float a) {cout << a << " ";};
    cout << "Ingrese la cantidad de datos que desea leer ordenadamente: ";
    cin >> n;
 
    for (int i = 0; i < n; ++i)
    {
        cin >> e;
        t->Add(e);
    }
    remove(8.00);
    t->InOrder(prt);
 
    
    delete t;
   
} */ //bst //bst
//avl
/*
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

template<typename T, typename Comparable = T, T NONE = 0>
class AVLTree {
	struct Node {
		T     elem;
		int   h;
		int   n;
		Node* left;
		Node* right;

		Node(T elem)
			: elem(elem), left(nullptr), right(nullptr), h(0), n(1) {}
	};

	Node* root;

	std::function<Comparable(T)>  key;

	void destroy(Node* node) {
		if (node != nullptr) {
			destroy(node->left);
			destroy(node->right);
			delete node;
		}
	}
	Node* add(Node* node, T elem) {
		if (node == nullptr) {
			node = new Node(elem);
		}
		else {
			if (key(elem) > key(node->elem)) {
				node->right = add(node->right, elem);
			}
			else {
				node->left = add(node->left, elem);
			}
			node = balance(node);
		}
		return node;
	}
	void inorder(Node* node, std::function<void(T)> proc) {
		if (node != nullptr) {
			inorder(node->left, proc);
			proc(node->elem);
			inorder(node->right, proc);
		}
	}
	T find(Node* node, Comparable val) {
		if (node == nullptr) {
			return NONE;
		}
		if (val == key(node->elem)) {
			return node->elem;
		}
		else if (val < key(node->elem)) {
			return find(node->left, val);
		}
		else {
			return find(node->right, val);
		}
	}

	// BALANCEO 
	int height(Node* node) {
		return node == nullptr ? -1 : node->h;
	}
	int length(Node* node) {
		return node == nullptr ? 0 : node->n;
	}
	void updateHeight(Node* node) {
		int hl = height(node->left);
		int hr = height(node->right);
		node->h = 1 + (hl > hr ? hl : hr);
	}
	Node* rotRight(Node* node) {
		Node* aux = node->left;
		node->left = aux->right;
		aux->right = node;
		updateHeight(aux->right);
		updateHeight(aux);
		return aux;
	}
	Node* rotLeft(Node* node) {
		Node* aux = node->right;
		node->right = aux->left;
		aux->left = node;
		updateHeight(aux->left);
		updateHeight(aux);
		return aux;
	}
	Node* balance(Node* node) {
		int hl = height(node->left);
		int hr = height(node->right);
		if (hl - hr < -1) {
			if (height(node->right->left) > height(node->right->right)) {
				node->right = rotRight(node->right);
			}
			node = rotLeft(node);
		}
		else if (hl - hr > 1) {
			if (height(node->left->right) > height(node->left->left)) {
				node->left = rotLeft(node->left);
			}
			node = rotRight(node);
		}
		else {
			updateHeight(node);
		}
		return node;
	}

public:
	AVLTree(std::function<Comparable(T)>  key = [](T a) {return a; })
		: key(key), root(nullptr) {}
	~AVLTree() {
		destroy(root);
	}
	int height() {
		return height(root);
	}
	int length() {
		return length(root);
	}
	void add(T elem) {
		root = add(root, elem);
	}
	bool remove(Comparable val) {
		Node* aux = root;
		Node* parent;
		bool left;
		while (aux != nullptr) {
			if (val == key(aux->elem)) {
				break;
			}
			else {
				parent = aux;
				if (val < key(aux->elem)) {
					left = true;
					aux = aux->left;
				}
				else {
					left = false;
					aux = aux->right;
				}
			}
		}
		if (aux == nullptr) return false;
		if (aux->left == nullptr) {
			if (aux == root)  root = aux->right;
			else if (left)    parent->left = aux->right;
			else              parent->right = aux->right;
			delete aux;
		}
		else {
			Node* aux2 = aux->left;
			while (aux2->right != nullptr) {
				parent = aux2;
				aux2 = aux2->right;
			}
			if (aux2 == aux->left) {
				aux->left = aux2->left;
			}
			else {
				parent->right = aux2->left;
			}
			aux->elem = aux2->elem;
			delete aux2;
		}
		return true;
	}
	T find(Comparable val) {
		return find(root, val);
	}
	//list<T>* findAll(Comparable val) {
	  //return nullptr; // TODO!!
	//}

	void inorder(std::function<void(T)> proc) {
		inorder(root, proc);
	}
};



using namespace std;

enum Tipo { teoria, labcomp, labarq, cimlab, fablab, cubi };
class Salon {
	string nombre;
	Tipo tipo;
	int capacidad;

public:
	Salon(string nombre, Tipo tipo, int capacidad)
		: nombre(nombre), tipo(tipo), capacidad(capacidad) {}


	string getNombre() { return nombre; }
	Tipo getTipo() { return tipo; }
	int getCapacidad() { return capacidad; }
	void setnombre(string nombre) {
		this->nombre = nombre;
	}
	void settipo(Tipo tipo) {
		this->tipo = tipo;
	}
	void setcapacidad(int capacidad) {
		this->capacidad = capacidad;
	}
};
// https://repl.it/repls/UncomfortableSandyMozbot
int main() {
	typedef AVLTree<Salon*, string, nullptr> TNom;
	typedef AVLTree<Salon*, int, nullptr> TCap;

	auto knom = [](Salon* s) { return s->getNombre(); };
	auto kcap = [](Salon* s) { return s->getCapacidad(); };

	TNom* tnom = new TNom(knom);
	TCap* tcap = new TCap(kcap);

	auto px = [](Salon* s) {
		cout << "{"
			<< s->getNombre() << " "
			<< s->getTipo() << " "
			<< s->getCapacidad() << "}\n";
	};
	for (int i = 0; i < 1e6; ++i) {
		stringstream nom;
		nom << "U" << (char)('A' + rand() % 8)
			<< (1 + rand() % 8);
		Tipo tipo = (Tipo)(rand() % 6);
		int cap = 5 + rand() % 36;

		Salon* salon = new Salon(nom.str(), tipo, cap);
		//px(salon);
		tnom->add(salon);
		tcap->add(salon);
	}
	cout << tnom->height() << endl;
	//tnom->inorder(px);
	cout << tcap->height() << endl;
	//tcap->inorder(px);

	//px(t->find(labarq));

	delete tnom;
	delete tcap;
	return 0;
}*///avl

//sass
/*

#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;

class GraphNW {
	int n;
	vector<vector<char>> G;
	map<string, int> names;
	vector<string> revNames;

public:
	GraphNW(int n): n(n), G(n, vector<char>(n, 0)) {}
	void addNode(string node) {
		if (names.size() < n) {
			names[node] = names.size();
			revNames.push_back(node);
		}
	}
	void addEdge(string nodeU, string nodeV) {
		int u = names[nodeU];
		int v = names[nodeV];
		G[u][v] = 1;
		G[v][u] = 1;
	}
	// búsqueda en profundidad
	void dfs(string strs, string strt) {
		int s = names[strs];
		vector<bool> visited(n, false);
		vector<int> path(n, -1);
		visited[s] = true;
		dfs(s, visited, path);
		int fin = names[strt];
		while (fin >= 0) {
			cout << revNames[fin] << " <- ";
			fin = path[fin];
		}
		cout << "\n";
	}

private:
	void dfs(int s, vector<bool>& visited, vector<int>& path) {
		for (int v = 0; v < n; ++v) {
			if (G[s][v] != 0 && !visited[v]) {
				visited[v] = true;
				path[v] = s;
				dfs(v, visited, path);
			}
		}
	}
};


int main() {
  GraphNW* g = new GraphNW(20);
	g->addNode("Oradea");
	g->addNode("Zerind");
	g->addNode("Arad");
	g->addNode("Timisoara");
	g->addNode("Lugoj");
	g->addNode("Mehadia");
	g->addNode("Dobreta");
	g->addNode("Craiova");
	g->addNode("Rimnicu Vilcea");
	g->addNode("Sibiu");
	g->addNode("Fagaras");
	g->addNode("Pitesti");
	g->addNode("Bucharest");
	g->addNode("Giurgiu");
	g->addNode("Urziceni");
	g->addNode("Hirsova");
	g->addNode("Vaslui");
	g->addNode("Neamt");
	g->addNode("Iasi");
	g->addNode("Eforie");
	g->addEdge("Oradea", "Zerind");
	g->addEdge("Oradea", "Sibiu");
	g->addEdge("Zerind", "Arad");
	g->addEdge("Arad", "Sibiu");
	g->addEdge("Arad", "Timisoara");
	g->addEdge("Timisoara", "Lugoj");
	g->addEdge("Lugoj", "Mehadia");
	g->addEdge("Mehadia", "Dobreta");
	g->addEdge("Dobreta", "Craiova");
	g->addEdge("Craiova", "Rimnicu Vilcea");
	g->addEdge("Rimnicu Vilcea", "Sibiu");
	g->addEdge("Craiova", "Pitesti");
	g->addEdge("Rimnicu Vilcea", "Pitesti");
	g->addEdge("Sibiu", "Fagaras");
	g->addEdge("Fagaras", "Bucharest");
	g->addEdge("Pitesti", "Bucharest");
	g->addEdge("Bucharest", "Giurgiu");
	g->addEdge("Bucharest", "Urziceni");
	g->addEdge("Urziceni", "Hirsova");
	g->addEdge("Urziceni", "Vaslui");
	g->addEdge("Hirsova", "Eforie");
	g->addEdge("Vaslui", "Iasi");
	g->addEdge("Iasi", "Neamt");

	g->dfs("Arad", "Timisoara");

	return 0;
}



#include<iostream>
#include<queue>
using namespace std;

struct Vertice {
	string nomb;
	int num;
public:
	Vertice() {}
	Vertice(string nomb) :nomb(nomb), num(-1) {}
	Vertice(string nomb, int num) :nomb(nomb), num(num) {}
	bool igual_nombre(Vertice n) {
		return nomb == n.nomb;
	}
	//onomVer RETORNAR NOMBRE
	//PNOM    sET: CAM VERTICE
	//IGUAL   IGUALDAD ENTRE NOMBRES
	//oNUM  RETURN NUM
	//PNUM   SET:CAM VERTIC
};


class GrafoMatriz {

protected:
	int Max_V;
	int numVerts;
	Vertice* verts;		//arrays de vertices
	int** matAd;		//matriz de adyacencia
public:
	GrafoMatriz(int Max_V) :Max_V(Max_V) {

		verts = new Vertice[Max_V];
		matAd = new int* [Max_V];
		numVerts = 0;
		for (int i = 0; i < Max_V; i++)
			matAd[i] = new int[Max_V];
	}

	GrafoMatriz() {
		Max_V = 1;
		GrafoMatriz(Max_V);
	}

	void nuevo_Vertice(string nomb) {
		bool esta = num_Vertice(nomb) <= 0;
		if (esta == false) {
			Vertice v = Vertice(nomb, numVerts);
			verts[numVerts++] = v;   //se asigna a la lista
		}
	}
	// buscar vertice
	int num_Vertice(string nomb) {

		bool encontrado = false;
		int i;
		for (i = 0; (i < numVerts) && encontrado == false;) {
			encontrado = verts[i].igual_nombre(nomb);
			if (encontrado == false)i++;
		}
		return i < numVerts ? i : -1;
	}

	//existencia de arco 1 o 0
	void nuevoArco(int va, int vb) {
		if (va<0 || vb<0 || va>numVerts || vb>numVerts)return;
		matAd[va][vb] = 1;
	}


	void nuevoArco_Peso(int va, int vb, int peso) {
		if (va<0 || vb<0 || va>numVerts || vb>numVerts)return;
		matAd[va][vb] = peso;
	}

	//por nombre
	bool adyacente(string a, string b) {
		int va, vb;
		va = num_Vertice(a);
		vb = num_Vertice(b);
		if (va < 0 || vb < 0 || va >= numVerts || vb >= numVerts)return false;
		return matAd[va][vb] = 1;

	}
	//por numeros
	bool adyacente(int  va, int vb) {

		if (va < 0 || vb < 0 || va >= numVerts || vb >= numVerts)return;
		return matAd[va][vb] = 1;

	}

	Vertice* Get_ver() {
		return verts;
	}
};

enum Color { blanco, gris, negro };

void dfs(GrafoMatriz G, int v) {
	vector<bool>color(G.num_Vertice, blanco);
	color[v] = gris;
	for (auto& w : G.Get_ver[v])
		if (color[w] == blanco)
			dfs(G, w);
	color[v] = negro;
}

void bfs(GrafoMatriz G, int inicial) {
	vector<bool> color(G.num_Vertice, blanco);

	queue<int> q;
	q.push(inicial);
	color[inicial] = gris;

	while (!q.empty()) {
		int v = q.front(); q.pop();
		G.Get_ver()[v].num = negro;
		for (auto& w : G.Get_ver[v])
			if (color[w] == blanco) {
				q.push(w);
				color[w] = gris;
			}
	}

}

bool hasCycle(GrafoMatriz G, int v, int p = -1) {
	vector<bool> visited = (false, G.num_Vertice);
	visited[v] = true;
	bool cycle = false;
	for (auto& w : G.Get_ver[v])
		if (!visited[w])
			cycle |= hasCycle(w, v);
		else if (w != p)
			cycle = true;
	return cycle;

}

int main() {

	int i = 3;
	i |= 5;
	bool s = t;
	s |= false; cout << s << endl;

	system("pause");
	return 0;
}
