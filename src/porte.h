/*
 * FICHIER: porte.h
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-06
 *
 * Il s'agit de l'interactionnable de base. Elle necessite une clef pour être activé. Il sert à lier deux niveaux entre eux
 */

#ifndef __LikeASir_fonctionnel__porte__
#define __LikeASir_fonctionnel__porte__

#include "interaction.h"

class porte : public interaction{
public:
    porte();
    ~porte();
    
    virtual void rafraichir(float delta);
    
    virtual void enCollisionAvecActeur(acteur *autre);
    
    virtual void subitUneCollision();
    
    void setProchainNiveau(int valeur);
    int getProchainNiveau();
    
private:
    int _prochainNiveau;
    sf::Sound _sonVerouille;
    
    bool _sonUnique;
};

#endif /* defined(__LikeASir_fonctionnel__porte__) */
