#include "header.h"
#include <iostream>
#include <fstream>
using namespace std;

void Graf::Node::Add_Node_Naprawiony(int dist, int nr_to, Node*& root)
{
	Node* nowy = new Node;
	nowy->dist = dist;
	nowy->nr_where = nr_to;
	nowy->next = root;
	root = nowy;  //utworzenie nowego 
}

void Graf::Node::Show_Naprawiony(Node* linking_)
{
	while (linking_)
	{
		std::cout << linking_->dist << "(" << linking_->nr_where << ")";  //wypisywanie drogi wraz z numerami wierzcholkow
		linking_ = linking_->next;
	}
	std::cout << std::endl;
}

Graf::Graf()
{
	fstream plik;
	plik.open("plikGraf.txt");
	int current_liczba;

	plik >> size;
	ls = new Node*[size];

	for (int i = 0; i < size; i++)
	{
		//ls[i] = new Node;
		ls[i] = NULL;
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			plik >> current_liczba;

			if (current_liczba != 0)
				ls[i]->Add_Node(ls[i], current_liczba, j);
		}
	}
}

void Graf::Show()
{
	for (int i = 0; i < size; i++)
	{
		ls[i]->Show(ls[i]);
	}
}

void Graf::Node::Add_Node(Node *& link_do_tablicy, int dist, int nr_to)  
{
	Add_Node_Naprawiony(dist, nr_to, link_do_tablicy);
}

void Graf::Node::Show(Node* root)
{
	Show_Naprawiony(root);
}

void Graf::lista::show(lista* root)
{
	while (root)
	{
		cout << root->wartosc << " ";

		root = root->next;
	}
}

Graf::lista* Graf::greedy()  //przechodzenie wszerz bfs zachlannie
{
	lista* Root_queue = NULL;
	Root_queue->add(0, Root_queue);
	lista* beenhere = NULL;
	beenhere->add(0, beenhere);
	Node* pom = new Node;

	while (Root_queue)
	{
		pom = ls[Root_queue->wartosc];
		while (pom)
		{
			if (beenhere->isitonlist(pom->nr_where, beenhere))
			{
				beenhere->add(pom->nr_where, beenhere);
				//cout << "(1) ";
				//beenhere->show(beenhere);	cout << endl;

				Root_queue->add(pom->nr_where, Root_queue);
				//cout << "(2) ";
				//Root_queue->show(Root_queue); cout << endl;
			}

			pom = pom->next;
		}
		//cout << Root_queue->wartosc<< "   ";
		Root_queue = Root_queue->next;
	}

	beenhere->show(beenhere);

	return Root_queue;
}

bool Graf::lista::isitonlist(int val, lista* root)
{

	bool output = true;

	while (root)
	{
		if (val == root->wartosc)
		{
			output = false;
		}
		root = root->next;
	}

	return output;
}

void Graf::lista::add(int value, lista*& root)
{
	if (isitonlist(value, root))
	{
		lista* pom = root;
		lista* nowy = new lista;
		nowy->wartosc = value;
		if (root)
		{
			while (pom->next)
			{
				pom = pom->next;
			}
			pom->next = nowy;
			pom->next->next = NULL;
		}
		else
		{
			root = nowy;
			root->next = NULL;
		}
	}
}

Graf::LE::LE()
{
	nr_from = NULL;
	nr_to = NULL;
	dist = NULL;
	next = nullptr;
}

void Graf::LE::fix(LE*& head)  //kompilator uznaje null jako za cos wiec zeby nie uznawalo
{
	LE* pom = new LE;
	pom = head;
	while (pom->next->dist != 0)
	{
		pom = pom->next;
	}
	delete pom->next;
	pom->next = NULL;
}

void Graf::LE::add(int nr_from, int nr_to, int dist, LE*& head)
{
	LE* nowy = new LE;
	nowy->nr_to = nr_to;
	nowy->nr_from = nr_from;
	nowy->dist = dist;
	nowy->next = head;
	head = nowy;          //dodajemy nowy element do listy(Wierzcholek od wierzcholek do)
}

