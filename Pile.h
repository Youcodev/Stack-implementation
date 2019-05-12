/********************************************
* Titre: Travail pratique #5 - Pile.h
* Date: 19/03/2017
* Auteur: Gergi Younis
*******************************************/

/************************************************************************************************************
* Une autre solution qui utilise un vector � la place d'un tableau dynamique est propos�e (fichier vector). *
* En fin de compte, un vector c'est aussi une forme de tableau dynamique !									*
*************************************************************************************************************/

#ifndef PILE_H
#define PILE_H

using namespace std;

template <typename T>
class Pile {
public:
//Constructeur par d�faut
	Pile();

//Destructeur
	~Pile();

/*********************************************************************
* Fonction : empiler												 *
* Description : Ajoute un �l�ment sur la pile (au sommet du tableau) *
* Param�tres : Un �l�ment de type g�n�rique � ajouter				 *
* Valeur de retour : True si l'ajout est r�ussi						 *
*					 i.e. la pile n'est pas pleine					 *
**********************************************************************/
	bool empiler(const T&);

/*****************************************************************************************
* Fonction : depiler																	 *
* Description : Retire le dernier �l�ment ajout� � la pile et le retourne par param�tre  *
* Param�tres : Un type g�n�rique pour le retour de l'�l�ment du dessus de la pile        *
* Valeur de retour : True si le d�pilage est r�ussi										 *
*					 i.e. la pile n'est pas vide										 *
******************************************************************************************/
	bool depiler(T& elem);

/********************************************************
* Fonction : estVide									*
* Description : Indique si la pile est vide				*
* Param�tres : Aucun									*
* Valeur de retour : True si la pile est vide			*
*********************************************************/
	bool estVide() const;

/**********************************************************
* Fonction : estPleine									  *
* Description : Indique si la pile est pleine			  *
* Param�tres : Aucun									  *
* Valeur de retour : True si la pile est pleine			  *
***********************************************************/
	bool estPleine() const;

/**********************************************************
* Fonction : obtenirSommet								  *
* Description : Acc�der � l'�l�ment du dessus de la pile  *
* Param�tres : Aucun									  *
* Valeur de retour : R�f�rence sur cet �l�ment			  *
***********************************************************/
	const T& obtenirSommet() const;

/**************************************************************
* Fonction : obtenirTaille									  *
* Description : D�termine le nombre d'�l�ments dans la pile	  *
* Param�tres : Aucun										  *
* Valeur de retour : Nombre d'�l�ments pr�sents dans la pile  *
***************************************************************/
	int obtenirTaille() const;

private:
	int const capacite_; //La capacit� du tableau restera fixe
	int nombreElements_; //Le nombre d'�l�ments pr�sents dans la pile
	T* elements_; //Un tableau dynamique d'�l�ments g�n�riques
};

template <typename T>
Pile<T>::Pile(): capacite_(6), nombreElements_(0) {
	elements_ = new T[capacite_];
}

template <typename T>
Pile<T>::~Pile() {
	//On lib�re les zones allou�es dynamiquement afin d'�viter les fuites de m�moire
	delete[] elements_;
	elements_ = nullptr;
}

template <typename T>
bool Pile<T>::empiler(const T& elem) {
//On v�rifie d'abord si la pile est pleine (pour �viter son d�bordement)
	if (estPleine())
		return false;
//Sinon, on y ajoute l'�l�ment pass� en param�tre
//On incr�mente ensuite l'indice du tableau vers la prochaine position libre (attente d'une �ventuelle nouvelle valeur)
	elements_[nombreElements_++] = elem;
	return true;
}

template <typename T>
bool Pile<T>::depiler(T& elem) {
//On v�rifie d'abord si la pile est vide (pas d'�l�ments � d�piler)
	if (estVide())
	return false;
/*Sinon, on y retire l'�l�ment au sommet de la pile apr�s l'avoir renvoy� (par param�tre pour une utilisation donn�e).
Apr�s d�cr�mentation de l'indice du tableau, on aurait pu tout simplement consid�rer que cet �l�ment n'appartient plus � la
pile, et que l'ajout d'un futur �l�ment remplacera l'�l�ment ainsi d�laiss�. Or une solution plus propre a �t� privil�gi�e ici 
par la suppression des �l�ments d�pil�s (en les initialisant � leur valeur par d�faut, ce qui donne par exemple une valeur nulle
pour un double et une cha�ne vide pour un string) du moment o� la pile forme un tout par sa taille fixe, et puis ce choix 
ressemble � la fonction pop_back des conteneurs de la STL; en fait, une fois cette fonctions appel�e, on n'a plus acc�s au 
dernier �l�ment retir� (sauf si on l'a sauvegard� avant).*/
	elem = obtenirSommet();
	elements_[--nombreElements_] = T{};
	return true;
}

template <typename T>
bool Pile<T>::estVide() const {
	return nombreElements_ == 0;
}

template <typename T>
bool Pile<T>::estPleine() const {
	return obtenirTaille() == capacite_;
}

template <typename T>
const T& Pile<T>::obtenirSommet() const {
//On suppose ici que la pile n'est pas vide.
// Dans le cas contraire, il faudrait g�rer des exceptions telle que throw out_of_range
// Ou �ventuellement changer le type de retour pour un pointeur afin de retourner un nullptr
	return elements_[nombreElements_ - 1];
}

template <typename T>
int Pile<T>::obtenirTaille() const {
	return nombreElements_;
}

#endif // !PILE_H
