/*
 * FICHIER: clef.h
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-06
 *
 * Outils collectionnable qui permet l'utilisation d'une porte
 */

#ifndef __LikeASir_fonctionnel__clef__
#define __LikeASir_fonctionnel__clef__

#include "collectionnable.h"

class clef : public collectionnable {
public:
    clef();
    ~clef();
    
    virtual void rafraichir(float delta);
    
    virtual void enCollisionAvecActeur(acteur *autre);
    
    virtual void subitUneCollision();
private:
};

#endif /* defined(__LikeASir_fonctionnel__clef__) */
