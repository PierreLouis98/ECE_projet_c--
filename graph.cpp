#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );

    /// TEST
    m_top_box.add_child( m_marche );
    m_marche.set_dim(8, 8);
    m_marche.set_pos(17,88);
    m_marche.set_bg_color(ROUGE);
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(225,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    // TEST
/// PREMIERE CASE:
       /// On ajoute en haut à droite la boite à boutons
    m_top_box.add_child( m_boite );
    m_boite.set_dim(50,40);
    m_boite.set_pos(12,12);
    m_boite.set_bg_color(FUCHSIACLAIR);

    /// Puis un 1er bouton avec un texte
    m_boite.add_child( m_bouton );
    m_bouton.set_frame(3,3,50,40);
    m_bouton.set_bg_color(FUCHSIA);

    m_bouton.add_child(m_bouton_label);
    m_bouton_label.set_message("SAVE");

/// SECONDE CASE:
       /// On ajoute en haut à droite la boite à boutons
    m_top_box.add_child( m_boite2 );
    m_boite2.set_dim(50,40);
    m_boite2.set_pos(12,62);
    m_boite2.set_bg_color(FUCHSIACLAIR);

    /// Puis un 1er bouton avec un texte
    m_boite2.add_child( m_bouton2 );
    m_bouton2.set_frame(3,3,50,40);
    m_bouton2.set_bg_color(FUCHSIA);

    m_bouton2.add_child(m_bouton_label2);
    m_bouton_label2.set_message("OPEN 1 ");

/// TROISIEME CASE:
       /// On ajoute en haut à droite la boite à boutons
    m_top_box.add_child( m_boite3 );
    m_boite3.set_dim(140,30);
    m_boite3.set_pos(850,10);
    m_boite3.set_bg_color(FUCHSIACLAIR);

    /// Puis un 1er bouton avec un texte
    m_boite3.add_child( m_bouton3);
    m_bouton3.set_frame(3,3,140,30);
    m_bouton3.set_bg_color(FUCHSIA);

    m_bouton3.add_child(m_bouton_label3);
    m_bouton_label3.set_message("AJOUTER UN SOMMET");

/// QUATRIEME CASE:
       /// On ajoute en haut à droite la boite à boutons
    m_top_box.add_child( m_boite4 );
    m_boite4.set_dim(50,40);
    m_boite4.set_pos(12,112);
    m_boite4.set_bg_color(FUCHSIACLAIR);

    /// Puis un 1er bouton avec un texte
    m_boite4.add_child( m_bouton4 );
    m_bouton4.set_frame(3,3,50,40);
    m_bouton4.set_bg_color(FUCHSIA);

    m_bouton4.add_child(m_bouton_label4);
    m_bouton_label4.set_message("OPEN 2");

/// CINQUIEME CASE:
       /// On ajoute en haut à droite la boite à boutons
    m_top_box.add_child( m_boite5 );
    m_boite5.set_dim(50,40);
    m_boite5.set_pos(12,162);
    m_boite5.set_bg_color(FUCHSIACLAIR);

    /// Puis un 1er bouton avec un texte
    m_boite5.add_child( m_bouton5 );
    m_bouton5.set_frame(3,3,50,40);
    m_bouton5.set_bg_color(FUCHSIA);

    m_bouton5.add_child(m_bouton_label5);
    m_bouton_label5.set_message("OPEN 3");


 /// SIXIEME BOUTTON CASE:
       /// On ajoute en haut à droite la boite à boutons
    m_top_box.add_child( m_boite6 );
    m_boite6.set_dim(140,30);
    m_boite6.set_pos(850,50);
    m_boite6.set_bg_color(FUCHSIACLAIR);

    m_boite6.add_child( m_bouton6);
    m_bouton6.set_frame(3,3,140,30);
    m_bouton6.set_bg_color(FUCHSIA);

    m_bouton6.add_child(m_bouton_label6);
    m_bouton_label6.set_message("AJOUTER UNE ARETE");

     /// SEPTIEME BOUTTON CASE:
       /// On ajoute en haut à droite la boite à boutons
    m_top_box.add_child( m_boite7 );
    m_boite7.set_dim(140,30);
    m_boite7.set_pos(850,90);
    m_boite7.set_bg_color(FUCHSIACLAIR);

    m_boite7.add_child( m_bouton7);
    m_bouton7.set_frame(3,3,140,30);
    m_bouton7.set_bg_color(FUCHSIA);

    m_bouton7.add_child(m_bouton_label7);
    m_bouton_label7.set_message("SUPPRIMER UNE ARETE");
}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(8,69.0, 150, 250, "renard.jpg");
    add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 2, 50.0);
    add_interfaced_edge(1, 0, 1, 50.0);
    add_interfaced_edge(2, 1, 3, 75.0);
    add_interfaced_edge(3, 4, 1, 25.0);
    add_interfaced_edge(4, 6, 3, 25.0);
    add_interfaced_edge(5, 7, 3, 25.0);
    add_interfaced_edge(6, 3, 4, 0.0);
    add_interfaced_edge(7, 2, 0, 100.0);
    add_interfaced_edge(8, 5, 2, 20.0);
    add_interfaced_edge(9, 3, 7, 80.0);
}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

    // AJOUTER UN SOMMET

    if ( m_interface->m_bouton3.clicked() )
    {
        std::cout << "NEW !" << std::endl;
        ajouter_sommet();
    }

        if ( m_interface->m_bouton6.clicked() )
    {
        std::cout << "NEW !" << std::endl;
        ajouter_arete();
    }

        if ( m_interface->m_bouton7.clicked() )
{
    int choix;
            std::cout << "quelle arete voulez vous supprimer ? " << std::endl;
            std::cin >>choix;
            test_remove_edge(choix);


}

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
    m_edges[idx].m_from=id_vert1;
    m_edges[idx].m_to=id_vert2;

    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
}

