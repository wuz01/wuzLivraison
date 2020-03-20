#ifndef LIVRAISONWINDOW_H
#define LIVRAISONWINDOW_H

#include <QWidget>
#include<QPushButton>
#include<QCheckBox>
#include<QLabel>
#include<QButtonGroup>
#include"tarif.h"
#include"livraison.h"

using std::vector;

class LivraisonWindow : public QWidget
{
    Q_OBJECT

public:
    LivraisonWindow(const vector<tarif*>& tab_tarif , QWidget *parent = nullptr);
    //~LivraisonWindow();
    void vue_cree();
    void vue_afficheDestination(const int& i);
    void vue_affichePrix(double prix);
    double prixLivraisonCourante() const;
    void onDestination(const int& id);
    void vue_afficheTypeLivraison(const livraison& livr);
    void onExpress(int etat);
    void onFragile(int etat);
    void onQuitter();
    void onReinitialiser();
    void onAcheter();

private :
    vector<tarif*> d_tarif ;
    livraison d_livraison ;
    int d_numeroTarif ;

    QPushButton *buttonReinitialiser, *buttonAcheter, *buttonQuitter;

    QCheckBox *d_fragile, *d_express;

    QLabel *d_labelPrix;

    QButtonGroup *d_radioDestination;
};
#endif // LIVRAISONWINDOW_H
