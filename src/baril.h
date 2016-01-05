/*
 * FICHIER: baril.h
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-09
 *
 * Cachette principale. Si le joueur se tient dessus, il peut disparaitre et réinitialiser son compteur de recherche.
 */

#ifndef __LikeASir_fonctionnel__baril__
#define __LikeASir_fonctionnel__baril__

#include "interaction.h"

class baril : public interaction{
public:
    baril();
    ~baril();
    
    virtual void rafraichir(float delta);
    
    virtual void enCollisionAvecActeur(acteur *autre);
    
    virtual void subitUneCollision();
    
private:
    bool _uniqueAction;
};


#endif /* defined(__LikeASir_fonctionnel__baril__) */
