/*
 * FICHIER: collectionnable.h
 * PROJET:  LikeASir
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-23
 *
 * Une dérive d'acteur représentant des objets pouvant être collectionnés.
 */

#ifndef __LikeASir__collectionnable__
#define __LikeASir__collectionnable__

#include <iostream>
#include "acteur.h"

class collectionnable : public acteur {
public:
    enum typeCollectionnable {
      NON_DEFINI = 0
    };
    
    
    collectionnable();
    collectionnable(collectionnable const& copy);
    ~collectionnable();
    
    typeCollectionnable getTypeCollectionnable();
    
    // Rafraichir les informations de l'acteur [ABSTRAITE]
    virtual void rafraichir(float delta) = 0;
    
    virtual void enCollisionAvecActeur(acteur *autre) = 0;
    
    virtual void subitUneCollision() = 0;
private:
    typeCollectionnable _typeCollectionnable;
};

#endif /* defined(__LikeASir__collectionnable__) */
