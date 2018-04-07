#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;

   g.lecture_vertex("sommetschaine_2.txt");
   g.lecture_edge("areteschaine_2.txt");

   g.afficher_les_comp_fort_connexe();

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    g.ecriture_vertex("sommetschaine_2.txt");
    g.ecriture_edge("areteschaine_2.txt");

    grman::fermer_allegro();

    return 0;

// yooooooooooooooooo
}
END_OF_MAIN();


