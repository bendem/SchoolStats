#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <qapplication.h>
#include <qdialog.h>
#include <qmetaobject.h>
#include <qvariant.h>
#include <private/qucomextra_p.h>

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
    Application(DataSource2D*, QWidget* parent = 0, const char* name = 0, bool modal = false, WFlags flags = 0);
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
    Data2D d1;
    Data2D d2;
    float e1;
    float e2;
    float max1, max2, min1, min2;
    DataSource2D* dataSource;

};

#endif
