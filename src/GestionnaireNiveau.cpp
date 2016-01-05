/*
 * FICHIER: GestionnaireNiveau.cpp
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-06
 *
*/

#include "GestionnaireNiveau.h"

gestionnaireNiveau::gestionnaireNiveau() {
    
}

gestionnaireNiveau::~gestionnaireNiveau() {
    
}

niveau* gestionnaireNiveau::getNiveauActuel() {
    return _niveauActuelPtr;
}

niveau gestionnaireNiveau::getNiveau(int index) {
    return _niveaux[index];
}

int gestionnaireNiveau::getNbNiveau() {
    return int(_niveaux.size());
}

void gestionnaireNiveau::changerNiveau(int nouveauNiveau) {
    if(nouveauNiveau >= 0 && nouveauNiveau < getNbNiveau())
        _niveauActuel = nouveauNiveau;
    
    _niveauActuelPtr = new niveau(_niveaux[_niveauActuel]);
    
    // On transfert l'acteur
    _niveauActuelPtr->ajouterActeur(_joueur);
    _joueur->setPosition(_niveauActuelPtr->getEntree().x * 8, _niveauActuelPtr->getEntree().y * 8);
    
}

void gestionnaireNiveau::ajouterNiveau(niveau nouvNiveau) {
    _niveaux.push_back(nouvNiveau);
}

void gestionnaireNiveau::setJoueur(joueur *j) {
    _joueur = j;
}

void gestionnaireNiveau::rechargerNiveauActuel() {
    _niveauActuelPtr->recharger();
}