/*
 * FICHIER: Acteurs.h
 * PROJET:  LikeASir
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-22
 *
 * Un acteur correspond à n'importe quoi comme le personnage, un monstre, une clef, une porte, un projectile, un lapin, etc.
 */

#ifndef __LikeASir__Acteurs__
#define __LikeASir__Acteurs__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

typedef unsigned long ulong;



class acteur {    
public:
    enum typeActeur {
        NON_DEFINI = 0,
        PERSONNAGE,
        COLLECTIONNABLE,
        INTERACTIONNABLE,
        FIN_TYPE_ACTEUR
    };

private:
    static unsigned long _autoID;
    
protected:
    sf::Sprite _sprite;
    sf::Vector2f _position;
    sf::Vector2f _deplacement, _velocite;
    
    float _largeur, _hauteur;
    
    ulong _id;
    typeActeur _type;
    
    bool _vivant, _visible;
    
    bool _clef;
    
public:
    // Constructeur
    acteur();
    
    acteur(acteur const& copy);
    
    // Destructeur
    ~acteur();
    
    // Setters
    void setPosition(sf::Vector2f val);
    void setPosition(float x, float y);
    void setDeplacement(sf::Vector2f val);
    void setDeplacement(float x, float y);
    void setVelocite(sf::Vector2f val);
    void setVelocite(float x, float y);
    void setVisible(bool val);
    void setLargeur(float largeur);
    void setHauteur(float hauteur);
    
    // Getters
    sf::Vector2f getPosition();
    sf::Vector2f getDeplacement();
    sf::Vector2f getVelocite();
    
    float getLargeur();
    float getHauteur();
    bool getVivant();    
    bool getVisible();
    
    //Ajustement des valeurs bool
    void tuer();
    void cacher();
    void devoiler();
    
    ulong getId();
    typeActeur getType();
    
    void setTexture(sf::Texture &texture);
    
    // Dessiner l'acteur à l'écran
    virtual void afficher(sf::RenderTarget *destination);
    
    // Rafraichir les informations de l'acteur [ABSTRAITE]
    virtual void rafraichir(float delta) = 0;
    
    // L'Acteur entre en collision avec un autre, que ce passe t'il?
    virtual void enCollisionAvecActeur(acteur *autre) = 0;
    
    virtual void subitUneCollision() = 0;
};

#endif /* defined(__LikeASir__Acteurs__) */
