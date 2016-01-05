/*
 * FICHIER: mechant.h
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-09
 *
 * Dérive de personnage et représente un ennemi dans le jeu
 */

#ifndef __LikeASir_fonctionnel__mechant__
#define __LikeASir_fonctionnel__mechant__

#include "personnage.h"

class mechant : public personnage {
public:
    mechant();
    ~mechant();
    
    virtual void rafraichir(float delta);
    virtual void enCollisionAvecActeur(acteur *autre);
    virtual void afficher(sf::RenderTarget *destination);
    
    void subitUneCollision();
    void acteurDansChampsDeVision(acteur *autre);
    
private:
    sf::Clock _updateClock;
    
};

#endif /* defined(__LikeASir_fonctionnel__mechant__) */
