/*
 * FICHIER: trap.cpp
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-11
 *
*/

#include "trap.h"
#include "GestionnaireNiveau.h"
#include "TextureManager.h"

trap::trap()
:interaction()
{
    _typeInteraction = interaction::TRAP;
    tuile t;
    t.mur = false;
    t.identifiant = 15;
    t._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    
    _tuileDesactive = t;
    
    t.mur = true;
    t.identifiant = 13;
    
    _tuileActive = t;
    
    _defautOuverture = true;
    _active = false;
}

trap::~trap() {
    
}

void trap::rafraichir(float delta) {
    
    if(_ouvert) {
        gestionnaireNiveau::getInstance()->getNiveauActuel()->setTuile(_position.x / 8, _position.y / 8, _tuileDesactive);
    } else {
        gestionnaireNiveau::getInstance()->getNiveauActuel()->setTuile(_position.x / 8, _position.y / 8, _tuileActive);
    }
}

void trap::enCollisionAvecActeur(acteur *autre) {
    
}

void trap::subitUneCollision() {
    
}

int trap::getLevierID() {
    return _levierID;
}

void trap::setLevierID(int ID) {
    _levierID = ID;
}

void trap::ouvrir() {
    _ouvert = true;
}

void trap::fermer() {
    _ouvert = false;
}

void trap::toggleOuvert() {
    _ouvert = !_ouvert;
}

bool trap::getOuvertureDefaut() {
    return _defautOuverture;
}

void trap::setOuvertureDefaut(bool val) {
    _defautOuverture = val;
}