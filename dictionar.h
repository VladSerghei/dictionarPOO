#pragma once
#include <iostream>
#include <climits>
#include <process.h>
#include <cassert>
using namespace std;

int max(int a, int b)
{
	return (a > b) ? a : b;
}
template <class K, class V>
class nod
{
public:
	nod* st;
	nod* dr;
	nod* tata;
	K cheie;
	V valoare;
	int inaltime;
	nod()
	{
		st = nullptr;
		dr = nullptr;
		tata = nullptr;
	}
	nod(K key, V val)
	{
		st = nullptr;
		dr = nullptr;
		tata = nullptr;
		valoare = val;
		cheie = key;

	}
	K getKey()
	{
		return this->cheie;
	}
	V getVal()
	{
		return this->valoare;
	}
	int getHeight()
	{
		if (this == nullptr)
			return 0;
		return this->inaltime;
	}
};

template <class K, class V>
class dictionar
{

private:
	nod<K, V>* radacina;
	int nrElem;

public:

	dictionar();
	dictionar(const dictionar& d);
	
	dictionar &operator =(const dictionar& d);
	~dictionar();
	
	nod<K, V>* clone(nod <K, V>*t) const;
	void cleanUp(nod<K, V>* &t);
	void clear();

	nod<K, V>* rotatieDr(nod<K, V>* y);
	nod<K, V>* rotatieSt(nod<K, V>* x);
	int getBal(nod <K, V>*n);

	nod<K, V>* insert(K &key, V &val, nod<K, V>* &t);
	void setWithKey(K key, V val);
	int getNrElem();
	
	nod<K, V>* minValNod(nod<K, V>* Nod);
	nod<K, V>* deleteNode(K key, nod<K, V>* rad);
	void erase(K key);

	V src(K key, nod<K, V> *rad);
	V search(K key);

	void empty();
	V operator [](const K key);
	nod<K, V>* getRad();
	static void inorder(nod <K, V>*rad, ostream &out);

	friend ostream& operator<<(ostream &out, const dictionar& d);

};

template <class K,class V>
dictionar <K,V>::dictionar()
{
	radacina = nullptr;
	nrElem = 0;
}

template <class K, class V>
dictionar <K, V>::dictionar(const dictionar& d)
{
	radacina = nullptr;
	radacina = clone(d.radacina);

}

template <class K, class V>
dictionar <K,V>& dictionar <K, V>::operator =(const dictionar& d)
{
	clear();
	radacina = clone(d.radacina);
	this->nrElem = d.nrElem;
	return *this;
}

template <class K, class V>
dictionar <K, V>::~dictionar()
{
	clear();
}

template <class K, class V>
nod <K,V>* dictionar <K, V>::clone(nod<K,V>*t) const
{
	if (t == nullptr)
		return nullptr;

	nod<K, V> *rad = new nod<K, V>;
	rad->cheie = t->cheie;
	rad->valoare = t->valoare;
	rad->tata = t->tata;
	rad->st = clone(t->st);
	rad->dr = clone(t->dr);

	return rad;
}

template <class K, class V>
void dictionar <K, V>::cleanUp(nod<K, V>* &t)
{
	if (t != nullptr)
	{
		cleanUp(t->st);
		cleanUp(t->dr);
		delete t;
	}
	t = nullptr;
}

template <class K, class V>
void dictionar <K, V>::clear()
{
	cleanUp(radacina);
}

template <class K, class V>
nod<K, V>* dictionar <K, V>::rotatieDr(nod<K, V>* y)
{
	nod<K, V>* x = y->st;
	nod<K, V>* z = x->dr;

	x->dr = y;//rotim spre dreapta
	y->st = z;

	y->inaltime = max(y->st->getHeight(), y->dr->getHeight()) + 1;//actualizam inaltimile
	x->inaltime = max(x->st->getHeight(), x->dr->getHeight()) + 1;

	return x;
}

template <class K, class V>
nod<K, V>* dictionar <K, V>::rotatieSt(nod<K, V>* x)
{
	nod<K, V>* y = x->dr;
	nod<K, V>* z = y->st;

	y->st = x;//rotim spre stanga
	x->dr = z;

	x->inaltime = max(x->st->getHeight(), x->dr->getHeight()) + 1;//actualizam inaltimile
	y->inaltime = max(y->st->getHeight(), y->dr->getHeight()) + 1;

	return y;
}

template <class K, class V>
int dictionar <K, V>::getBal(nod<K, V> *n)
{
	if (n == nullptr)
		return 0;
	return (n->st->getHeight() - n->dr->getHeight());
}