void Graf::LE::sortuj(LE*& head)
{
	head->add(NULL, NULL, NULL, head);   //sortujemy babelkowo wg wag
	LE* pom = new LE;
	pom = head;
	LE* pom2 = new LE;
	int pomocniczy;
	while (pom->next && pom->next->next)
	{
		if (pom->next->dist > pom->next->next->dist)
		{
			pom2 = pom->next->next;
			pom->next->next = pom->next->next->next;
			pom2->next = pom->next;
			pom->next = pom2;
		}
		pom = pom->next;
	}

	pom = head;
	head = head->next;
	delete pom;
}

void Graf::LE::show(LE* head)
{
	while (head)
	{
		cout << head->dist << "  ";
		head = head->next;

	}
}

void show_tablice(int* tab1, int* tab2, int size)  //wypisywanie tablic
{
	cout << "TAB1 [";
	for (int i = 0; i < size; i++)   //colors
	{
		cout << tab1[i] << " ";
	}
	cout << "]";



	cout << "TAB2 [";
	for (int i = 0; i < size; i++)
	{
		cout << tab2[i] << " "; //lasy
	}
	cout << "]";

	cout << endl;
}

void zeruj_tablice(int* tab1, int* tab2, int size)
{
	for (int i = 0; i < size; i++)
	{
		tab1[i] = 0;
	}



	for (int i = 0; i < size; i++)
	{
		tab2[i] = 0;
	}
}

void Graf::LE::Kruskal(LE*& head, int size)
{
	int* colors = new int[size];
	int* forest = new int[size];
	int increment = 1;
	int pom;
	LE* LER = new LE;

	zeruj_tablice(colors, forest, size);

	while (head)
	{

		if (colors[head->nr_from] == 0 && colors[head->nr_to] == 0)  //jesli obydwa nie sa w zadnym lesie(tworzymy nowy las i dodajemy je do niego i oznaczamy ze juz sa w lesie
		{

			colors[head->nr_from] = 1;
			colors[head->nr_to] = 1;

			forest[head->nr_from] = increment;
			forest[head->nr_to] = increment;

			increment++;

			LER->add(head->nr_from, head->nr_to, head->dist, LER);

		}
		else if (colors[head->nr_from] == 1 && colors[head->nr_to] == 0)  //jeden jest w lesie drugi nie jest w lesie, oznaczamy ze oba sa w lesie i dodajemy ten co nie byl do lasu 
		{ 

			colors[head->nr_from] = 1;
			colors[head->nr_to] = 1;

			pom = forest[head->nr_from];
			forest[head->nr_to] = pom;

			LER->add(head->nr_from, head->nr_to, head->dist, LER);

		}
		else if (colors[head->nr_from] == 0 && colors[head->nr_to] == 1) //odwrotna sytuacja
		{
			colors[head->nr_from] = 1;
			colors[head->nr_to] = 1;

			pom = forest[head->nr_to];
			forest[head->nr_from] = pom;

			LER->add(head->nr_from, head->nr_to, head->dist, LER);

		}
		else if (colors[head->nr_from] == 1 && colors[head->nr_to] == 1) //sa oba w lasach
		{
			if (forest[head->nr_from] != forest[head->nr_to]) //jesli sa w roznych 
			{ 
				increment++;  //tworzymy nowy las i dodajemy wszystkie z tych dwoch lasow ktore byly xd do tego lasu 
				int forest1_pom, forest2_pom;

				forest1_pom = forest[head->nr_from];
				forest2_pom = forest[head->nr_to];

				for (int i = 0; i < size; i++)
				{
					if (forest[i] == forest1_pom || forest[i] == forest2_pom)
					{
						forest[i] = increment;
					}
				}

				LER->add(head->nr_from, head->nr_to, head->dist, LER);
			}
		}
		show_tablice(colors, forest, size);

		head = head->next;
	}
	LER->fix(LER);
	LER->show(LER);
}

void Graf::add_to_list()
{

	fstream plik;
	plik.open("graf.txt");
	int current_liczba;

	plik >> size;
	int _current_liczba;
	LE* Lista = new LE;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i < j)
			{
				plik >> _current_liczba;
			}
			else
			{
				plik >> _current_liczba;
				if (_current_liczba != 0)
				{
					Lista->add(i, j, _current_liczba, Lista);
				}
			}
		}
	}
	Lista->fix(Lista);

	Lista->show(Lista);
	for (int i = 0; i < size; i++)
	{
		Lista->sortuj(Lista);
	}
	cout << endl;
	Lista->show(Lista); cout << endl;

	Lista->Kruskal(Lista, size);
}
