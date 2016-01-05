/*
 * FICHIER: trapAuto.cpp
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-11
 *
*/

#include "trapAuto.h"

trapAuto::trapAuto() 
:trap(){
    _levierID = -1;
    _delta = 1000;
}

trapAuto::~trapAuto() {
    
}

void trapAuto::rafraichir(float delta) {
    if(_clock.getElapsedTime().asSeconds() > _delta) {
        this->toggleOuvert();
        _clock.restart();
    }
    
    trap::rafraichir(delta);
}

void trapAuto::setDeltaTime(int val) {
    _delta = val;
}