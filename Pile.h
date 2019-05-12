/********************************************
* Titre: Travail pratique #5 - Pile.h
* Date: 19/03/2017
* Auteur: Gergi Younis
*******************************************/

#ifndef PILE_H
#define PILE_H

using namespace std;

template <typename T>
class Pile {
public:
//Constructeur par défaut
	Pile();

//Destructeur
	~Pile();

/*********************************************************************
* Fonction : empiler												 *
* Description : Ajoute un élément sur la pile (au sommet du tableau) *
* Paramètres : Un élément de type générique à ajouter				 *
* Valeur de retour : True si l'ajout est réussi						 *
*					 i.e. la pile n'est pas pleine					 *
**********************************************************************/
	bool empiler(const T&);

/*****************************************************************************************
* Fonction : depiler																	 *
* Description : Retire le dernier élément ajouté à la pile et le retourne par paramètre  *
* Paramètres : Un type générique pour le retour de l'élément du dessus de la pile        *
* Valeur de retour : True si le dépilage est réussi										 *
*					 i.e. la pile n'est pas vide										 *
******************************************************************************************/
	bool depiler(T& elem);

/********************************************************
* Fonction : estVide									*
* Description : Indique si la pile est vide				*
* Paramètres : Aucun									*
* Valeur de retour : True si la pile est vide			*
*********************************************************/
	bool estVide() const;

/**********************************************************
* Fonction : estPleine									  *
* Description : Indique si la pile est pleine			  *
* Paramètres : Aucun									  *
* Valeur de retour : True si la pile est pleine			  *
***********************************************************/
	bool estPleine() const;

/**********************************************************
* Fonction : obtenirSommet								  *
* Description : Accéder à l'élément du dessus de la pile  *
* Paramètres : Aucun									  *
* Valeur de retour : Référence sur cet élément			  *
***********************************************************/
	const T& obtenirSommet() const;

/**************************************************************
* Fonction : obtenirTaille									  *
* Description : Détermine le nombre d'éléments dans la pile	  *
* Paramètres : Aucun										  *
* Valeur de retour : Nombre d'éléments présents dans la pile  *
***************************************************************/
	int obtenirTaille() const;

private:
	int const capacite_; //La capacité du tableau restera fixe
	int nombreElements_; //Le nombre d'éléments présents dans la pile
	T* elements_; //Un tableau dynamique d'éléments génériques
};

template <typename T>
Pile<T>::Pile(): capacite_(6), nombreElements_(0) {
	elements_ = new T[capacite_];
}

template <typename T>
Pile<T>::~Pile() {
	//On libère les zones allouées dynamiquement afin d'éviter les fuites de mémoire
	delete[] elements_;
	elements_ = nullptr;
}

template <typename T>
bool Pile<T>::empiler(const T& elem) {
//On vérifie d'abord si la pile est pleine (pour éviter son débordement)
	if (estPleine())
		return false;
//Sinon, on y ajoute l'élément passé en paramètre
//On incrémente ensuite l'indice du tableau vers la prochaine position libre (attente d'une éventuelle nouvelle valeur)
	elements_[nombreElements_++] = elem;
	return true;
}

template <typename T>
bool Pile<T>::depiler(T& elem) {
//On vérifie d'abord si la pile est vide (pas d'éléments à dépiler)
	if (estVide())
	return false;
/*Sinon, on y retire l'élément au sommet de la pile après l'avoir renvoyé (par paramètre pour une utilisation donnée).
Après décrémentation de l'indice du tableau, on aurait pu tout simplement considérer que cet élément n'appartient plus à la
pile, et que l'ajout d'un futur élément remplacera l'élément ainsi délaissé. Or une solution plus propre a été privilégiée ici 
par la suppression des éléments dépilés (en les initialisant à leur valeur par défaut, ce qui donne par exemple une valeur nulle
pour un double et une chaîne vide pour un string) du moment où la pile forme un tout par sa taille fixe, et puis ce choix 
ressemble à la fonction pop_back des conteneurs de la STL; en fait, une fois cette fonctions appelée, on n'a plus accès au 
dernier élément retiré (sauf si on l'a sauvegardé avant).*/
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
// Dans le cas contraire, il faudrait gérer des exceptions telle que throw out_of_range
// Ou éventuellement changer le type de retour pour un pointeur afin de retourner un nullptr
	return elements_[nombreElements_ - 1];
}

template <typename T>
int Pile<T>::obtenirTaille() const {
	return nombreElements_;
}

#endif // !PILE_H
