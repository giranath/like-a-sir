/*
 * FICHIER: GestionnaireNiveau.h
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-06
 *
 * Gestionnaire unique permettant le changement de niveaux
 */

#ifndef __LikeASir_fonctionnel__GestionnaireNiveau__
#define __LikeASir_fonctionnel__GestionnaireNiveau__

#include "Singleton.h"
#include "niveau.h"
#include <vector>
#include "joueur.h"

class gestionnaireNiveau : public Singleton<gestionnaireNiveau> {
    friend class Singleton<gestionnaireNiveau>;
    
public:
    niveau* getNiveauActuel();
    niveau getNiveau(int index);
    int getNbNiveau();
    void changerNiveau(int nouveauNiveau);
    void ajouterNiveau(niveau nouvNiveau);
    
    void setJoueur(joueur *j);
    void rechargerNiveauActuel();
    
private:
    gestionnaireNiveau();
    ~gestionnaireNiveau();
    
    int _niveauActuel;
    niveau *_niveauActuelPtr;
    std::vector<niveau> _niveaux;
    joueur *_joueur;
};

#endif /* defined(__LikeASir_fonctionnel__GestionnaireNiveau__) */