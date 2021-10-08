/* --------------------------------------------------------------------------------- *\
    CALCOLO NUMERICO E PROGRAMMAZIONE C++ (AA 2021/22)                  Alice Plebe

    Template -- esempio con alberi binari
\* --------------------------------------------------------------------------------- */

#include <iostream>
using namespace std;


// crea una classe template per rappresentare alberi binari (ovvero ogni nodo ha al piu` due figli)
template <class Type>
class Tree {
    public:
        // struttura per rappresentare un generico nodo
        struct node {
            Type    value;      // valore contenuto nel nodo
            node    *left;      // puntatore al nodo-figlio sinistro
            node    *right;     // puntatore al nodo-figlio destro
        };

        node    *root;          // puntatore alla radice dell'albero

        // il costruttore inizializza la radice
        Tree( Type v ) {
            root            = new node;
            root->value     = v;
            root->right     = NULL;     // inizializza un puntatore nullo
            root->left      = NULL;     // inizializza un puntatore nullo
        }

        // aggiunge un nodo-figlio destro al nodo 'p'
        void add_right( node *p, Type v ) {
            p->right        = new node;
            p->right->value = v;
            p->right->right = NULL;
            p->right->left  = NULL;
        }

        // aggiunge un nodo-figlio sinistro al nodo 'p'
        void add_left( node *p, Type v ) {
            p->left         = new node;
            p->left->value  = v;
            p->left->right  = NULL;
            p->left->left   = NULL;
        }

        // stampa tutti i valori contenuti nell'albero, visitando i nodi in modo "inorder"
        void print_tree( node *p ) {
            if ( p == NULL ) {          // termina la ricorsione quando raggiunge una foglia
                return;
            }
            print_tree( p->left );      // visita il sotto-albero sinistro
            cout << p->value << " ";    // stampa il valore del nodo corrente
            print_tree( p->right );     // visita il sotto-albero destro
        }
};

int main() {
    Tree<int>   int_tree( 4 );          // albero di interi
    int_tree.add_left( int_tree.root, 2 );
    int_tree.add_right( int_tree.root, 6 );
    int_tree.add_left( int_tree.root->left, 1 );
    int_tree.add_right( int_tree.root->left, 3 );
    int_tree.add_left( int_tree.root->right, 5 );
    int_tree.add_right( int_tree.root->right, 7 );
    int_tree.print_tree( int_tree.root );
    cout << endl;
    
    Tree<char>   char_tree( 'd' );      // albero di char
    char_tree.add_left( char_tree.root, 'b' );
    char_tree.add_right( char_tree.root, 'f' );
    char_tree.add_left( char_tree.root->left, 'a' );
    char_tree.add_right( char_tree.root->left, 'c' );
    char_tree.add_left( char_tree.root->right, 'e' );
    char_tree.add_right( char_tree.root->right, 'g' );
    char_tree.print_tree( char_tree.root );
    cout << endl;

    return 0;
}