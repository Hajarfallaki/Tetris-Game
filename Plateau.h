#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

/// Inclusion des biblioth�ques standard et d�finitions
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

/// D�finition du nombre maximum de pi�ces
#define NBmax_piece 15
using namespace std;

/// D�claration de la classe AnimatedSprite, qui h�rite de sf::Sprite
class AnimatedSprite : public sf::Sprite {
public:
    // Ajoute une texture � la liste des frames
    void addFrame(sf::Texture texture) {
        frames.push_back(texture);
    }

    // Met � jour la frame actuelle en fonction du temps �coul�
    void update() {
        static sf::Clock clock; // Horloge pour mesurer le temps �coul�
        sf::Time elapsed = clock.getElapsedTime();

        // Change de frame toutes les 0.1 secondes
        if (elapsed.asSeconds() > 0.1) {
            currentFrame = (currentFrame + 1) % frames.size();
            setTexture(frames[currentFrame]);
            clock.restart();
        }
    }

private:
    std::vector<sf::Texture> frames; // Liste des textures pour l'animation
    int currentFrame = 0; // Index de la frame actuelle
};

/// Structure repr�sentant l'�tat du jeu
struct EtatJeu {
    std::string nomJoueur; // Nom du joueur
    int score; // Score actuel
    int niveau; // Niveau actuel
    float temps; // Temps �coul�
};

/// Instance globale de EtatJeu
EtatJeu etatJeu;

///D�claration anticip�e de la classe Piece pour r�soudre la d�pendance circulaire
class Piece;

/// D�claration de la classe PieceGraphique, qui associe une forme graphique � une pi�ce
class PieceGraphique {
public:
    sf::RectangleShape shape; // Forme rectangulaire par d�faut
    Piece* piece; // Pointeur vers la pi�ce associ�e

    // Constructeur de PieceGraphique
    PieceGraphique(const sf::Vector2f& size, Piece* piece, const sf::Color& color, const sf::Vector2f& position)
        : piece(piece) {
        shape.setSize(size);
        shape.setFillColor(color);
        shape.setPosition(position);
    }

    // Dessine la forme graphique dans la fen�tre
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    // Retourne le pointeur vers la pi�ce associ�e
    Piece* getPiece() { return piece; }
};

///Classe Piece : repr�sente une pi�ce de jeu avec des attributs pour la couleur et la forme,
///ainsi que des pointeurs vers d'autres pi�ces dans une structure de liste cha�n�e.

class Piece {
private:
    sf::Color couleur; // Couleur de la pi�ce
    std::string forme; // Forme g�om�trique de la pi�ce
    // Pointeurs vers les pi�ces adjacentes dans la liste cha�n�e
    Piece* suivante; // Pi�ce suivante dans la liste
    Piece* precedente; // Pi�ce pr�c�dente dans la liste
    // Pointeurs vers les pi�ces de m�me forme, permettant de cr�er une sous-liste
    Piece* suivanteMemeForme; // Pi�ce suivante de m�me forme
    Piece* precedenteMemeForme; // Pi�ce pr�c�dente de m�me forme

public:
    // Constructeur de la classe Piece initialisant les attributs et les pointeurs � nullptr
    Piece(const sf::Color& color, const std::string& form)
        : couleur(color), forme(form), suivante(nullptr), precedente(nullptr),
        suivanteMemeForme(nullptr), precedenteMemeForme(nullptr) {}

    // Getters : fonctions pour obtenir les valeurs des attributs
    sf::Color getCouleur() const { return couleur; }
    std::string getForme() const { return forme; }
    Piece* getSuivante() { return suivante; }
    Piece* getPrecedente() { return precedente; }
    Piece* getSuivanteMemeForme() { return suivanteMemeForme; }
    Piece* getPrecedenteMemeForme() { return precedenteMemeForme; }

