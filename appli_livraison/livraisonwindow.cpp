#include "livraisonwindow.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLabel>
#include<QFrame>
#include<QCheckBox>
#include<QRadioButton>
#include<QButtonGroup>
#include<QMessageBox>

LivraisonWindow::LivraisonWindow(const vector<tarif*>& tab_tarif, QWidget *parent)
    : QWidget{parent} , d_tarif{tab_tarif} , d_livraison{} , d_numeroTarif{0}
{
    vue_cree();
    vue_afficheDestination(d_numeroTarif);   // sélectionne par def un radio button
    vue_afficheTypeLivraison(d_livraison);
    vue_affichePrix(d_tarif[d_numeroTarif]->prixNormal());
    connect(d_radioDestination , static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            this , &LivraisonWindow::onDestination);
    connect(d_express, &QCheckBox::stateChanged , this , &LivraisonWindow::onExpress);
    connect(d_fragile, &QCheckBox::stateChanged , this , &LivraisonWindow::onFragile);
    connect(buttonQuitter, &QPushButton::clicked , this , &LivraisonWindow::onQuitter);
    connect(buttonReinitialiser, &QPushButton::clicked , this , &LivraisonWindow::onReinitialiser);
    connect(buttonAcheter, &QPushButton::clicked , this , &LivraisonWindow::onAcheter);

}

void LivraisonWindow::vue_cree()
{
    auto layoutPrincipal = new QHBoxLayout{this};

    //partie boutton
    auto layoutBoutton = new QVBoxLayout{this};
    buttonReinitialiser = new QPushButton{"Ré-initialiser"};
    layoutBoutton->addWidget(buttonReinitialiser,0,Qt::AlignVCenter);
    buttonAcheter = new QPushButton{"Acheter"};
    layoutBoutton->addWidget(buttonAcheter,0,Qt::AlignVCenter);
    buttonQuitter = new QPushButton{"Quitter"};
    layoutBoutton->addWidget(buttonQuitter,0,Qt::AlignVCenter);

    //partie frame
    auto frame = new QFrame;
    frame->setFrameStyle(QFrame::VLine|QFrame::Sunken);

    //partie destination
    auto layoutDestination = new QVBoxLayout{this};
    auto labelDestination = new QLabel{"Destination"};
    layoutDestination->addWidget(labelDestination,0,Qt::AlignTop|Qt::AlignVCenter);
    d_radioDestination = new QButtonGroup{layoutDestination}; //je creer le groupe radio
    for(unsigned int i=0 ; i<d_tarif.size() ; ++i)       //creer un radio et l'ajouter au groupe
    {
        auto buttonRadio = new QRadioButton{QString::fromStdString(d_tarif[i]->destination())};
        d_radioDestination->addButton(buttonRadio, i);
        layoutDestination->addWidget(buttonRadio,0,Qt::AlignLeft);
    }

    //partie type livraison
    auto layoutType = new QVBoxLayout{this};
    auto labelType = new QLabel{"Type"};
    layoutType->addWidget(labelType,0,Qt::AlignTop|Qt::AlignVCenter);
    d_express = new QCheckBox{"Express"};
    layoutType->addWidget(d_express,0,Qt::AlignVCenter);
    d_fragile = new QCheckBox{"Fragile"};
    layoutType->addWidget(d_fragile,0,Qt::AlignVCenter);

    //partie prix
    auto layoutPrix = new QVBoxLayout{this};
    auto labelPrix = new QLabel{"Prix"};
    layoutPrix->addWidget(labelPrix,0,Qt::AlignTop|Qt::AlignVCenter);
    d_labelPrix = new QLabel{""};       //affiche le tarif
    layoutPrix->addWidget(d_labelPrix,0,Qt::AlignVCenter);


    layoutPrincipal->addLayout(layoutBoutton,0);
    layoutPrincipal->addWidget(frame,0,Qt::AlignLeft);
    layoutPrincipal->addLayout(layoutDestination,0);
    layoutPrincipal->addLayout(layoutType,0);
    layoutPrincipal->addLayout(layoutPrix,0);

    layoutPrincipal->addSpacing(20);
    setLayout(layoutPrincipal);

}


void LivraisonWindow::vue_afficheDestination(const int& i)
{
    d_radioDestination->button(i)->setChecked(true);
    vue_affichePrix(prixLivraisonCourante());
}

void LivraisonWindow::vue_afficheTypeLivraison(const livraison& livr)
{
    d_fragile->setChecked(livr.estFragile());
    d_express->setChecked(livr.estExpress());
    vue_affichePrix(prixLivraisonCourante());
}


void LivraisonWindow::vue_affichePrix(double prix)
{
    d_labelPrix->setText(QString::number(prix,'f',2));
}

double LivraisonWindow::prixLivraisonCourante() const
{
     return d_tarif[d_numeroTarif]->prix(d_livraison);
}

void LivraisonWindow::onDestination(const int& id)
{
    d_numeroTarif = id;
    vue_affichePrix(d_tarif[d_numeroTarif]->prixNormal());

}

void LivraisonWindow::onExpress(int etat)
{
    d_livraison.rendExpress(etat == Qt::Checked);
    vue_affichePrix(prixLivraisonCourante());
}
void LivraisonWindow::onFragile(int etat)
{
    d_livraison.rendFragile(etat == Qt::Checked);
    vue_affichePrix(prixLivraisonCourante());
}

void LivraisonWindow::onQuitter()
{
    close();
}

void LivraisonWindow::onReinitialiser()
{
    d_numeroTarif = 0;
    d_livraison.reInitialise();

    vue_afficheDestination(d_numeroTarif);   // sélectionne par def un radio button
    vue_afficheTypeLivraison(d_livraison);
    vue_affichePrix(prixLivraisonCourante());

}

void LivraisonWindow::onAcheter()
{
    QMessageBox message{QMessageBox::Information, "Information", "Livraison achetée"};
    message.exec();
}


/*LivraisonWindow::~LivraisonWindow()
{
}*/

