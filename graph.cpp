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
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
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

    /// bouton supp sommet
    m_top_box.add_child( m_supp_sommet );
    m_supp_sommet.set_dim(8, 8);
    m_supp_sommet.set_pos(17,88);
    m_supp_sommet.set_bg_color(ROUGE);
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

    ///bouton supprimer
//    if (m_interface->m_supp_sommet.clicked())
//    {
//        std::cout<< "bg sa mere"<<std::endl;
//    }
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
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
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

    m_boite5.add_child( m_bouton5 );
    m_bouton5.set_frame(3,3,50,40);
    m_bouton5.set_bg_color(FUCHSIA);

    m_bouton5.add_child(m_bouton_label5);
    m_bouton_label5.set_message("OPEN 3");


    /// SIXIEME BOUTTON CASE:
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

    /// HUITIEME BOUTTON CASE:
    /// On ajoute en haut à droite la boite à boutons
    m_top_box.add_child( m_boite8 );
    m_boite8.set_dim(140,30);
    m_boite8.set_pos(850,130);
    m_boite8.set_bg_color(FUCHSIACLAIR);

    m_boite8.add_child( m_bouton8);
    m_bouton8.set_frame(3,3,140,30);
    m_bouton8.set_bg_color(FUCHSIA);

    m_bouton8.add_child(m_bouton_label8);
    m_bouton_label8.set_message("SUPPRIMER UN SOMMET");


    /// NEUVIEME BOUTON CASE:  HORLOGE PLAY ET VISU DE L'HORLOGE

    m_tool_box.add_child( m_case_horloge );
    m_case_horloge.set_dim(50,40);
    m_case_horloge.set_pos(12,600);
    m_case_horloge.set_bg_color(VERTFLUO);


    m_case_horloge.add_child(m_bouton_label_horloge);
    m_bouton_label_horloge.set_message("0");

    ///BOUTON LAUNCH
    m_tool_box.add_child(m_boite_launch);
    m_boite_launch.set_pos(22,550);
    m_boite_launch.set_dim(30,30);

    ///  BOUTTON FORT CONNEXITE :
    m_top_box.add_child( m_boite_connex );
    m_boite_connex.set_dim(50,40);
    m_boite_connex.set_pos(12,300);
    m_boite_connex.set_bg_color(ROSECLAIR);

    /// Puis un 1er bouton avec un texte
    m_boite_connex.add_child( m_bouton_connex );
    m_bouton_connex.set_frame(3,3,50,40);
    m_bouton_connex.set_bg_color(ROSESOMBRE);

    m_bouton_connex.add_child(m_bouton_label_connex);
    m_bouton_label_connex.set_message("CONNEXITE");





}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.


