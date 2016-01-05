/*
 * FICHIER: levier.h
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-11
 *
 * Permet d'activer/Desactiver à distance des trappes.
 */

#ifndef __LikeASir_fonctionnel__levier__
#define __LikeASir_fonctionnel__levier__

#include "interaction.h"
#include <SFML/Audio.hpp>

class levier : public interaction {
public:
    levier();
    ~levier();
    virtual void rafraichir(float delta);
    
    virtual void enCollisionAvecActeur(acteur *autre);
    
    virtual void subitUneCollision();
    
    int getLevierID();
    void setLevierID(int ID);
    
    void setUtiliser(bool val);
    
private:
    int _levierIdentifiant;
    bool _utilise;
    bool _uniqueUtilisation;
    sf::Sound _son;
};

#endif /* defined(__LikeASir_fonctionnel__levier__) */
