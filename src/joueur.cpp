/*
 * FICHIER: joueur.cpp
 * PROJET:  LikeASir
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-23
 *
*/

#include "joueur.h"

//#include "unicorn.h"
#include <sstream>
#include <cmath>
#include "BufferManager.h"

joueur::joueur()
:personnage()
{
    _largeur = 8;
    _hauteur = 16;
    
    _antenne1.x = 0;
    _antenne1.y = _hauteur;
    
    _antenne2.x = _largeur - 1;
    _antenne2.y = _hauteur;
    
    _longueurAntennes = 1.0f;
    
    _typePersonnage = JOUEUR;
    
    enleverClef();
    nonDetecte();
    
    _sonSaut.setBuffer(*BufferManager::getInstance()->getBuffer("jump"));
    _sonSaut.setVolume(15.0f);
    
    _sonClef.setBuffer(*BufferManager::getInstance()->getBuffer("clef"));
    _sonClef.setVolume(15.0f);
    
    _sonHurt.setBuffer(*BufferManager::getInstance()->getBuffer("hurt"));
    
    _cache = false;
    _indetectable = false;
}

joueur::~joueur() {
    
}

void joueur::rafraichir(float delta) {
    _velocite.x = 0;
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && _cache == false) {
        _velocite.x += 1;
            
        _left = false;

    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && _cache == false) {
        _velocite.x -= 1;
            
        _left = true;
        
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && _auSol && _velocite.y >= 0 && _cache == false) {
        _velocite.y = -1.75f;
        if(_sonSaut.getStatus() != sf::Sound::Playing)
            _sonSaut.play();
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        _action = true;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) == false) {
        _action = false;
    }

    _sprite.setTextureRect(sf::IntRect(0,16,12,16));
    
    if(_left == false) {
        _sprite.setTextureRect(sf::IntRect(0,0,12,16));
    }
    
    if(_auSol == false) {
        if(_left)
            _sprite.setTextureRect(sf::IntRect(0,32,12,16));
        else 
            _sprite.setTextureRect(sf::IntRect(0,48,12,16));
    }
    
    if(_watchOut == true && _auSol) {
        if(!_left)
            _sprite.setTextureRect(sf::IntRect(0,64,12,16));
        else 
            _sprite.setTextureRect(sf::IntRect(0,80,12,16));
    }
    
}

void joueur::enCollisionAvecActeur(acteur *autre) {
    
}

void joueur::afficher(sf::RenderTarget *destination) {
    if(_indetectable) {
        _sprite.setColor(sf::Color(255,255,255,100));
    } else {
        _sprite.setColor(sf::Color(255,255,255,255));
    }
    
    acteur::afficher(destination);
    
    sf::RectangleShape boundingBox;
    boundingBox.setPosition(round(_position.x), round(_position.y));
    boundingBox.setSize(sf::Vector2f(_largeur, _hauteur));
    boundingBox.setFillColor(sf::Color(255,0,255,100));
    
    sf::RectangleShape antenne;
    antenne.setSize(sf::Vector2f(1, _longueurAntennes));
    antenne.setPosition(_position + _antenne1);
    
    antenne.setFillColor(sf::Color(0,255,0));
    
    //destination->draw(antenne);
    
    antenne.setPosition(_position + _antenne2);
    antenne.setFillColor(sf::Color(0,255,0));
    
   // destination->draw(antenne);
    
    float length;
    length = sqrtf((_velocite.x * _velocite.x) + (_velocite.y * _velocite.y));
    
    antenne.setSize(sf::Vector2f(1, length));
    antenne.setPosition(_position.x + _largeur/2, _position.y + _hauteur/2);
    
    float angle = atan2f(-_velocite.x, _velocite.y);
    angle = angle * 180 / 3.14159;
    
    antenne.setRotation(angle);
    
    if(_auSol) {
        antenne.setFillColor(sf::Color(255,0,0));
    }
    
    //destination->draw(antenne);
    
    sf::Text t;
  
}

void joueur::subitUneCollision() {
    if(_velocite.y > 3) { 
        _sonHurt.play();
    }
}

bool joueur::getCache() {
    return _cache;
}

void joueur::setCache(bool val) {
    _cache = val;
}

void joueur::trouverClef() {
    _clef = true;
    _sonClef.play();
}

void joueur::enleverClef() {
    _clef = false;
}

bool joueur::getClef() {
    return _clef;
}

bool joueur::getAction() {
    return _action;
}

bool joueur::getDetecte() {
    return _detecte;
}

void joueur::detecte() {
    _detecte = true;
    _timerDetection.restart();
}

void joueur::nonDetecte() {
    _detecte = false;
}

long joueur::getTempsDetection() {
    return TEMPS_MAXIMUM_DETEXTION_MS - _timerDetection.getElapsedTime().asMilliseconds();
}

bool joueur::getCacher() {
    return _cache;
}

bool joueur::getIndetectable() {
    return _indetectable;
}

void joueur::setIndetectable(bool val) {
    _indetectable = val;
}