    // Setters : fonctions pour d�finir les valeurs des attributs
    void setSuivante(Piece* suiv) { suivante = suiv; }
    void setPrecedente(Piece* prec) { precedente = prec; }
    void setCouleur(const sf::Color& clr) { couleur = clr; }
    void setForme(const std::string& newForme) { forme = newForme;}
    void setSuivanteMemeForme(Piece* suiv) { suivanteMemeForme = suiv; }
    void setPrecedenteMemeForme(Piece* prec) { precedenteMemeForme = prec; }
    // Fonctions pour comparer les attributs avec une autre pi�ce
    bool aMemeForme(Piece* autrePiece) { return this->forme == autrePiece->forme; }
    bool aMemeCouleur(Piece* autrePiece) { return this->couleur == autrePiece->couleur; }
};

///Les classes suivantes d�finissent des formes g�om�triques sp�cifiques en h�ritant de sf::Shape.
///   Chaque classe initialise la forme avec un nombre de points et une couleur sp�cifiques.

///Classe Triangle : forme g�om�trique d'un triangle �quilat�ral
class Triangle : public sf::ConvexShape {
public:
    Triangle(float size, const sf::Color& color) {
        setPointCount(3); // D�finit le nombre de points (sommets) du triangle
        // D�finit les points du triangle pour former un triangle �quilat�ral
        setPoint(0, sf::Vector2f(0, 0));
        setPoint(1, sf::Vector2f(size, 0));
        setPoint(2, sf::Vector2f(size / 2, size * 0.866f)); // Hauteur d'un triangle �quilat�ral
        setFillColor(color); // D�finit la couleur de remplissage du triangle
    }
};

/// Classe Carre : forme g�om�trique d'un carr�
class Carre : public sf::RectangleShape {
public:
    Carre(float size, const sf::Color& color) {
        setSize(sf::Vector2f(size, size)); // D�finit la taille du carr�
        setFillColor(color); // D�finit la couleur de remplissage du carr�
    }
};

/// Classe Losange : forme g�om�trique d'un losange
class Losange : public sf::ConvexShape {
public:
    Losange(float size, const sf::Color& color) {
        setPointCount(4); // D�finit le nombre de points (sommets) du losange
        // D�finit les points du losange pour former la forme sp�cifique
        setPoint(0, sf::Vector2f(size / 2, 0));
        setPoint(1, sf::Vector2f(size, size / 2));
        setPoint(2, sf::Vector2f(size / 2, size));
        setPoint(3, sf::Vector2f(0, size / 2));
        setFillColor(color); // D�finit la couleur de remplissage du losange
    }
};

/// Classe Circle : forme g�om�trique d'un cercle
class Circle : public sf::CircleShape {
public:
    Circle(float radius, const sf::Color& color) {
        setRadius(radius); // D�finit le rayon du cercle
        setFillColor(color); // D�finit la couleur de remplissage du cercle
    }
};



/// D�claration de la classe Plateau qui g�re un ensemble de pi�ces dans un jeu.
class Plateau {
public:
    // Pointeurs vers la premi�re et la derni�re pi�ce de la liste cha�n�e.
    Piece* debut;
    Piece* fin;
    // Score actuel du joueur.
    int score;
    // Indicateur de d�calage effectu� pour les op�rations de jeu.
    bool decalageEffectue;
    // Buffer pour stocker les sons � jouer.
    sf::SoundBuffer buffer;
    // Objet son pour jouer des effets sonores.
    sf::Sound sound;

public:
    // Constructeur par d�faut qui initialise les membres de la classe.
    Plateau() : debut(nullptr), fin(nullptr), score(0), decalageEffectue(false) {}

    // Destructeur qui lib�re la m�moire allou�e pour les pi�ces.
    ~Plateau() {
        while (debut != nullptr) {
            Piece* temp = debut;
            debut = debut->getSuivante();
            delete temp;
        }
    }

    // M�thodes pour ins�rer des pi�ces � gauche ou � droite.
    void insererGauche(Piece* piece);
    void insererDroite(Piece* piece);

