#include "livraisonwindow.h"
#include"tarif.h"

#include <QApplication>

using std::vector;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    vector<tarif*> main_tarif;
    main_tarif.push_back(new tarif{"France", 10, 20, 30, 40});
    main_tarif.push_back(new tarif{"Belgique", 15, 25, 35, 45});
    main_tarif.push_back(new tarif{"Suisse", 20, 30, 40, 50});
    main_tarif.push_back(new tarif{"USA", 25, 35, 45, 55});

    LivraisonWindow w{main_tarif};
    w.show();

    //delete [] tarif;
    return a.exec();
}
