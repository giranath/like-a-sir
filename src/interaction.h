/*
 * FICHIER: interaction.h
 * PROJET:  LikeASir
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-23
 *
 * Il s'agit d'une spécialisation de la classe acteur. Elle à la particularité d'être actionnable et donc d'avoir une interaction avec.
 */

#ifndef __LikeASir__interaction__
#define __LikeASir__interaction__

#include <iostream>
#include "acteur.h"

class interaction : public acteur{
public:
    enum typeInteraction {
        NON_DEFINI = 0,
        PORTE = 1,
        CACHETTE = 2, 
        LEVIER = 3,
        TRAP = 4,
        FIN_TYPE_INTERACTION = 5
    };
    
    interaction();
    interaction(interaction const& copy);
    ~interaction();
    
    typeInteraction getTypeInterraction();
    
    // Rafraichir les informations de l'acteur [ABSTRAITE]
    virtual void rafraichir(float delta) = 0;
    
    virtual void enCollisionAvecActeur(acteur *autre) = 0;
    
    virtual void subitUneCollision() = 0;
    
    // Dessiner l'acteur à l'écran
    virtual void afficher(sf::RenderTarget *destination);
    
protected:
    bool _active;
    typeInteraction _typeInteraction;
};

#endif /* defined(__LikeASir__interaction__) */