    // M�thode pour afficher les pi�ces sur le plateau.
    void afficherPieces(sf::RenderWindow& window, float x, float y);

    // M�thode pour afficher une pi�ce � ins�rer � une position donn�e.
    void afficherPieceAInserer(sf::RenderWindow& window, Piece* piece, float positionX) {
        if (piece != nullptr) {
            sf::Shape* shape = nullptr;
            // Cr�ation d'une forme graphique selon la forme de la pi�ce.
            if (piece->getForme() == "Triangle") {
                shape = new Triangle(50, piece->getCouleur());
            } else if (piece->getForme() == "Carre") {
                shape = new Carre(50, piece->getCouleur());
            } else if (piece->getForme() == "Losange") {
                shape = new Losange(50, piece->getCouleur());
            } else if (piece->getForme() == "Circle") {
                shape = new Circle(25, piece->getCouleur());
            }

            // Si une forme a �t� cr��e, l'afficher puis la supprimer.
            if (shape != nullptr) {
                shape->setPosition(positionX, 50.0f);
                window.draw(*shape);
                delete shape;
            }
        }
    };

    // M�thode pour v�rifier si le plateau est vide.
    bool estVide() const {
        return debut == nullptr;
    };

    /// Diverses m�thodes pour g�rer le score et les op�rations de jeu.
    void score_jeux();
    void supprimer(Piece* piece);
    void supprimerTriplets_memeCouleur();
    void supprimerTriplets_memeForme();
    void decalerParForme(const std::string& forme);
    void decalerParCouleur(const sf::Color& couleur);
    void score_jeux1();
    void setDecalageEffectue(bool value);

    // M�thodes pour afficher le score, le temps, le niveau et d'autres informations.
    void score_Afficher(sf::RenderWindow& window, const sf::Font& font) const;
    int nombreDePieces() const;
    sf::Time timeElapsed;
    void afficherTemps(sf::RenderWindow& window, const sf::Font& font);
    void Level_Afficher(sf::RenderWindow& window, const sf::Font& font);
    void afficherInformations(sf::RenderWindow& window, const sf::Font& font);

    // M�thode pour demander le nom du joueur.
    std::string demanderNomJoueur();

    // M�thode pour afficher le plateau.
    void afficher() const;
};

/// M�thode pour ins�rer une pi�ce � l'extr�mit� Gauche  du plateau.
void Plateau::insererGauche(Piece* piece) {
    if (!debut) {
        debut = piece;
        fin = piece;
    }
    else {
        piece->setSuivante(debut);
        debut->setPrecedente(piece);
        debut = piece;

        // Mettre � jour les liens avec les pi�ces de m�me forme
        Piece* current = piece->getSuivante();
        while (current != nullptr && current != piece) {
            if (current->getForme() == piece->getForme()) {
                piece->setSuivanteMemeForme(current);
                current->setPrecedenteMemeForme(piece);
                break; // Ne cherchez que la premi�re pi�ce de m�me forme � droite
            }
            current = current->getSuivante();
        }
    }
}

/// M�thode pour ins�rer une pi�ce � l'extr�mit� droite du plateau.
void Plateau::insererDroite(Piece* piece) {
    // Si le plateau est vide, initialisez-le avec la nouvelle pi�ce.
    if (!debut) {
        debut = piece;
        fin = piece;
    }
    else {
        // Sinon, liez la nouvelle pi�ce � la fin de la liste cha�n�e.
        piece->setPrecedente(fin);
        fin->setSuivante(piece);
        fin = piece;

        // Mettre � jour les liens avec les pi�ces de m�me forme.
        Piece* current = piece->getPrecedente();
        while (current != nullptr && current != piece) {
            if (current->getForme() == piece->getForme()) {
                piece->setPrecedenteMemeForme(current);
                current->setSuivanteMemeForme(piece);
                break; // Arr�tez la recherche apr�s avoir trouv� la premi�re correspondance.
            }
            current = current->getPrecedente();
        }
    }
}


