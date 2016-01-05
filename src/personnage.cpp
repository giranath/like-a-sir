/*
 * FICHIER: personnage.cpp
 * PROJET:  LikeASir
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-23
 *
*/

#include "personnage.h"

personnage::personnage()
:acteur(){
    _type = PERSONNAGE;
    _antenne1.x = 0;
    _antenne1.y = _hauteur;
    
    _antenne2.x = _largeur;
    _antenne2.y = _hauteur;
    
    _longueurAntennes = 5.0f;
}

personnage::personnage(personnage const& copy) {
    _largeur = copy._largeur;
    _hauteur = copy._hauteur;
    _id = copy._id;
    
    _vivant = copy._vivant;
    _visible = copy._visible;
    
    _type = copy._type;
    
    _antenne1 = copy._antenne1;
    _antenne2 = copy._antenne2;
    
    _auSol = copy._auSol;
    
    _directionVision = copy._directionVision;
    _distanceVision = copy._distanceVision;
}

personnage::~personnage() {
    
}

personnage::typePersonnage personnage::getTypePersonnage() {
    return _typePersonnage;
}

int personnage::getVie() {
    return _vie;
}

float personnage::getDistanceVision() {
    return _distanceVision;
}

sf::Vector2f personnage::getDirectionVision() {
    return _directionVision;
}

sf::Vector2f personnage::getAntenne1() {
    return _antenne1;
}

sf::Vector2f personnage::getAntenne2() {
    return _antenne2;
}

float personnage::getLongueurAntenne() {
    return _longueurAntennes;
}

void personnage::setDirectionVision(float x, float y) {
    _directionVision = sf::Vector2f(x, y);
}

void personnage::setDirectionVision(sf::Vector2f vect) {
    _directionVision = vect;
}

void personnage::setLongueurAntenne(float longeur) {
    _longueurAntennes = longeur;
}

bool personnage::getAuSol() {
    return _auSol;
}

void personnage::setAuSol(bool val) {
    _auSol = val;
}

void personnage::setWatchOut(bool val) {
    _watchOut = val;
}