Graph::~Graph()
{

}
/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update(std::string& choixfichiersom,std::string& choixfichierare)
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

    //bouton save
    if (m_interface->m_bouton.clicked())
    {
        ecriture_vertex(choixfichiersom);
        ecriture_edge(choixfichierare);
    }
    //ajouter sommer
    if ( m_interface->m_bouton3.clicked() )
    {
        std::cout << "NEW !" << std::endl;
        ajouter_sommet();
    }
    //ajouter arete
    if ( m_interface->m_bouton6.clicked() )
    {
        std::cout << "NEW !" << std::endl;
        ajouter_arete();
    }
    //sup arete
    if ( m_interface->m_bouton7.clicked() )
    {
        int choix;
        for (const auto& elem : m_edges)
        {
            std::cout<< elem.first <<"  "<<elem.second.m_from<<"->"<<elem.second.m_to <<std::endl;
        }
        std::cout << "quelle arete voulez vous supprimer ? " << std::endl;
        std::cin >>choix;
        remove_edge(choix);

    }
    //ouvrir graph 1
    if(m_interface->m_bouton2.clicked())
    {
        m_edges.clear();
        m_vertices.clear();
        choixfichiersom="sommetschaine_1.txt";
        choixfichierare="areteschaine_1.txt";
        lecture_vertex(choixfichiersom);
        lecture_edge(choixfichierare);
    }
    //ouvrir graph2
    if(m_interface->m_bouton4.clicked())
    {
        m_edges.clear();
        m_vertices.clear();
        choixfichiersom="sommetschaine_2.txt";
        choixfichierare="areteschaine_2.txt";
        lecture_vertex(choixfichiersom);
        lecture_edge(choixfichierare);
    }
    //ouvrir graph 3
    if(m_interface->m_bouton5.clicked())
    {
        m_edges.clear();
        m_vertices.clear();
        choixfichiersom="sommetschaine_3.txt";
        choixfichierare="areteschaine_3.txt";
        lecture_vertex(choixfichiersom);
        lecture_edge(choixfichierare);
    }
    //suprimer sommet
    if(m_interface->m_bouton8.clicked())
    {
        int sommet;
        std::cout<< "Indice du sommet a sup: ";
        std::cin>> sommet;
        remove_vertex(sommet);
    }


    ///HORLOGE

    if (m_interface->m_boite_launch.get_value()==true)
    {
        std::string Result;
        std::ostringstream convert;
        dynamisme();
        convert << m_horloge   ;
        Result = convert.str();
        m_interface->m_bouton_label_horloge.set_message(Result);
    }



    /// FORTE CONNEXITE
    if (m_interface->m_bouton_connex.clicked())
    {
        afficher_les_comp_fort_connexe();
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
        float r;
        double value;
        while(fichier >>indice)
        {
            fichier >>value>>posx>>posy>>nom_image>>r;
            add_interfaced_vertex(indice,value, posx, posy, nom_image);
            m_vertices.find(indice)->second.m_r=r;
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
            fichier<< elem.first<<" "<<elem.second.m_value<<" "<<elem.second.m_interface->m_top_box.get_posx()<<" "<<elem.second.m_interface->m_top_box.get_posy()<<" "<<elem.second.m_interface->m_img.get_pic_name()<<" " <<elem.second.m_r <<std::endl;
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


    add_interfaced_edge(arete_max+1,proie, predateur,50);
}

void Graph::afficher_les_sommets()
{
    for (const auto& elem : m_vertices)
    {
        std::cout<< elem.first <<"  "<<elem.second.m_interface->m_img.get_pic_name()<< std::endl;
    }
}


void Graph::remove_edge(int eidx)
{
/// référence vers le Edge à enlever
    Edge &remed=m_edges.at(eidx);

    // std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

/// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    //  std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    // std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    // std::cout << m_edges.size() << std::endl;

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
    // std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    // std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    // std::cout << m_edges.size() << std::endl;

}

/**/

void Graph::remove_vertex(int idx)
{
    int maxi;
    for( int i=0; i<=m_vertices.find(idx)->second.m_in.size(); i++)
    {
        maxi=i;
    }
    for (int i=0; i<maxi; i++)
    {
        remove_edge( m_vertices.find(idx)->second.m_in[0] );
    }
    for(int i=0; i<=m_vertices.find(idx)->second.m_out.size(); i++)
    {
        maxi=i;
    }
    for(int i=0; i<maxi; i++)
    {
        remove_edge( m_vertices.find(idx)->second.m_out[0] );
    }
    Vertex &remed=m_vertices.at(idx);
    if (m_interface && remed.m_interface)
    {
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_box );
    }

    m_vertices.erase( idx );

}

void Graph::dynamisme()
{
    m_horloge=m_horloge+1;
//   std::cout<<m_horloge<<std::endl;

    ///equa
    for ( auto& elem : m_vertices)
    {
        int test=0;
        elem.second.m_k=0;
        for(int i=0; i<elem.second.m_in.size(); i++)
        {
            test=1;
            elem.second.m_k+=(m_edges.find(elem.second.m_in[i])->second.m_weight)/100*m_vertices.find(m_edges.find(elem.second.m_in[i])->second.m_from)->second.m_value;
        }
        if (test==0)
            elem.second.m_k=70;

        elem.second.m_value=elem.second.m_value+elem.second.m_r*elem.second.m_value*(1-elem.second.m_value/elem.second.m_k);
        if (elem.second.m_value<0)
            elem.second.m_value=0.1;
        if (elem.second.m_value>99)
            elem.second.m_value=99;
    }


}