/// M�thode pour afficher toutes les pi�ces pr�sentes sur le plateau
void Plateau::afficherPieces(sf::RenderWindow& window, float x, float y) {
    float posX = x;
    float posY = y;
    Piece* current = debut;

     // Parcourez chaque pi�ce et cr�ez une forme graphique correspondante.
    while (current != nullptr) {
        sf::Shape* shape = nullptr;
        // Cr�ez une forme en fonction de la forme de la pi�ce
        if (current->getForme() == "Triangle") {
            shape = new Triangle(50, current->getCouleur()); // Triangle size
        }
        else if (current->getForme() == "Carre") {
            shape = new Carre(50, current->getCouleur()); // Square size
        }
        else if (current->getForme() == "Losange") {
            shape = new Losange(50, current->getCouleur()); // Losange size
        }
        else if (current->getForme() == "Circle") {
            shape = new Circle(25, current->getCouleur()); // Circle radius
        }
        // Add conditions for other piece shapes...

        if (shape != nullptr) {
            shape->setPosition(posX, posY);
            window.draw(*shape);
            delete shape; // Free dynamically allocated memory
        }
   // D�placez la position X pour la prochaine pi�ce
        posX += 100.0f;
        current = current->getSuivante();
    }
}


/// M�thode pour supprimer une pi�ce sp�cifique du plateau.
void Plateau::supprimer(Piece* piece_supprimer) {
    // Si le plateau est vide, il n'y a rien � faire.
    if (!debut) {
        cout << "Le plateau est vide !!!\n";
        return;
    }
    // G�rez la suppression de la pi�ce en fonction de sa position.
    if (piece_supprimer == debut && piece_supprimer == fin) {
    // Si c'est la seule pi�ce, videz le plateau.
        debut = nullptr;
        fin = nullptr;
    }
    else if (piece_supprimer == debut) {
    // Si c'est la premi�re pi�ce, mettez � jour le d�but.
        debut = debut->getSuivante();
        debut->setPrecedente(nullptr);
    }
    else if (piece_supprimer == fin) {
    // Si c'est la derni�re pi�ce, mettez � jour la fin.
        fin = fin->getPrecedente();
        fin->setSuivante(nullptr);
    }
    else {
        // Sinon, reliez les pi�ces pr�c�dente et suivante entre elles.
        piece_supprimer->getPrecedente()->setSuivante(piece_supprimer->getSuivante());
        piece_supprimer->getSuivante()->setPrecedente(piece_supprimer->getPrecedente());
    }
    // Lib�rez la m�moire allou�e pour la pi�ce supprim�e.
    delete piece_supprimer;
}
/// M�thode pour supprimer les triplets de pi�ces de m�me couleur.
void Plateau::supprimerTriplets_memeCouleur() {
    // V�rifiez si le plateau est vide avant de commencer.
    if (!debut) {
        cout << "Le plateau est vide." << endl;
        return;
    }

    // Commencez par la premi�re pi�ce.
    Piece* currentPiece = debut;
    // Continuez tant qu'il y a des pi�ces sur le plateau.
    while (currentPiece != nullptr) {
        // Obtenez la pi�ce suivante dans la liste.
        Piece* nextPiece = currentPiece->getSuivante();
        // Si la fin de la liste est atteinte, arr�tez la boucle.
        if (nextPiece == nullptr) break;
        // Obtenez la pi�ce apr�s la suivante.
        Piece* nextNextPiece = nextPiece->getSuivante();

        // Si la fin de la liste est atteinte, arr�tez la boucle.
        if (nextNextPiece == nullptr) break;
        // V�rifiez si les trois pi�ces cons�cutives ont la m�me couleur.
        if (currentPiece->getCouleur() == nextPiece->getCouleur() && nextPiece->getCouleur() == nextNextPiece->getCouleur()) {
            // Si oui, supprimez ces trois pi�ces.
            supprimer(currentPiece);
            supprimer(nextPiece);
            supprimer(nextNextPiece);
            // Mettez � jour le score apr�s la suppression.
            score_jeux();
            // Recommencez � partir du d�but de la liste.
            currentPiece = debut;
            continue;
        }

        // Passez � la pi�ce suivante dans la liste.
        currentPiece = currentPiece->getSuivante();
    }
}


