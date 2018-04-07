#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;



    int choix;
    std::string choixsommet;
    std::string choixarete;

    choixsommet="sommetschaine_2.txt";
    choixarete="areteschaine_2.txt";


    g.lecture_vertex(choixsommet);
    g.lecture_edge(choixarete);
//g.m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.dynamisme();
        g.update(choixsommet, choixarete);


        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();



    }



    grman::fermer_allegro();

    return 0;

// yooooooooooooooooo
}
END_OF_MAIN();


