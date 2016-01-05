/*
 * FICHIER: BufferManager.h
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-09
 *
 * Autre gestionaire pris d'un projet personnel. Gère les buffers des sons
 */

#ifndef __LikeASir_fonctionnel__BufferManager__
#define __LikeASir_fonctionnel__BufferManager__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include "Singleton.h"

class BufferManager : public Singleton<BufferManager> {
    friend class Singleton<BufferManager>;
public:
    bool addBuffer(std::string name);
    bool removeBuffer(std::string name);
    
    bool loadBuffer(std::string name, std::string path);
    sf::SoundBuffer *getBuffer(std::string name);
    
private:
    BufferManager();
    ~BufferManager();
    std::map<std::string, sf::SoundBuffer*> _buffer;
};

#endif /* defined(__LikeASir_fonctionnel__BufferManager__) */
