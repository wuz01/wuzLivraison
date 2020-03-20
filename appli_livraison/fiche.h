#ifndef FICHE_H
#define FICHE_H

#include"livraison.h"
#include"tarif.h"
#include<QTextStream>

class Fiche
{
public:
    Fiche();
    void imprime(const livraison& livr , const tarif& t , const QTextStream& ost);

private:
    livraison d_livraison_fiche;
    int n_tarif_fiche;
};

#endif // FICHE_H