void Graph::lecture_vertex(std::string nom_fichier)
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    std::ifstream fichier(nom_fichier);
    if(fichier)
    {
        std::string nom_image;
        int indice,posx,posy;
        double value;
        while(fichier >>indice)
        {
            fichier >>value>>posx>>posy>>nom_image;
            add_interfaced_vertex(indice,value, posx, posy, nom_image);
        }
        fichier.close();
    }
    else
        std::cout<<"error : "<<nom_fichier<<std::endl;
}

void Graph::lecture_edge(std::string nom_fichier)
{
    std::ifstream fichier(nom_fichier);
    if(fichier)
    {
        std::string nom_image;
        int indice,id_vert1,id_vert2;
        double poid;
        while(fichier >>indice)
        {
            fichier >>id_vert1>>id_vert2>>poid;
            add_interfaced_edge(indice,id_vert1,id_vert2,poid);
        }
        fichier.close();
    }
    else
        std::cout<<"error : "<<nom_fichier<<std::endl;
}


void Graph::ecriture_vertex(std::string nom_fichier)
{
    std::ofstream fichier(nom_fichier, std::ios::out | std::ios::trunc);
    if(fichier)
    {
        for (const auto& elem : m_vertices)
        {
            fichier<< elem.first<<" "<<elem.second.m_value<<" "<<elem.second.m_interface->m_top_box.get_posx()<<" "<<elem.second.m_interface->m_top_box.get_posy()<<" "<<elem.second.m_interface->m_img.get_pic_name()<<std::endl;
        }

        fichier.close();
    }

    else
        std::cout<<"error : "<<nom_fichier<<std::endl;
}

void Graph::ecriture_edge(std::string nom_fichier)
{
    std::ofstream fichier(nom_fichier, std::ios::out | std::ios::trunc);
    if(fichier)
    {
        for (const auto& elem : m_edges)
        {
            fichier<< elem.first<<" "<<elem.second.m_from<<" "<<elem.second.m_to<<" "<<elem.second.m_weight<< std::endl;
            std::cout<<"ok"<<std::endl;
        }

        fichier.close();
    }

    else
        std::cout<<"error : "<<nom_fichier<<std::endl;
}

void Graph::ajouter_sommet()
{
int sommet_max=-1;
std::string espece;


       for (const auto& elem : m_vertices)
        {
            if (elem.first>sommet_max)
                sommet_max=elem.first;
        }

        std::cout << "choisissez une espece"<< std::endl;
        afficher_les_sommets();
std::cin>> espece ;

        add_interfaced_vertex(sommet_max+1,50,20,20,espece+".jpg");

}