std::vector<bool> Graph::uneComposanteFortementConnexe (unsigned int ordre, int s)
{
    //Variables locales
    std::vector<bool> c1(ordre, 0); // composantes connexes directes partant de s
    std::vector<bool> c2(ordre, 0);  // composantes connexes indirectes arrivant vers s
    std::vector<bool> c(ordre, 0) ; // composante fortement connexe = c1  c2 à retourner
    std::vector<bool> marques(ordre, 0) ; // tableau dynamique indiquant si les sommets sont marqués ou non
    std::vector<bool> marques2(ordre, 0) ;
    std::vector<int> out; // TABLEAU DES ARETES SORTANTES DU SOMMET
    std::vector<int> in; // TABLEAU DES ARETES ENTRANTES DU SOMMET
    int from; // INDICE DU SOMMET DE DEPART
    int to; // INDICE DU SOMMET D'ARRIVEE
    unsigned int carambar = 0;
    int carambar2 = 0;
    unsigned int x, y; // numéros de sommets intermédiaires des composantes connexes
    int ajout; // booléen indiquant si une nouvelle composante connexe est ajoutée

    // Rendre le sommet s connexe
    c1[s] = 1;
    c2[s] = 1;
    ajout = 1;

    // Recherche des composantes connexes partant de s à ajouter dans c1 :
    while (ajout == 1)
    {
        ajout = 0;

        for (x=0 ; x<ordre ; x++)
        {
            out = m_vertices[x].m_out;
            if (marques[x]==0 && c1[x]==1)
            {
                marques[x] = 1 ;
                for (y=0 ; y< out.size() ; y++)
                {
                    to = m_edges[out[y]].m_to;
                    if (marques[to]==0)
                    {
                        c1[to] = 1 ;
                        ajout = 1 ; // nouvelle composante connexe ajoutée
                    }
                }
            }
        }
    }
    /*   /// AFFICHER C1
       for(unsigned int i = 0; i < c1.size(); i++)
           std::cout << std::endl << "+: " << c1[i] << " ";    */

    /// on remet ajout à 1
    ajout = 1;

    // Recherche des composantes connexes arrivant à s à ajouter dans c2 :
    while (ajout)
    {
        ajout = 0;
        for (x=0 ; x<ordre ; x++)
        {
            in = m_vertices[x].m_in;
            if (marques2[x]==0 && c2[x]==1)
            {
                marques2[x] = 1 ;
                for (y=0 ; y< in.size() ; y++)
                {
                    from = m_edges[in[y]].m_from;
                    if (marques2[from]==0)
                    {
                        c2[from] = 1 ;
                        ajout = 1 ; // nouvelle composante connexe ajoutée
                    }
                }
            }
        }
    }
    /*   /// AFFICHER C2
       for(unsigned int i = 0; i < c2.size(); i++)
           std::cout << std::endl << "-: " << c2[i] << " ";    */


    /// RASSEMBLER LES DEUX PARCOURS DU GRAPHE
    for (x=0 ; x<ordre ; x++)
        c[x] = c1[x] & c2[x] ;

    /*  /// AFFICHER C
      for(unsigned int i = 0; i < c.size(); i++)
          std::cout << std::endl << "+ & -: " << c[i] << " "; */

    for(unsigned int i = 0; i < c.size(); i++)
    {
        if(c[i] == 0)
            carambar++;
        else
            carambar2 = i;
    }
    if (carambar == c.size()-1 && carambar2 == s)
        c[s] = 0;
    /// ATTENTION PB: IL FAUT RAJOUTER UNE CONDITION POUR SAVOIR SI CE SOMMET EST RELIE A LUI-MEME

    return c ;
}

std::vector<std::vector<bool>> Graph::toutesLesComposantesFortementConnexes()
{
    // Variables locales
    std::vector<std::vector<bool>> tabc ; // tableau dynamique des composantes fortement connexes à retourner
    std::vector<bool> marq ; // tableau dynamique indiquant si les sommets sont marqués ou non
    std::vector<bool> non_nul;
    int blablacar; // nombre de sommets
    int monsieur = 0;

    blablacar = m_vertices.size();

    /// Initialiser les valeurs de ces tableaux à 0
    for (int l = 0; l < blablacar; l++)
        marq.push_back(0);

    // Pour tous les sommets x non marqués
    // Rechercher la composante fortement connexe de x
    // Marquer chaque sommet x et marquer les sommets y connectés à x et non marqués
    for (int x=0 ; x<blablacar ; x++)
    {
        if (!marq[x])
        {
            non_nul = uneComposanteFortementConnexe(blablacar, x);
            for(int h = 0; h < blablacar; h++)
            {
                if(non_nul[h] == 0)
                    monsieur ++;
            }
            if (monsieur != blablacar)
                tabc.push_back(uneComposanteFortementConnexe(blablacar, x));
            monsieur = 0;
            marq[x] = 1;
            //     std::cout << std::endl << "A CE TOUR, X VAUT: " << x << std::endl;
            for (int y=0 ; y<blablacar ; y++)
            {
                if (non_nul[y]==1 && marq[y]==0)
                {
                    marq[y] = 1;
                }
            }
        }
    }
    return tabc ;
}

void Graph::remplir_mat_dadj()
{
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
        m_adj[to][from] = 1;
    }

    m_adj[0][0] = 0;

    /*   /// AFFICHAGE DE LA MATRICE
       std::cout << "Matrice d'adjacence:" << std::endl << "x ";
       for (unsigned int w = 0; w < blablacar; w++)
           std::cout << w << " ";

       std::cout << std::endl;
       for (unsigned int x = 0; x < blablacar; x++)
       {
           std::cout << x << " ";
              for (unsigned int y = 0; y < blablacar; y++)
               std::cout << m_adj[x][y] << " ";
           std::cout << std::endl;
       }*/
}

void Graph::afficher_les_comp_fort_connexe()
{
    std::vector<std::vector<bool>> resultat;
    remplir_mat_dadj();

    resultat = toutesLesComposantesFortementConnexes();

    if(resultat.size() == 1)
        std::cout << "Le graphe est fortement connexe" << std::endl;
    else if(resultat.size() == 0)
        std::cout << "Le graphe n'est pas fortement connexe et il n'a aucune composante fortement connexe" << std::endl;
    else
        std::cout << "Le graphe n'est pas fortement connexe" << std::endl;

    for (unsigned int i = 0; i < resultat.size(); i++)
    {
        std::cout << i + 1 << " composante: { ";
        for (unsigned int j = 0; j < m_vertices.size(); j++)
        {
            std::cout << resultat[i][j];
            std::cout << " ";
        }
        std::cout << "}" << std::endl;
    }
}



