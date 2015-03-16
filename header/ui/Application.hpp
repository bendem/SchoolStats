#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <qapplication.h>
#include <qdialog.h>
#include <qframe.h>
#include <qlayout.h>
#include <qmetaobject.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qvariant.h>
#include <qwhatsthis.h>
#include <private/qucomextra_p.h>

#include "data/Data2D.hpp"
#include "data/DataSource2D.hpp"
#include "statistics/StatisticalSerie2D.hpp"

class QFrame;
class QGridLayout;
class QHBoxLayout;
class QPushButton;
class QSpacerItem;
class QVBoxLayout;

class Application : public QDialog {
Q_OBJECT

public:
    Application(const StatisticalSerie2D*);
    ~Application();

    QPushButton* doneButton;
    QPushButton* drawButton;
    QPushButton* selectButton;
    QPushButton* refreshButton;
    QFrame* thePaintingFrame;

public slots:
    virtual void refresh();
    virtual void drawLine();
    virtual void done();
    virtual void select();

protected:
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mousePressEvent(QMouseEvent*);


protected slots:
    virtual void languageChange();

private:
    static const unsigned int WIDTH;
    static const unsigned int HEIGHT;

    QPoint startingPoint;
    QPoint endingPoint;
    bool isMouseButtonDown;
    float e1;
    float e2;
    float maxX, maxY, minX, minY;
    const StatisticalSerie2D* serie2D;
    unsigned transformX(float) const;
    unsigned transformY(float) const;

};

#endif
