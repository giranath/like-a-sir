/*
 * FICHIER: trapAuto.h
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-11
 *
 * Il s'agit d'un type de trap non-actionnable car ils le font seul à partir d'un minuteur.
 */

#ifndef __LikeASir_fonctionnel__trapAuto__
#define __LikeASir_fonctionnel__trapAuto__

#include "trap.h"

class trapAuto : public trap{
public:
    trapAuto();
    ~trapAuto();
    
    virtual void rafraichir(float delta);
    
    void setDeltaTime(int val);
    
private:
    sf::Clock _clock;
    int _delta;
};

#endif /* defined(__LikeASir_fonctionnel__trapAuto__) */
