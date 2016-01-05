/*
 * FICHIER: joueur.h
 * PROJET:  LikeASir
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-23
 *
 * Il s'agit d'une spécialisation de la class Personnage. Il représente le joueur
 */

#ifndef __LikeASir__joueur__
#define __LikeASir__joueur__

#include <iostream>
#include "personnage.h"
#include <SFML/Audio.hpp>

const long TEMPS_MAXIMUM_DETEXTION_MS = 7500;

class joueur : public personnage {
public:
    joueur();
    ~joueur();
    
    virtual void rafraichir(float delta);
    virtual void enCollisionAvecActeur(acteur *autre);
    virtual void afficher(sf::RenderTarget *destination);
    
    bool getCache();
    void setCache(bool val);
    
    void subitUneCollision();
    
    void trouverClef();
    void enleverClef();
    
    bool getClef();
    
    bool getAction();
    
    bool getDetecte();
    void detecte();
    void nonDetecte();
    
    long getTempsDetection();
    
    bool getCacher();
    bool getIndetectable();
    void setIndetectable(bool val);
    
private:
    bool _cache;    // Le héro est caché?
    bool _clef;
    bool _action;
    bool _detecte;
    bool _indetectable;
    
    sf::Sound _sonSaut;
    sf::Sound _sonClef;
    sf::Sound _sonHurt;
    
    sf::Clock _timerDetection;
};

#endif /* defined(__LikeASir__joueur__) */
