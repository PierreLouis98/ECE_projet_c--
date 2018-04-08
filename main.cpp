#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{



    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;



    int choix;
    std::string choixsommet;
    std::string choixarete;

    std::cout << "quel graphe voulez vous ouvrir : 1, 2 ou 3 ?"<< std::endl;


    std::cin>>choix;
    switch (choix)
    {
    case 1:
        choixsommet="sommetschaine_1.txt";
        choixarete="areteschaine_1.txt";
        break;
    case 2:
        choixsommet="sommetschaine_2.txt";
        choixarete="areteschaine_2.txt";
        break;
    case 3:
        choixsommet="sommetschaine_3.txt";
        choixarete="areteschaine_3.txt";
        break;
    }
/// A appeler en 1er avant d'instancier des objets graphiques etc...

    grman::init();
    g.lecture_vertex(choixsommet);
    g.lecture_edge(choixarete);


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets

        g.update(choixsommet, choixarete);


        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();



    }



    grman::fermer_allegro();

    return 0;

// yooooooooooooooooo
}
END_OF_MAIN();


