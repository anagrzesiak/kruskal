#pragma once
class Graf
{
public:

	struct Node
	{
		Node* next;
		int dist;
		int nr_where;
	private:

		void Add_Node_Naprawiony(int dist, int nr_to, Node*& linking);
		void Show_Naprawiony(Node* root);

	public:
		void Add_Node(Node*& link_do_tablicy, int dist, int nr_to);
		void Show(Node* root);
	};

	struct lista
	{
		lista* next;
		int wartosc;

		static bool isitonlist(int value, lista* root);
		void add(int value, lista*& root);
		void show(lista* root);
	};

	struct LE
	{
		int nr_from;
		int nr_to;
		int dist;
		LE* next;

		LE();
		void fix(LE*& head);
		void add(int nr_from, int nr_to, int dist, LE*& head);
		void sortuj(LE*& head);
		void show(LE* head);
		void Kruskal(LE*& head, int size);
	};

private:
	int size;
	Node ** ls;
public:
	Graf();
	void Show();
	lista* greedy();
	void add_to_list();
};