void Graph::ajouter_arete()
{
    int arete_max=-1;
int predateur;
int proie;


        for (const auto& elem : m_edges)
        {

                if (elem.first>arete_max)
                arete_max=elem.first;
        }

afficher_les_sommets();

        std::cout << "PREDATEUR :"<< std::endl;
std::cin>> predateur ;
        std::cout << "PROIE"<< std::endl;
std::cin>> proie ;


add_interfaced_edge(arete_max+1,predateur, proie,50);
}

void Graph::afficher_les_sommets()
  {
      int  i=0;
     std::string chaine;
       for (const auto& elem : m_vertices)
        {
            chaine=elem.second.m_interface->m_img.get_pic_name();
            std::cout<<i << " " << chaine<<std::endl;
            i++;
        }

}


void Graph::test_remove_edge(int eidx)
{
/// référence vers le Edge à enlever
Edge &remed=m_edges.at(eidx);

std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

/// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
std::cout << m_edges.size() << std::endl;

/// test : on a bien des éléments interfacés
if (m_interface && remed.m_interface)
{
/// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
/* EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
/* m_interface->m_main_box.add_child(ei->m_top_edge); */
/* m_edges[idx] = Edge(weight, ei); */
/// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
/// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
/// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
}

/// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
/// References sur les listes de edges des sommets from et to
std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
std::vector<int> &veto = m_vertices[remed.m_to].m_in;
vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

/// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
/// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
/// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
m_edges.erase( eidx );

/// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
std::cout << m_edges.size() << std::endl;

}


std::vector<bool> Graph::uneComposanteFortementConnexe (unsigned int ordre, int s)
{
    //Variables locales
    std::vector<bool> c1(ordre, FALSE); // composantes connexes directes partant de s
    std::vector<bool> c2(ordre, FALSE);  // composantes connexes indirectes arrivant vers s
    std::vector<bool> c(ordre, FALSE) ; // composante fortement connexe = c1  c2 à retourner
    std::vector<bool> marques(ordre, FALSE) ; // tableau dynamique indiquant si les sommets sont marqués ou non
    unsigned int x, y ; // numéros de sommets intermédiaires des composantes connexes
    int ajout; // booléen indiquant si une nouvelle composante connexe est ajoutée


    // Rendre le sommet s connexe
    c1[s] = true;
    c2[s] = true;
    ajout = 1;

    // Recherche des composantes connexes partant de s à ajouter dans c1 :
    while (ajout == 1)
    {
         ajout = 0; // à chaque tour, recherche d’une nouvelle composante connexe à ajouter
        // Pour tous les sommets x non marqués et connectés en partant de s
        // Marquer chaque sommet x et connecter les sommets non marqués y adjacents à x
        for (x=0 ; x<ordre ; x++)
        {
            if (marques[x]==0 && c1[x]==1)
            {
                marques[x] = 1 ;
                for (y=0 ; y<ordre ; y++)
                {
                    if (m_adj[x][y]==1 && marques[y]==0)
                    {
                        if (c1[y] == 0)
                            c1[y] = 1 ;
                        if ( ajout == 0)
                            ajout = 1 ; // nouvelle composante connexe ajoutée
                    }
                 }
            }
        }
    }

    // Recherche des composantes connexes arrivant à s à ajouter dans c2 :
    while (ajout)
    {
         ajout = 0; // à chaque tour, recherche d’une nouvelle composante connexe à ajouter
        // Pour tous les sommets x non marqués et connectés en partant de s
        // Marquer chaque sommet x et connecter les sommets non marqués y adjacents à x
        for (x=0 ; x<ordre ; x++)
        {
            if (marques[x]==0 && c2[x]==1)
            {
                marques[x] = 1 ;
                for (y=0 ; y<ordre ; y++)
                {
                    if (m_adj[x][y]== -1 && marques[y]==0)
                    {
                        c2[y] = 1 ;
                        ajout = 1 ; // nouvelle composante connexe ajoutée
                    }
                 }
            }
        }
    }


    // Composante fortement connexe c = intersection de c1 et c2
    for (x=0 ; x<ordre ; x++)
        c[x] = c1[x] & c2[x] ;
    // Retourner la composante fortement connexe c

    for (unsigned int g = 0; g < c.size(); g++)
    {
        if (c[g] == 0 && c[s])
            c[s] = 0;
        // ATTENTION AUX ARETES QUI PARTENT ET REJOINGNENT LE MEME SOMMET !!!!
    }

    return c ;
}