/// M�thode pour supprimer les triplets de pi�ces de m�me forme.
void Plateau::supprimerTriplets_memeForme() {
    // V�rifiez si le plateau est vide avant de commencer.
    if (!debut) {
        cout << "Le plateau est vide." << endl;
        return;
    }

    // Commencez par la premi�re pi�ce.
    Piece* currentPiece = debut;
    // Continuez tant qu'il y a des pi�ces sur le plateau.
    while (currentPiece != nullptr) {
        // Obtenez la pi�ce suivante dans la liste.
        Piece* nextPiece = currentPiece->getSuivante();
        // Si la fin de la liste est atteinte, arr�tez la boucle.
        if (nextPiece == nullptr) break;
        // Obtenez la pi�ce apr�s la suivante.
        Piece* nextNextPiece = nextPiece->getSuivante();

        // Si la fin de la liste est atteinte, arr�tez la boucle.
        if (nextNextPiece == nullptr) break;
        // V�rifiez si les trois pi�ces cons�cutives ont la m�me forme.
        if (currentPiece->getForme() == nextPiece->getForme() && nextPiece->getForme() == nextNextPiece->getForme()) {
            // Si oui, supprimez ces trois pi�ces.
            supprimer(currentPiece);
            supprimer(nextPiece);
            supprimer(nextNextPiece);
            // Mettez � jour le score apr�s la suppression.
            score_jeux();
            // Recommencez � partir du d�but de la liste.
            currentPiece = debut;
            continue;
        }

        // Passez � la pi�ce suivante dans la liste.
        currentPiece = currentPiece->getSuivante();
    }
}


///Fonction pour obtenir le nom d'une couleur SFML sous forme de cha�ne de caract�res.
std::string getColorName(const sf::Color& color) {
    // Compare la couleur pass�e en param�tre avec les couleurs pr�d�finies de SFML.
    if (color == sf::Color::Red) {
        return "Red"; // Retourne "Red" si la couleur est rouge.
    }
    else if (color == sf::Color::Green) {
        return "Green"; // Retourne "Green" si la couleur est verte.
    }
    else if (color == sf::Color::Blue) {
        return "Blue"; // Retourne "Blue" si la couleur est bleue.
    }
    else if (color == sf::Color::Yellow) {
        return "Yellow"; // Retourne "Yellow" si la couleur est jaune.
    }
    else {
        return "Unknown"; // Retourne "Unknown" si la couleur ne correspond � aucune des couleurs pr�d�finies.
    }
}





