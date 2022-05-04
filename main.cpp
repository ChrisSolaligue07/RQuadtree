/*
 * - Cada nodo tiene 4 punteros, cada puntero (B, D, C, E) está referido a los cuadrantes maximos que puede
 *   tener una raíz
 * - Se hizo las pruebas de "Build" con una profundidad i, donde: 1 <= i <= 4
 * - La función add, es recursiva
 * - La función build crea el árbol, esta función también es recursiva
 * - La explicación de la estructura formada se encuentra en la carpeta "IMG"
 * - La prueba de su funcionamiento en cuanto a la posición de los puntos también se encuentra en "IMG"
 */
#include <iostream>

using std::cout, std::endl;

struct RQTree_Node{
    RQTree_Node *B;
    RQTree_Node *C;
    RQTree_Node *D;
    RQTree_Node *E;
    float LIM_SUP[2]{};
    float LIM_INF[2]{};
    int frecuencia;
    int profundidad;
    RQTree_Node(const float LIM_SUP[2], const float LIM_INF[2], int prof){
        B = nullptr;
        C = nullptr;
        D = nullptr;
        E = nullptr;

        this->LIM_SUP[0] = LIM_SUP[0];
        this->LIM_SUP[1] = LIM_SUP[1];

        this->LIM_INF[0] = LIM_INF[0];
        this->LIM_INF[1] = LIM_INF[1];

        profundidad = prof;
        frecuencia = 0;
    }
    void print() {
        cout << "Nodo x ------------------------------------------------------" << endl;
        cout << "Limite Superior : (" << LIM_SUP[0] << " ," << LIM_SUP[1] << ")" << endl;
        cout << "Limite Inferior : (" << LIM_INF[0] << " ," << LIM_INF[1] << ")" << endl;
        cout << "-------------------------------------------------------------" << endl << endl;
    }
};
struct RQTree {
    RQTree_Node *root;
    int profundidad;

    RQTree(float LIM_SUP[2], float LIM_INF[2], int prof) {
        root = new RQTree_Node(LIM_SUP, LIM_INF, prof);
        profundidad = prof;
        Build(root, LIM_SUP, LIM_INF, prof);
    }
    void Build(RQTree_Node *tmp, float L[2], float F[2], int prof){
        if(prof <= 1){    // Condición de parada
            return;
        } else {
            if(tmp->B == nullptr){
                float sup[2] = { L[0], L[1] };
                float inf[2] = { F[0] - (F[0] - L[0]) / 2, L[1] - (L[1] - F[1]) / 2 };
                tmp->B = new RQTree_Node(sup, inf, prof - 1);
                Build(tmp->B, sup, inf, prof - 1);
            }
            if(tmp->C == nullptr){
                float sup[2] = { F[0] - (F[0] - L[0]) / 2, L[1] };
                float inf[2] = { F[0], L[1] - (L[1] - F[1]) / 2 };
                tmp->C = new RQTree_Node(sup, inf, prof - 1);
                Build(tmp->C, sup, inf, prof - 1);
            }
            if(tmp->D == nullptr){
                float sup[2] = { L[0], L[1] - (L[1] - F[1]) / 2 };
                float inf[2] = { F[0] - (F[0] - L[0]) / 2, F[1] };
                tmp->D = new RQTree_Node(sup, inf, prof - 1);
                Build(tmp->D, sup, inf, prof - 1);
            }
            if(tmp->E == nullptr){
                float sup[2] = { F[0] - (F[0] - L[0]) / 2, L[1] - (L[1] - F[1]) / 2 };
                float inf[2] = { F[0], F[1] };
                tmp->E = new RQTree_Node(sup, inf, prof - 1);
                Build(tmp->E, sup, inf, prof - 1);
            }
        }
    }
    static bool limit(float x, float y, RQTree_Node *cuadrante) {
        if ((x <= cuadrante->LIM_INF[0] && x >= cuadrante->LIM_SUP[0]) && (y <= cuadrante->LIM_SUP[1] && y >= cuadrante->LIM_INF[1])) {
            return true;
        } else {
            return false;
        }
    }
    void add(float x, float y, RQTree_Node *tmp){
        if(!limit(x, y, tmp) || tmp == nullptr){    // Condición de parada
            return;
        } else {
            tmp->frecuencia++;
            if(tmp->B != nullptr && limit(x, y, tmp->B)){
                add(x, y , tmp->B);
            }
            if(tmp->C != nullptr && limit(x, y, tmp->C)){
                add(x, y , tmp->C);
            }
            if(tmp->D != nullptr && limit(x, y, tmp->D)){
                add(x, y , tmp->D);
            }
            if(tmp->E != nullptr && limit(x, y, tmp->E)){
                add(x, y , tmp->E);
            }
            return;
        }
    }
    void add(float x, float y){
        if(!limit(x, y, root)){
            cout << "El punto (" << x << ", " << y << ") esta fuera del cuadrante" << endl;
            return;
        } else {
            add(x, y, root);
        }
    }
};

