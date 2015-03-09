#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <qapplication.h>
#include <qdialog.h>
#include <qmetaobject.h>
#include <qvariant.h>
#include <private/qucomextra_p.h>
#include <statistics/StatisticalSerie2D.hpp>

#include "data/Data2D.hpp"
#include "data/DataSource2D.hpp"

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
    QFrame* aRandomFrameWhichWeDontKnowWhatToDoWith;

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
    QPoint startingPoint;
    QPoint endingPoint;
    bool isMouseButtonDown;
    float e1;
    float e2;
    float max1, max2, min1, min2;
    const StatisticalSerie2D* serie2D;

};

#endif
