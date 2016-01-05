/*
 * FICHIER: acteurs.cpp
 * PROJET:  LikeASir
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-22
 *
*/

#include "acteur.h"

unsigned long acteur::_autoID = 0;

acteur::acteur() {
    _id = _autoID++;
    _largeur = 0;
    _hauteur = 0;
    
    _vivant = true;
    _visible = true;
    
    _type = NON_DEFINI;
}

acteur::acteur(acteur const& copy) {
    _largeur = copy._largeur;
    _hauteur = copy._hauteur;
    _id = _autoID++;
    
    _vivant = copy._vivant;
    _visible = copy._visible;
    
    _type = copy._type;
}

acteur::~acteur() {
    
}

void acteur::setPosition(sf::Vector2f val) {
    _position = val;
}

void acteur::setPosition(float x, float y) {
    _position.x = x;
    _position.y =y;
}

void acteur::setDeplacement(sf::Vector2f val) {
    _deplacement = val;
}

void acteur::setDeplacement(float x, float y) {
    _deplacement.x = x;
    _deplacement.y = y;
}

void acteur::setVelocite(sf::Vector2f val) {
    _velocite = val;
}

void acteur::setVelocite(float x, float y) {
    _velocite.x = x;
    _velocite.y = y;
}

void acteur::setLargeur(float largeur) {
    _largeur = largeur;
}

void acteur::setHauteur(float hauteur) {
    _hauteur = hauteur;
}

sf::Vector2f acteur::getPosition() {
    return _position;
}

sf::Vector2f acteur::getDeplacement() {
    return _deplacement;
}

sf::Vector2f acteur::getVelocite() {
    return _velocite;
}

float acteur::getLargeur() {
    return _largeur;
}

float acteur::getHauteur() {
    return _hauteur;
}

ulong acteur::getId() {
    return _id;
}

acteur::typeActeur acteur::getType() {
    return _type;
}

bool acteur::getVivant() {
    return _vivant;
}

void acteur::tuer() {
    _vivant = false;
}

bool acteur::getVisible() {
    return _visible;
}

void acteur::setVisible(bool val) {
    _visible = val;
}

void acteur::cacher() {
    _visible = false;
}

void acteur::devoiler() {
    _visible = true;
}

void acteur::afficher(sf::RenderTarget *destination) {
    
    if(_sprite.getTextureRect().width <= _largeur)
        _sprite.setPosition(_position);
    else {
        _sprite.setPosition(_position.x - (_sprite.getTextureRect().width - _largeur)/2, _position.y);
    }
    
    destination->draw(_sprite);
}

void acteur::setTexture(sf::Texture &texture) {
    _sprite.setTexture(texture);
}