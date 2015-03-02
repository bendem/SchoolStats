/****************************************************************************
** Form interface generated from reading ui file 'faffichage.ui'
**
** Created: dim. déc. 4 20:50:19 2011
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FAFFICHAGE_H
#define FAFFICHAGE_H

#include <qvariant.h>
#include <qdialog.h>

#include "data/Data2D.hpp"
#include "data/DataSource2D.hpp"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QFrame;

class FAffichage : public QDialog
{
Q_OBJECT

public:
    FAffichage(DataSource2D*, QWidget* parent = 0, const char* name = 0, bool modal = false, WFlags fl = 0 );
    ~FAffichage();

    QPushButton* ButtonTerminer;
    QPushButton* ButtonTracer;
    QPushButton* ButtonSelectionner;
    QPushButton* ButtonRafffraichir;
    QFrame* frame3;

public slots:
    virtual void Raffaichir();
    virtual void TracerLigne();
    virtual void Terminer();
    virtual void Selectionner();

protected:
    virtual void mouseMoveEvent( QMouseEvent *e );
    virtual void mouseReleaseEvent( QMouseEvent * );
    virtual void mousePressEvent( QMouseEvent * );


protected slots:
    virtual void languageChange();

private:
    QPoint    PointDepart;
    QPoint    PointArrivee;
    bool    Marque;
    Data2D D1;
    Data2D D2;
    float   E1 ;
    float   E2 ;
    float   Max1,Max2,Min1,Min2;
    DataSource2D* DD;


};

#include "ui/faffichage.hpp"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>

const char *FAffichage::className() const {
    return "FAffichage";
}

QMetaObject *FAffichage::metaObj = 0;
static QMetaObjectCleanUp cleanUp_FAffichage( "FAffichage", &FAffichage::staticMetaObject );

QString FAffichage::tr( const char *s, const char *c ) {
    if ( qApp )
        return qApp->translate( "FAffichage", s, c, QApplication::DefaultCodec );
    else
        return QString::fromLatin1( s );
}
QString FAffichage::trUtf8( const char *s, const char *c ) {
    if ( qApp )
        return qApp->translate( "FAffichage", s, c, QApplication::UnicodeUTF8 );
    else
        return QString::fromUtf8( s );
}

QMetaObject* FAffichage::staticMetaObject() {
    if ( metaObj )
        return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"Raffaichir", 0, 0 };
    static const QUMethod slot_1 = {"TracerLigne", 0, 0 };
    static const QUMethod slot_2 = {"Terminer", 0, 0 };
    static const QUMethod slot_3 = {"Selectionner", 0, 0 };
    static const QUMethod slot_4 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
        { "Raffaichir()", &slot_0, QMetaData::Public },
        { "TracerLigne()", &slot_1, QMetaData::Public },
        { "Terminer()", &slot_2, QMetaData::Public },
        { "Selectionner()", &slot_3, QMetaData::Public },
        { "languageChange()", &slot_4, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
        "FAffichage", parentObject,
        slot_tbl, 5,
        0, 0,
#ifndef QT_NO_PROPERTIES
        0, 0,
        0, 0,
#endif // QT_NO_PROPERTIES
        0, 0 );
    cleanUp_FAffichage.setMetaObject( metaObj );
    return metaObj;
}

void* FAffichage::qt_cast( const char* clname ) {
    if ( !qstrcmp( clname, "FAffichage" ) )
        return this;
    return QDialog::qt_cast( clname );
}

bool FAffichage::qt_invoke( int _id, QUObject* _o ) {
    switch ( _id - staticMetaObject()->slotOffset() ) {
        case 0: Raffaichir(); break;
        case 1: TracerLigne(); break;
        case 2: Terminer(); break;
        case 3: Selectionner(); break;
        case 4: languageChange(); break;
        default:
            return QDialog::qt_invoke( _id, _o );
    }
    return true;
}

bool FAffichage::qt_emit( int _id, QUObject* _o ) {
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool FAffichage::qt_property( int id, int f, QVariant* v) {
    return QDialog::qt_property( id, f, v);
}

bool FAffichage::qt_static_property( QObject* , int , int , QVariant* ) {
    return false;
}
#endif // QT_NO_PROPERTIES


#endif // FAFFICHAGE_H