int main() {
    int dep = 3;
    float LIM_SUP[2] = {4, 15};
    float LIM_INF[2] = {10, 2};

    RQTree RQ(LIM_SUP, LIM_INF, dep);
    /*
    Print del limite superior e inferior de cada nodo formado
    RQ.root->B->B->print();
    RQ.root->B->C->print();
    RQ.root->B->D->print();
    RQ.root->B->E->print();
    cout << "----------------------------------" << endl;
    RQ.root->C->B->print();
    RQ.root->C->C->print();
    RQ.root->C->D->print();
    RQ.root->C->E->print();
    cout << "----------------------------------" << endl;
    RQ.root->D->B->print();
    RQ.root->D->C->print();
    RQ.root->D->D->print();
    RQ.root->D->E->print();
    cout << "----------------------------------" << endl;
    RQ.root->E->B->print();
    RQ.root->E->C->print();
    RQ.root->E->D->print();
    RQ.root->E->E->print();
    cout << "----------------------------------" << endl << endl;
    */
    RQ.add(4.5, 7.5);
    RQ.add(4.5, 14);
    RQ.add(5, 13.5);
    RQ.add(6.7, 13);
    RQ.add(4.2, 3);
    RQ.add(7.8, 7);
    RQ.add(9.5, 3.2);
    RQ.add(7.4, 4.7);
    RQ.add(7.8, 4);
    RQ.add(8.9, 13);
    RQ.add(7.9, 10);
    RQ.add(4.4, 10);
    RQ.add(2, 6);   // Fuera del LIM_SUP & LIM_INF
    RQ.add(11, 9);  // Fuera del LIM_SUP & LIM_INF
    cout << "----------------------------------" << endl;
    cout << "A :" << RQ.root->frecuencia << endl;
    cout << "----------------------------------" << endl;
    cout << "B :" << RQ.root->B->frecuencia << endl;
    cout << "BB :" << RQ.root->B->B->frecuencia << endl;
    cout << "BC :" << RQ.root->B->C->frecuencia << endl;
    cout << "BD :" << RQ.root->B->D->frecuencia << endl;
    cout << "BE :" << RQ.root->B->E->frecuencia << endl;
    cout << "----------------------------------" << endl;
    cout << "C :" << RQ.root->C->frecuencia << endl;
    cout << "CB :" << RQ.root->C->B->frecuencia << endl;
    cout << "CC :" << RQ.root->C->C->frecuencia << endl;
    cout << "CD :" << RQ.root->C->D->frecuencia << endl;
    cout << "CE :" << RQ.root->C->E->frecuencia << endl;
    cout << "----------------------------------" << endl;
    cout << "D " << RQ.root->D->frecuencia << endl;
    cout << "DB :" << RQ.root->D->B->frecuencia << endl;
    cout << "DC :" << RQ.root->D->C->frecuencia << endl;
    cout << "DD :" << RQ.root->D->D->frecuencia << endl;
    cout << "DE :" << RQ.root->D->E->frecuencia << endl;
    cout << "----------------------------------" << endl;
    cout << "E :" << RQ.root->E->frecuencia << endl;
    cout << "EB :" << RQ.root->E->B->frecuencia << endl;
    cout << "EC :" << RQ.root->E->C->frecuencia << endl;
    cout << "ED :" << RQ.root->E->D->frecuencia << endl;
    cout << "EE :" << RQ.root->E->E->frecuencia << endl;
    cout << "----------------------------------" << endl;

    return 0;
}