std::vector<std::vector<bool>> Graph::toutesLesComposantesFortementConnexes()
{
    // Variables locales
    std::vector<std::vector<bool>> tabc ; // tableau dynamique des composantes fortement connexes à retourner
    std::vector<bool> marques ; // tableau dynamique indiquant si les sommets sont marqués ou non
    std::vector<bool> non_nul;
    int x, y ; // numéros de sommets intermédiaires comme indices des tableaux
    int blablacar; // nombre de sommets
    int monsieur = 0;

    blablacar = m_vertices.size();

    // Initialiser les valeurs de ces tableaux à 0

   // for (int j = 0; j < blablacar; j++)
     //   tabc.push_back(std::vector<bool>(blablacar,FALSE));

    for (int l = 0; l < blablacar; l++)
        marques.push_back(FALSE);

    // Pour tous les sommets x non marqués
    // Rechercher la composante fortement connexe de x
    // Marquer chaque sommet x et marquer les sommets y connectés à x et non marqués
    for (x=0 ; x<blablacar ; x++)
    {
        if (!marques[x])
        {
        //    tabc[x] = uneComposanteFortementConnexe(blablacar, x) ;
        // ATTENTION IL FAUT PUSH_BACK LA PREMIERE LIGNE AUSSI (X)
  /*          non_nul = uneComposanteFortementConnexe(blablacar, x);
            for(int h = 0; h < blablacar; h++)
            {
                if(non_nul[h] == 0)
                    monsieur ++;
            }
            if (monsieur != blablacar)*/
                tabc.push_back(uneComposanteFortementConnexe(blablacar, x));
        // AFFICHER POUR VOIR
            marques[x] = 1;
            for (y=0 ; y<blablacar ; y++)
            {
                if (tabc[x][y] && !marques[y])
                    marques[y] = 1;
            }
            /* EXEMPLE:
            (0) (1)<-->(2)
            0: {1,0,0}
            1: {0,1,1} */
        }
     }
    return tabc ;
}


void Graph::remplir_mat_dadj()
{
    /// test
    std::vector<bool> grosse_chiasse;
    std::vector<std::vector<bool>> enorme_chiasse;

   // std::vector<std::vector<int>> m_adj;
    int from, to;
    unsigned int blablacar; // nombre de sommets

    blablacar = m_vertices.size();

    for (unsigned int j = 0; j < blablacar; j++)
        m_adj.push_back(std::vector<int>(blablacar,0));

    for (unsigned int i = 0; i < m_edges.size(); i++)
    {
        from = m_edges[i].m_from;
        to = m_edges[i].m_to;
        m_adj[from][to] = 1;
        m_adj[to][from] = -1;
    }

    m_adj[0][0] = 0;

    /// AFFICHAGE DE LA MATRICE
    std::cout << "Matrice d'adjacence:" << std::endl << "x ";
    for (unsigned int w = 0; w < blablacar; w++)
    {
        std::cout << w << " ";
    }
    std::cout << std::endl;
    for (unsigned int x = 0; x < blablacar; x++)
    {
        std::cout << x << " ";
           for (unsigned int y = 0; y < blablacar; y++)
        {
            std::cout << m_adj[x][y] << " ";
        }
        std::cout << std::endl;
    }


   // grosse_chiasse = uneComposanteFortementConnexe (blablacar, 3);
    enorme_chiasse = toutesLesComposantesFortementConnexes();
  /*  std::cout << std::endl;
    std::cout << "Composants fortement connexe du sommet : " << std::endl;
    for(unsigned int youhou = 0; youhou < grosse_chiasse.size(); youhou++)
        std::cout << grosse_chiasse[youhou] << std::endl;*/
}


void Graph::afficher_les_comp_fort_connexe()
{
    std::vector<std::vector<bool>> resultat;
    remplir_mat_dadj();

    resultat = toutesLesComposantesFortementConnexes();


    for (unsigned int i = 0; i < resultat.size(); i++)
    {
        std::cout << i << " composante: { ";
        for (unsigned int j = 0; j < resultat.size(); j++)
        {
            std::cout << resultat[i][j];
            std::cout << " ";
        }
        std::cout << "}" << std::endl;
    }
}