/// M�thode pour d�caler les couleurs des pi�ces ayant une forme sp�cifique.
void Plateau::decalerParForme(const std::string& forme) {
    // Initialisation de l'indicateur de d�calage � false.
    decalageEffectue = false;
    // V�rifiez si le plateau est vide avant de commencer.
    if (!debut) {
        cout << "Le plateau est vide." << endl;
        return;
    }

    // Commencez par la derni�re pi�ce.
    Piece* curr = fin;
    int count = 0; // Compteur pour le nombre de d�calages effectu�s.
    do {
        // Recherchez la premi�re pi�ce de la forme sp�cifi�e en remontant la liste.
        while ((curr->getForme() != forme) && curr->getPrecedente() != fin) {
            curr = curr->getPrecedente();
        }
        // Si une pi�ce de la forme sp�cifi�e est trouv�e, proc�dez au d�calage.
        if (curr->getForme() == forme) {
            count++;
            // Sauvegardez la couleur de la pi�ce actuelle.
            sf::Color couleurTmp1 = curr->getCouleur();
            // Trouvez la pi�ce pr�c�dente de la m�me forme.
            Piece* first = curr->getPrecedente();
            while (first && first->getForme() != forme && first != fin) {
                first = first->getPrecedente();
            }
            // Si une telle pi�ce est trouv�e, �changez les couleurs.
            if (first && first->getForme() == forme) {
                count++;
                sf::Color couleurTmp2 = first->getCouleur();
                first->setCouleur(couleurTmp1);
                // Trouvez la pi�ce encore pr�c�dente de la m�me forme.
                Piece* second = first->getPrecedente();
                while (second && second->getForme() != forme && second != fin) {
                    second = second->getPrecedente();
                }
                // Si une telle pi�ce est trouv�e, �changez les couleurs.
                if (second && second->getForme() == forme) {
                    count++;
                    sf::Color couleurTmp3 = second->getCouleur();
                    second->setCouleur(couleurTmp2);
                    curr->setCouleur(couleurTmp3);
                    // Indiquez qu'un d�calage a �t� effectu�.
                    decalageEffectue = true;
                }
            }
        }
        else {
            // Si aucune pi�ce de la forme sp�cifi�e n'est trouv�e, terminez la fonction.
            return;
        }
    // Continuez tant que moins de trois d�calages ont �t� effectu�s et que le d�but n'est pas atteint.
    } while (count < 3 && curr != debut);
}



/// Convertit une cha�ne de caract�res repr�sentant une couleur en un objet sf::Color.
sf::Color stringToColor(const std::string& couleur) {
    if (couleur == "Green") {
        return sf::Color::Green; // Retourne la couleur verte.
    }
    else if (couleur == "Red") {
        return sf::Color::Red; // Retourne la couleur rouge.
    }
    else if (couleur == "Yellow") {
        return sf::Color::Yellow; // Retourne la couleur jaune.
    }
    else if (couleur == "Blue") {
        return sf::Color::Blue; // Retourne la couleur bleue.
    }
    // Si la cha�ne ne correspond � aucune couleur connue, retourne noir par d�faut.
    return sf::Color::Black;
}

/// Convertit un objet sf::Color en une cha�ne de caract�res repr�sentant la couleur.
std::string colorToString(const sf::Color& color) {
    if (color == sf::Color::Green) {
        return "Green"; // Si la couleur est verte, retourne "Green".
    }
    else if (color == sf::Color::Red) {
        return "Red"; // Si la couleur est rouge, retourne "Red".
    }
    else if (color == sf::Color::Yellow) {
        return "Yellow"; // Si la couleur est jaune, retourne "Yellow".
    }
    else if (color == sf::Color::Blue) {
        return "Blue"; // Si la couleur est bleue, retourne "Blue".
    }
    else {
        return "Unknown"; // Si la couleur n'est pas reconnue, retourne "Unknown".
    }
}




