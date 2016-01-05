/************************************************************
**Auteur : Jérémy Soucy / Nathan Giraldeau	               **
**Date : 6 avril 2013									   **
**But : Créer l'objet menu dans un .h avec sa structure	   **
************************************************************/
#include <SFML/Graphics.hpp>
#include <string>
//Ma structure pour les positions soit pour les images fixes ou dynamiques
struct position{	
	float x;			//Pour la position x de l'image
	float y;			//Pour la position y de l'image
};
//Les fonctions qui permet de récuper la police et l'image
bool init(std::string nom,sf::Font &font);
bool init(std::string nom,sf::Texture &image);
//On set l'image
sf::Sprite init(sf::Texture &nom,position coord,sf::IntRect carre,int format);
//On set la lettre ou le mot que on souhaite afficher
sf::Text ecrireMot(std::string mot,int taille,sf::Color couleur,position coord,int rota,sf::Font &font);
//On créer un rectangle
sf::RectangleShape creerRect(position coord,sf::Vector2f init);

bool menu(sf::RenderWindow &window);