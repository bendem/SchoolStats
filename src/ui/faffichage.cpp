/****************************************************************************
** Form implementation generated from reading ui file 'faffichage.ui'
**
** Created: dim. déc. 4 20:55:04 2011
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "ui/faffichage.hpp"

#include <qvariant.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

extern float a,b;
#include <pthread.h>
extern pthread_cond_t Cond;
extern pthread_mutex_t Mutex;
extern int again;
extern int errno;

/*
 *  Constructs a FAffichage as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
FAffichage::FAffichage(DataSource2D* D, QWidget* parent, const char* name, bool modal, WFlags fl)
        : QDialog(parent, name, modal, fl),
          D1(static_cast<Data2D&>(*D->getData().get(0))), // TODO I have no idea
          D2(static_cast<Data2D&>(*D->getData().get(0))) {
    if (!name) {
        //setName("FAffichage");
    }

    ButtonTerminer = new QPushButton("ButtonTerminer", this);
    ButtonTerminer->setGeometry(QRect(360, 280, 100, 29));
    ButtonTerminer->setAutoDefault(FALSE);

    ButtonTracer = new QPushButton("ButtonTracer", this);
    ButtonTracer->setGeometry(QRect(240, 280, 100, 29));
    ButtonTracer->setAutoDefault(FALSE);

    ButtonSelectionner = new QPushButton("ButtonSelectionner", this);
    ButtonSelectionner->setGeometry(QRect(130, 280, 100, 29));
    ButtonSelectionner->setAutoDefault(FALSE);

    ButtonRafffraichir = new QPushButton("ButtonRafffraichir", this);
    ButtonRafffraichir->setGeometry(QRect(10, 280, 100, 29));
    ButtonRafffraichir->setAutoDefault(FALSE);

    frame3 = new QFrame(this);
    frame3->setGeometry(QRect(20, 20, 440, 240));
    frame3->setFrameShape(QFrame::StyledPanel);
    frame3->setFrameShadow(QFrame::Raised);
    languageChange();
    resize(QSize(475, 327).expandedTo(minimumSizeHint()));
    //clearWState(WState_Polished);

    // signals and slots connections
    connect(ButtonRafffraichir, SIGNAL(clicked()), this, SLOT(Raffaichir()));
    connect(ButtonTerminer, SIGNAL(clicked()), this, SLOT(Terminer()));
    connect(ButtonTracer, SIGNAL(clicked()), this, SLOT(TracerLigne()));
    connect(ButtonSelectionner, SIGNAL(clicked()), this, SLOT(Selectionner()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
FAffichage::~FAffichage() {
    // no need to delete child widgets, Qt does it all for us
    cout << "dans destructeur FAffiche" << endl;
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void FAffichage::languageChange() {
    //setCaption(tr("Affichage des donnees"));
    ButtonTerminer->setText(tr("Terminer"));
    ButtonTracer->setText(tr("Tracer ligne"));
    ButtonSelectionner->setText(tr("Selectionner"));
    ButtonRafffraichir->setText(tr("Raffraichir"));
}

void FAffichage::Raffaichir() {
    qWarning("FAffichage::Raffaichir()");
/* dessine les points de la liste
...
*/
}

void FAffichage::TracerLigne() {
    qWarning("FAffichage::TracerLigne()");
/*
QPainter paint(frame3);
paint.drawLine(,,,);
*/

}

void FAffichage::Terminer() {
    qWarning("FAffichage::Terminer(): Not implemented yet");
/*
place une variable continue a 0 et signale au main
...
*/
    close();
}

void FAffichage::Selectionner() {
    qWarning("FAffichage::Selectionner() ");
/*
QPainter paint(frame3);
paint.setPen(Qt::black);
paint.drawRect(PointDepart.x(),PointDepart.y(),
        PointArrivee.x()-PointDepart.x(),PointArrivee.y()-PointDepart.y());
...
classes les 2 point selectionnes
...
retire les points de la zone selectionnee de la liste

place une variable continue a 1 et signale au main
...
*/
}

void FAffichage::mouseMoveEvent(QMouseEvent* e) {
}

void FAffichage::mouseReleaseEvent(QMouseEvent* e) {
    QPainter paint(frame3);
    if (Marque) {
        PointArrivee = e->pos();
        PointArrivee.setX(PointArrivee.x()- 20);
        PointArrivee.setY(PointArrivee.y()- 20);
        paint.drawText(PointArrivee.x() -4, PointArrivee.y() + 4,"x");
        Marque = false;
    }
    cout << "Depart : " << PointDepart.x() << " - " << PointDepart.y() << endl;
    cout << "Arrivee : " << PointArrivee.x() << " - " << PointArrivee.y() << endl;
}

void FAffichage::mousePressEvent(QMouseEvent* e) {
    QPainter paint(frame3);
    if (!Marque) {
        PointDepart = e->pos();
        PointDepart.setX(PointDepart.x() - 20);
        PointDepart.setY(PointDepart.y() - 20);
        paint.drawText(PointDepart.x() - 4, PointDepart.y() + 4, "x");
        Marque = true;
    }
}