/// M�thode pour d�caler les formes des pi�ces ayant une couleur sp�cifique.
void Plateau::decalerParCouleur(const sf::Color& couleur) {
    // Initialisation de l'indicateur de d�calage � false.
    decalageEffectue = false;
    // V�rifiez si le plateau est vide avant de commencer.
    if (!debut) {
        cout << "Le plateau est vide." << endl;
        return;
    }

    // Commencez par la derni�re pi�ce.
    Piece* curr = fin;
    int count = 0; // Compteur pour le nombre de d�calages effectu�s.
    do {
        // Recherchez la premi�re pi�ce de la couleur sp�cifi�e en remontant la liste.
        while ((curr->getCouleur() != couleur) && curr->getPrecedente() != fin) {
            curr = curr->getPrecedente();
        }
        // Si une pi�ce de la couleur sp�cifi�e est trouv�e, proc�dez au d�calage.
        if (curr->getCouleur() == couleur) {
            count++;
            // Sauvegardez la forme de la pi�ce actuelle.
            std::string formeTmp1 = curr->getForme();
            // Trouvez la pi�ce pr�c�dente de la m�me couleur.
            Piece* first = curr->getPrecedente();
            while (first && first->getCouleur() != couleur && first != fin) {
                first = first->getPrecedente();
            }
            // Si une telle pi�ce est trouv�e, �changez les formes.
            if (first && first->getCouleur() == couleur) {
                count++;
                std::string formeTmp2 = first->getForme();
                first->setForme(formeTmp1);
                // Trouvez la pi�ce encore pr�c�dente de la m�me couleur.
                Piece* second = first->getPrecedente();
                while (second && second->getCouleur() != couleur && second != fin) {
                    second = second->getPrecedente();
                }
                // Si une telle pi�ce est trouv�e, �changez les formes.
                if (second && second->getCouleur() == couleur) {
                    count++;
                    std::string formeTmp3 = second->getForme();
                    second->setForme(formeTmp2);
                    curr->setForme(formeTmp3);
                    // Indiquez qu'un d�calage a �t� effectu�.
                    decalageEffectue = true;
                }
            }
        }
        else {
            // Si aucune pi�ce de la couleur sp�cifi�e n'est trouv�e, terminez la fonction.
            return;
        }
    // Continuez tant que moins de trois d�calages ont �t� effectu�s et que le d�but n'est pas atteint.
    } while (count < 3 && curr != debut);
}






///M�thode pour mettre � jour le score du jeu et le niveau en fonction des actions effectu�es.
void Plateau::score_jeux() {
    // R�initialiser le niveau du jeu � 0.
    etatJeu.niveau = 0;

    // Charger le fichier sonore pour le score. Si le chargement �choue, afficher une erreur et quitter la m�thode.
    if (!buffer.loadFromFile("sonScore.WAV")) {
        std::cerr << "Erreur lors du chargement du fichier son" << std::endl;
        return;
    }

    // Associer le buffer sonore � l'objet sound.
    sound.setBuffer(buffer);

    // Si le score est sup�rieur � 5, incr�menter le niveau du jeu.
    if (score > 5) {
        etatJeu.niveau++;
    }

    // Si un d�calage a �t� effectu�, ajouter 5 au score et r�initialiser l'indicateur de d�calage.
    if (decalageEffectue) {
        score += 5;
        decalageEffectue = false;
    } else {
        // Sinon, incr�menter simplement le score.
        score++;
    }

    // Jouer le son du score.
    sound.play();
}

/// M�thode pour compter le nombre de pi�ces pr�sentes sur le plateau.
int Plateau::nombreDePieces() const {
    int count = 0; // Initialiser le compteur de pi�ces � 0.
    Piece* current = debut; // Commencer par la premi�re pi�ce.

    // Parcourir la liste cha�n�e de pi�ces et compter chaque pi�ce.
    while (current != nullptr) {
        count++;
        current = current->getSuivante();
    }

    // Retourner le nombre total de pi�ces.
    return count;
}



  /// M�thode pour afficher le score actuel dans la fen�tre de jeu.
void Plateau::score_Afficher(sf::RenderWindow& window, const sf::Font& font) const {
    // Cr�ation et configuration du texte � afficher.
    sf::Text scoreText("Score: " + std::to_string(score), font);
    scoreText.setCharacterSize(24); // Taille des caract�res
    scoreText.setStyle(sf::Text::Bold); // Style du texte
    scoreText.setPosition(10, 10); // Position du texte dans la fen�tre
    scoreText.setFillColor(sf::Color::White); // Couleur du texte
    window.draw(scoreText); // Dessiner le texte dans la fen�tre

    etatJeu.score = score; // Mise � jour du score dans l'�tat du jeu
}

