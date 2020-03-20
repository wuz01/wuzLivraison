#include "fiche.h"
#include"livraison.h"
#include"tarif.h"
#include<QTextStream>

Fiche::Fiche(): n_tarif_fiche{0} , d_livraison_fiche{}
{}

void Fiche::imprime(const livraison& livr , const tarif& t , const QTextStream& ost)
{
    /* ost<<"Livraison"<<endl;
    ost<<"Pays de destination :"<<t.destination();
    Livraioson : livr.*/
}
