/*
 * FICHIER: mechant.cpp
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-09
 *
*/

#include "mechant.h"
#include "TextureManager.h"
#include <cmath>
#include "joueur.h"

float vectLength(sf::Vector2f vect) {
    return sqrtf((vect.x * vect.x) + (vect.y * vect.y));
}

sf::Vector2f normalizeVect(sf::Vector2f vect) {
    float l = vectLength(vect);
    vect.x /= l;
    vect.y /= l;
    
    return vect;
}

mechant::mechant() 
:personnage()
{
    _sprite.setTexture(*TextureManager::getInstance()->getTexture("mechant"));
    
    _largeur = 8;
    _hauteur = 16;
    
    _antenne1.x = 0;
    _antenne1.y = _hauteur;
    
    _antenne2.x = _largeur - 1;
    _antenne2.y = _hauteur;
    
    _longueurAntennes = 1.0f;
    
    _typePersonnage = MECHANT;
    
    _distanceVision = 5;
    _directionVision = sf::Vector2f(1,0);
}

mechant::~mechant(){
    
}

void mechant::rafraichir(float delta) {
    if(_updateClock.getElapsedTime().asMilliseconds() > 3000) {
        _directionVision.x *= -1;
        _updateClock.restart();
    }
    
    if(_directionVision.x >= 0) {
        _sprite.setTextureRect(sf::IntRect(0,0,8,16));
    } else {
        _sprite.setTextureRect(sf::IntRect(0, 16, 8, 16));
    }
}

void mechant::enCollisionAvecActeur(acteur *autre) {
}

void mechant::acteurDansChampsDeVision(acteur *autre) {    
    if(autre->getType() == acteur::PERSONNAGE) {
        personnage *perso = dynamic_cast<personnage*>(autre);
        
        if(perso->getTypePersonnage() == personnage::JOUEUR) {
            joueur *j = dynamic_cast<joueur*>(perso);
            
            sf::Vector2f diff = j->getPosition() - _position;
            
            sf::Vector2f diffN = normalizeVect(diff);
            
            if(round(diffN.x) == _directionVision.x) {
                if(j->getDetecte() != true && j->getCache() == false && j->getIndetectable() == false)
                    j->detecte();
            }
        }
    }
}

void mechant::afficher(sf::RenderTarget *destination) {
    acteur::afficher(destination);
    
    sf::RectangleShape vision;
    vision.setSize(sf::Vector2f(_distanceVision * 8, 1));
    vision.setFillColor(sf::Color(255, 0, 255, 100));
    vision.setPosition(_position.x, _position.y + 6);
    
    float angle = 0;
    
    angle = atan2(_directionVision.y * -1, _directionVision.x) * 180/3.1416f;
    
    vision.setRotation(angle);
    
    //destination->draw(vision);
    
    sf::CircleShape shapeVision;
    shapeVision.setFillColor(sf::Color(255,255,255,70));
    shapeVision.setRadius(_distanceVision * 8);
    shapeVision.setPosition(_position.x - shapeVision.getRadius(), _position.y - shapeVision.getRadius());
    
    destination->draw(shapeVision);
    }

void mechant::subitUneCollision() {
    
}