template <class K, class V>
nod<K, V>* dictionar <K, V>::insert(K &key, V &val, nod<K, V>* &t)
{
	if (t == nullptr)
	{
		t = new nod<K, V>;
		t->cheie = key;
		t->valoare = val;
		t->st = t->dr = nullptr;
		t->inaltime = 1;
		return t;
	}
	if (key == t->cheie)
	{
		t->valoare = val;
		return t;
	}
	if (key < t->cheie)
	{
		nod<K, V> *n = insert(key, val, t->st);
		t->st = n;
		n->tata = t;
	}
	else
	{
		nod<K, V> *n = insert(key, val, t->dr);
		t->dr = n;
		n->tata = t;
	}

	t->inaltime = 1 + max(t->st->getHeight(), t->dr->getHeight());//actualizam inaltimea
	int bal = getBal(t);

	if (bal > 1 && key < t->st->cheie)//left-left
		return rotatieDr(t);

	if (bal < -1 && key > t->dr->cheie)//right-right
		return rotatieSt(t);

	if (bal > 1 && key > t->st->cheie)//left-right
	{
		t->st = rotatieSt(t->st);
		return rotatieDr(t);
	}

	if (bal < -1 && key > t->dr->cheie)
	{
		t->dr = rotatieDr(t->dr);
		return rotatieSt(t);
	}

	return t;
}

template <class K, class V>
void dictionar <K, V>::setWithKey(K key, V val)
{
	radacina = insert(key, val, radacina);
	nrElem++;
}

template <class K, class V>
int dictionar <K, V>::getNrElem()
{
	return nrElem;
}

template <class K, class V>
nod<K, V>* dictionar <K, V>::minValNod(nod<K, V>* Nod)
{
	nod<K, V>* n = Nod;
	while (n && n->st != nullptr)
		n = n->st;

	return n;
}

template <class K, class V>
nod<K, V>* dictionar <K, V>::deleteNode(K key, nod<K, V>* rad)
{

	if (rad == nullptr)
		return rad;
	if (key < rad->cheie)
		rad->st = deleteNode(key, rad->st);
	else if (key > rad->cheie)
		rad->dr = deleteNode(key, rad->dr);
	else
	{

		if (rad->st == nullptr || rad->dr == nullptr)//stergere nod cu un copil
		{
			nod<K, V> *temp = rad->st ? rad->st : rad->dr;
			if (temp == nullptr)
			{
				temp = rad;
				rad = nullptr;
			}
			else
				*rad = *temp;
			delete temp;
		}
		else
		{
			nod<K, V>* temp = minValNod(rad->dr);//pt nod cu 2 copii


			rad->cheie = temp->cheie;//copiem info succesor
			rad->valoare = temp->valoare;

			rad->dr = deleteNode(temp->cheie, rad->dr);
		}



	}

	if (rad == nullptr)
		return rad;

	rad->inaltime = 1 + max(rad->st->getHeight(), rad->dr->getHeight());//actualizam inaltimea
	int bal = getBal(rad);

	if (bal > 1 && getBal(rad->st) >= 0)//left-left
		return rotatieDr(rad);

	if (bal > 1 && getBal(rad->st) < 0)//left-right
	{
		rad->st = rotatieSt(rad->st);
		return rotatieDr(rad);

	}

	if (bal < -1 && getBal(rad->dr) <= 0)//right-right
		return rotatieSt(rad);

	if (bal < -1 && getBal(rad->dr) > 0)//right-left
	{
		rad->dr = rotatieDr(rad->dr);
		return rotatieSt(rad);
	}
	return rad;
}

template <class K, class V>
void dictionar <K, V>::erase(K key)
{
	radacina = deleteNode(key, radacina);
	nrElem--;
}

template <class K, class V>
V dictionar <K, V>::src(K key, nod <K, V>*rad)
{

	try
	{
		if (rad == nullptr)
			throw 1;
	}
	catch (int e)
	{
		cout << "Nu exista element care sa aiba cheia " << key << endl;
		return e;
	}
	if (rad->cheie == key)
		return rad->valoare;
	if (rad->cheie > key)
		return src(key, rad->st);
	else
		return src(key, rad->dr);
}

template <class K, class V>
V dictionar <K, V>::search(K key)
{
	return src(key, radacina);
}

template <class K, class V>
void dictionar <K, V>::empty()
{
	while (radacina != nullptr)
		erase(radacina->cheie);
}

template <class K, class V>
V dictionar <K, V>::operator [](const K key)
{
	K s = key;
	return this->search(s);
}

template <class K, class V>
nod<K, V>* dictionar <K, V>::getRad()
{
	return radacina;
}

template <class K, class V>
static void dictionar <K, V>::inorder(nod <K, V>*rad, ostream &out)
{
	if (rad != nullptr)
	{
		inorder(rad->st, out);
		out << rad->getKey() << '\t' << rad->getVal() << endl;
		inorder(rad->dr, out);
	}
}

template <class K, class V>
ostream& operator<<(ostream &out, const dictionar<K,V>& d)
{
	out << "Chei\tValori\n";

	nod<K, V> *p = d.radacina;
	inorder(p, out);
	return out;
}