/// M�thode pour afficher le temps �coul� dans la fen�tre de jeu.
void Plateau::afficherTemps(sf::RenderWindow& window, const sf::Font& font) {
    // Cr�ation et configuration du texte � afficher.
    sf::Text timeText("Time: " + std::to_string(timeElapsed.asSeconds()), font);
    timeText.setCharacterSize(24); // Taille des caract�res
    timeText.setStyle(sf::Text::Bold); // Style du texte
    timeText.setPosition(10, 40); // Position du texte dans la fen�tre
    timeText.setFillColor(sf::Color::White); // Couleur du texte
    window.draw(timeText); // Dessiner le texte dans la fen�tre

    etatJeu.temps = timeElapsed.asSeconds(); // Mise � jour du temps dans l'�tat du jeu
}

/// M�thode pour afficher le niveau actuel dans la fen�tre de jeu.
void Plateau::Level_Afficher(sf::RenderWindow& window, const sf::Font& font) {
    // Cr�ation et configuration du texte � afficher.
    sf::Text LevelText("Level: " + std::to_string(etatJeu.niveau), font);
    LevelText.setCharacterSize(24); // Taille des caract�res
    LevelText.setStyle(sf::Text::Bold); // Style du texte
    LevelText.setPosition(10, 70); // Position du texte dans la fen�tre
    LevelText.setFillColor(sf::Color::White); // Couleur du texte
    window.draw(LevelText); // Dessiner le texte dans la fen�tre
}

/// M�thode pour demander et retourner le nom du joueur.
std::string Plateau::demanderNomJoueur() {
    std::cout << "Entrez votre nom: "; // Demande d'entr�e � l'utilisateur
    std::cin >> etatJeu.nomJoueur; // Lecture du nom du joueur
    return etatJeu.nomJoueur; // Retour du nom du joueur
}


///Fonction pour afficher les informations du joueur dans la fen�tre de jeu.
void Plateau::afficherInformations(sf::RenderWindow& window, const sf::Font& font) {
    // Cr�ation et configuration du texte � afficher.
    sf::Text joueurText("Joueur: " + etatJeu.nomJoueur, font);
    joueurText.setCharacterSize(24); // Taille des caract�res
    joueurText.setStyle(sf::Text::Bold); // Style du texte
    joueurText.setPosition(10, 100); // Position du texte dans la fen�tre
    joueurText.setFillColor(sf::Color::White); // Couleur du texte
    window.draw(joueurText); // Dessiner le texte dans la fen�tre
}

/// Fonction pour sauvegarder l'�tat du jeu dans un fichier texte.
void sauvegarderEtatJeu(const EtatJeu& etat) {
    // Ouvrir un fichier texte en mode ajout.
    std::ofstream fichier("etatJeu.txt", std::ios::app);
    if (fichier.is_open()) {
        // �crire les informations du joueur dans le fichier.
        fichier << "Nom du Joueur: " << etat.nomJoueur << std::endl;
        fichier << "Score: " << etat.score << std::endl;
        fichier << "Temps: " << etat.temps << "s" << std::endl;
        fichier << "Niveau: " << etat.niveau << std::endl;
        fichier << "--------------------------" << std::endl;
        fichier.close(); // Fermer le fichier apr�s l'�criture.
    } else {
        // Afficher une erreur si le fichier ne peut pas �tre ouvert.
        std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
    }
}

/// Fonction pour charger l'�tat du jeu � partir d'un fichier texte.
EtatJeu chargerEtatJeu(const std::string& nomFichier) {
    // Ouvrir le fichier texte en mode lecture.
    std::ifstream fichier(nomFichier);
    EtatJeu etatJeu; // Cr�er une instance de EtatJeu pour stocker les informations.
    if (fichier.is_open()) {
        // Lire les informations du fichier et les stocker dans l'instance de EtatJeu.
        std::getline(fichier, etatJeu.nomJoueur);
        fichier >> etatJeu.score;
        fichier >> etatJeu.niveau;
        fichier >> etatJeu.temps;
        fichier.close(); // Fermer le fichier apr�s la lecture.
    }
    return etatJeu; // Retourner l'instance de EtatJeu avec les informations charg�es.
}


#endif // PLATEAU_H_INCLUDED

