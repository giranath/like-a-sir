/**********************************************
**Auteur : Jérémy Soucy / Nathan Giraldeau 
**Date : 6 avril 2013
**But : Rassembler les méthodes
***********************************************/
#include "menu.h"
//Fonction qui initialise la texture télécharger
bool init(std::string nom,sf::Texture &image){
	if(!image.loadFromFile(nom)){
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
//Fonction qui initialise le font pour la police
bool init(std::string nom,sf::Font &font){
	if(!font.loadFromFile(nom)){
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
//Fonction qui initialise le texte que on souhaite sortir ‡ l'écran
sf::Sprite init(sf::Texture &nom,position coord,sf::IntRect carre,int format){
	
	sf::Sprite img;

	img.setTexture(nom);					//On set le sprite avec la texture
	img.setPosition(coord.x,coord.y);		//On lui assigne une position
	img.setTextureRect(carre);				//On lui définie quelle parti de l'image on souhaite voir ‡ l'écran
	img.setScale(format,format);			//On lui demande d'augmenter l'image par le format en hauteur et largeur
	
	return img;
}
sf::Text ecrireMot(std::string mot,int taille,sf::Color couleur,position coord,int rota,sf::Font &font){
	sf::Text sorti;

	sorti.setFont(font);					//On set le style de la police
	sorti.setString(mot);					//On lui défini une chaÓne de caractËre
	sorti.setCharacterSize(taille);			//On lui donne la taille en pixel
	sorti.setColor(couleur);				//On lui donne une couleur
	sorti.setPosition(coord.x,coord.y);		//On lui donne une position
	sorti.setRotation(rota);				//On peut le faire tourner selon l'angle désirer

	return sorti;
}
sf::RectangleShape creerRect(position coord,sf::Vector2f init){
	sf::RectangleShape rectangle;

	rectangle.setFillColor(sf::Color::White);		//On lui assigne une couleur
	rectangle.setPosition(coord.x,coord.y);			//On lui donne une position
	rectangle.setSize(init);						//On lui ajuste une taille

	return rectangle;								//Retourne le rectangle
}

bool menu(sf::RenderWindow &windows) {    
	//Crée l'objet font pour les différents texte
	sf::Font font;
	//L'objet Mouse a été crée pour les boutons commencer et quitter
	sf::Mouse mouse;
	//Crée les deux structures
	position coordGentil;					//Position du personnage Principale
	position coord;							//Structures souvant réutiliser pour seter les positions qui sont fixes
	//Mes deux objets textures 
	sf::Texture bonhomme;					//Ma textures pour mon personnage principale
	sf::Texture terrein;					//Ma textures pour faire le sol
	//Objet de sprite
	sf::Sprite gentil;						//Va permettre de modifier et d'afficher l'image initiale
	sf::Sprite sol;							//Va permettre de modifier et d'afficher l'image pour le terrein
	//On récupËre la police, le bonhomme et le terrein
	init("Police.ttf",font);	
	init("textures/heroSkin.png",bonhomme);
	init("textures/tuiles.png",terrein);
	//On va seter le personnage principale *gentil* ...
	coordGentil.x = 100;
	coordGentil.y = 520;
	gentil=init(bonhomme,coordGentil,sf::IntRect(0,0,11,16),3);
	//On va seter le terrein 
	sol.setTexture(terrein);
	sol.setTextureRect(sf::IntRect(17,0,8,8));
	sol.setScale(4,4);
	//imgBonhomme.setTextureRect(sf::IntRect
	//On réduit la frame ‡ 60 pour qu'elle ne soit pas ‡ son plein potentiel et constante
	windows.setFramerateLimit(60);
    
	//C'est la que on met en place le settage des mots et des lettre pour afficher
	//Écrit la lettre L
	sf::Text lettreL;						//On crée l'objet texte de la lettre (*)
	coord.x = 320;							//On set le point x de la lettre	
	coord.y = 100;							//On set le point y de la lettre
	lettreL = ecrireMot("L",50,sf::Color(152,27,30),coord,335,font);
	//Écrit la lettre I
	sf::Text lettreI;
	coord.x = 370;
	coord.y = 75;
	lettreI = ecrireMot("i",50,sf::Color(152,27,30),coord,345,font);
	//Écrit la lettre K
	sf::Text lettreK;
	coord.x = 420;
	coord.y = 75;
	lettreK =  ecrireMot("k",50,sf::Color(152,27,30),coord,10,font);	
	//Écrit la lettre E
	sf::Text lettreE;
	coord.x = 470;
	coord.y = 90;
	lettreE =  ecrireMot("e",50,sf::Color(152,27,30),coord,35,font);
	//Écrit la lettre A
	sf::Text lettreA;
	coord.x = 385;
	coord.y = 150;
	lettreA =  ecrireMot("A",50,sf::Color(152,27,30),coord,0,font);
	//Écrit le texte Sir
	sf::Text txtSir;
	coord.x =360;
	coord.y = 220;
	txtSir =  ecrireMot("Sir",50,sf::Color(152,27,30),coord,0,font);
	//Écrire Commencer
	sf::Text jouer;
	coord.x = 150;
	coord.y = 375;
	jouer = ecrireMot("Commencer",20,sf::Color(252,130,33),coord,0,font);
	//Écrire Quitter
	sf::Text partir;
	coord.x = 570;
	coord.y = 375;
	partir = ecrireMot("Quitter",20,sf::Color(252,130,33),coord,0,font);
	
	//On crée les boutons Commencer et Quitter
	//Bouton pour Commencer
	sf::RectangleShape commence;					//On crée l'objet rectangle
	coord.x = 120;
	coord.y = 350;
	commence = creerRect(coord,sf::Vector2f(180,70));
	//Bouton pour Quitter
	sf::RectangleShape quitte;
	coord.x = 520;
	coord.y = 350;
	quitte = creerRect(coord,sf::Vector2f(180,70));
    
    
    bool play = false;
    
	while (true){
		//Crée l'objet event pour récupérer chaque event qui va se produire dans la fenÍtre
		sf::Event event;
        
		while(windows.pollEvent(event)){
            //Si l'utilisateur presse le bouton X en haut il quitte le programme
			//ou
            //Si on clic droit sur la souris et que celle-ci ‡ la mÍme position que le bouton droite **quitter**
			if(event.type == sf::Event::Closed || 
               (mouse.isButtonPressed(sf::Mouse::Left) && quitte.getGlobalBounds().contains((sf::Vector2f)mouse.getPosition(windows))))					
				return false;
            
            else if(mouse.isButtonPressed(sf::Mouse::Left) && commence.getGlobalBounds().contains((sf::Vector2f)mouse.getPosition(windows)))
               return true;
			//Si un event correspond au clavier on rentre dans le if
			else if(event.type == sf::Event::KeyPressed){
				
				switch (event.key.code)
				{
                        //Si la touche A est appuyer on change l'image du gentil et on le déplace vers la gauche
                    case (sf::Keyboard::A):					
                        gentil.setPosition(coordGentil.x -= 2,coordGentil.y);
                        gentil.setTextureRect(sf::IntRect(0,16,11,16));					
                        break;
                        //Si la touche D est appuyer on change l'image du gentil et on le déplace vers la droite
                    case (sf::Keyboard::D):
                        gentil.setPosition(coordGentil.x += 2,coordGentil.y);
                        gentil.setTextureRect(sf::IntRect(0,0,11,16));
                        break;
                    default:
                        break;
				}
			}
		}
		//On clear la fenÍtre et on lui donne un code de couleur qui va afficher comme arriËre-plan
		windows.clear(sf::Color(157,222,250));
		//On dessine le bouton quitter et commencer
		windows.draw(commence);
		windows.draw(quitte);
		//On dessine une ligne avec l'image du sol
		for(int x=0;x<40;x++){
			sol.setPosition(0+(x*20),568);
			windows.draw(sol);
		}
		//On réinitialise la position de départ
		sol.setPosition(0,500);
		//On Affiche Like A Sir
		windows.draw(gentil);
		windows.draw(lettreL);
		windows.draw(lettreI);
		windows.draw(lettreK);
		windows.draw(lettreE);
		windows.draw(lettreA);
		windows.draw(txtSir);
		//On affiche Le commencer et le quitter
		windows.draw(partir);
		windows.draw(jouer);
		//On affiche le tout		
		windows.display();
	}
    
    return play;
}