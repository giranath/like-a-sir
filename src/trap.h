/*
 * FICHIER: trap.h
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-11
 *
 * Classe représentant une trappe. Permet de gérer les tuiles derrière. 
 */

#ifndef __LikeASir_fonctionnel__trap__
#define __LikeASir_fonctionnel__trap__

#include "interaction.h"
#include "niveau.h"

class trap : public interaction {
public:
    trap();
    ~trap();
    
    virtual void rafraichir(float delta);
    
    virtual void enCollisionAvecActeur(acteur *autre);
    
    virtual void subitUneCollision();
    
    int getLevierID();
    void setLevierID(int ID);
    
    void ouvrir();
    void fermer();
    void toggleOuvert();
    
    bool getOuvertureDefaut();
    void setOuvertureDefaut(bool val);
    
protected:
    int _levierID;
    tuile _tuileActive, _tuileDesactive;
    bool _ouvert;
    bool _defautOuverture;
};

#endif /* defined(__LikeASir_fonctionnel__trap__) */
