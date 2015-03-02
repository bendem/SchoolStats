#include <qpainter.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlayout.h>
#include <qwhatsthis.h>

#include "ui/Application.hpp"

extern pthread_cond_t Cond;
extern pthread_mutex_t Mutex;
extern int again;

/*
 *  Constructs a Application as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
Application::Application(DataSource2D* D, QWidget* parent, const char* name, bool modal, WFlags flags)
    : QDialog(parent, name, modal, flags),
      d1(static_cast<Data2D&>(*D->getData().get(0))), // TODO I have no idea
      d2(static_cast<Data2D&>(*D->getData().get(0))) {
    if(!name) {
        setName("Application");
    }

    doneButton = new QPushButton("doneButton", this);
    doneButton->setGeometry(QRect(360, 280, 100, 29));
    doneButton->setAutoDefault(FALSE);

    drawButton = new QPushButton("drawButton", this);
    drawButton->setGeometry(QRect(240, 280, 100, 29));
    drawButton->setAutoDefault(FALSE);

    selectButton = new QPushButton("selectButton", this);
    selectButton->setGeometry(QRect(130, 280, 100, 29));
    selectButton->setAutoDefault(FALSE);

    refreshButton = new QPushButton("refreshButton", this);
    refreshButton->setGeometry(QRect(10, 280, 100, 29));
    refreshButton->setAutoDefault(FALSE);

    aRandomFrameWhichWeDontKnowWhatToDoWith = new QFrame(this);
    aRandomFrameWhichWeDontKnowWhatToDoWith->setGeometry(QRect(20, 20, 440, 240));
    aRandomFrameWhichWeDontKnowWhatToDoWith->setFrameShape(QFrame::StyledPanel);
    aRandomFrameWhichWeDontKnowWhatToDoWith->setFrameShadow(QFrame::Raised);
    languageChange();
    resize(QSize(475, 327).expandedTo(minimumSizeHint()));
    clearWState(WState_Polished);

    // signals and slots connections
    connect(refreshButton, SIGNAL(clicked()), this, SLOT(refresh()));
    connect(doneButton, SIGNAL(clicked()), this, SLOT(done()));
    connect(drawButton, SIGNAL(clicked()), this, SLOT(drawLine()));
    connect(selectButton, SIGNAL(clicked()), this, SLOT(select()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
Application::~Application() {
    // no need to delete child widgets, Qt does it all for us
    cout << "dans destructeur FAffiche" << endl;
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Application::languageChange() {
    setCaption(tr("Data display"));
    doneButton->setText(tr("Done"));
    drawButton->setText(tr("Draw line"));
    selectButton->setText(tr("Select"));
    refreshButton->setText(tr("Refresh"));
}

void Application::refresh() {
    qWarning("Application::refresh()");
    /* dessine les points de la liste
    ...
    */
}

void Application::drawLine() {
    qWarning("Application::drawLine()");
    /*
    QPainter paint(aRandomFrameWhichWeDontKnowWhatToDoWith);
    paint.drawLine(,,,);
    */

}

void Application::done() {
    qWarning("Application::done(): Not implemented yet");
    /*
    place une variable continue a 0 et signale au main
    ...
    */
    close();
}

void Application::select() {
    qWarning("Application::select() ");
    /*
    QPainter paint(aRandomFrameWhichWeDontKnowWhatToDoWith);
    paint.setPen(Qt::black);
    paint.drawRect(startingPoint.x(),startingPoint.y(),
            endingPoint.x()-startingPoint.x(),endingPoint.y()-startingPoint.y());
    ...
    classes les 2 point selectionnes
    ...
    retire les points de la zone selectionnee de la liste

    place une variable continue a 1 et signale au main
    ...
    */
}

void Application::mouseMoveEvent(QMouseEvent* e) {
}

void Application::mouseReleaseEvent(QMouseEvent* e) {
    QPainter paint(aRandomFrameWhichWeDontKnowWhatToDoWith);
    if(isMouseButtonDown) {
        endingPoint = e->pos();
        endingPoint.setX(endingPoint.x() - 20);
        endingPoint.setY(endingPoint.y() - 20);
        paint.drawText(endingPoint.x() - 4, endingPoint.y() + 4, "x");
        isMouseButtonDown = false;
    }
    cout << "Start: " << startingPoint.x() << " - " << startingPoint.y() << endl;
    cout << "End: " << endingPoint.x() << " - " << endingPoint.y() << endl;
}

void Application::mousePressEvent(QMouseEvent* e) {
    QPainter paint(aRandomFrameWhichWeDontKnowWhatToDoWith);
    if(!isMouseButtonDown) {
        startingPoint = e->pos();
        startingPoint.setX(startingPoint.x() - 20);
        startingPoint.setY(startingPoint.y() - 20);
        paint.drawText(startingPoint.x() - 4, startingPoint.y() + 4, "x");
        isMouseButtonDown = true;
    }
}

/************************************
 * Do not touch below here, teacher
 * did stuff, you don't want to know
 * anything more.
 ************************************/
const char* Application::className() const {
    return "Application";
}

QMetaObject* Application::metaObj = 0;
static QMetaObjectCleanUp cleanUp_FAffichage("Application", &Application::staticMetaObject);

QString Application::tr(const char* s, const char* c) {
    if(qApp) {
        return qApp->translate("Application", s, c, QApplication::DefaultCodec);
    } else {
        return QString::fromLatin1(s);
    }
}

QString Application::trUtf8(const char* s, const char* c) {
    if(qApp) {
        return qApp->translate("Application", s, c, QApplication::UnicodeUTF8);
    } else {
        return QString::fromUtf8(s);
    }
}

QMetaObject* Application::staticMetaObject() {
    if(metaObj) {
        return metaObj;
    }
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"refresh", 0, 0};
    static const QUMethod slot_1 = {"drawLine", 0, 0};
    static const QUMethod slot_2 = {"done", 0, 0};
    static const QUMethod slot_3 = {"select", 0, 0};
    static const QUMethod slot_4 = {"languageChange", 0, 0};
    static const QMetaData slot_tbl[] = {
        {"refresh()", &slot_0, QMetaData::Public},
        {"drawLine()", &slot_1, QMetaData::Public},
        {"done()", &slot_2, QMetaData::Public},
        {"select()", &slot_3, QMetaData::Public},
        {"languageChange()", &slot_4, QMetaData::Protected}
    };
    metaObj = QMetaObject::new_metaobject(
        "Application", parentObject,
        slot_tbl, 5,
        0, 0,
#ifndef QT_NO_PROPERTIES
        0, 0,
        0, 0,
#endif // QT_NO_PROPERTIES
        0, 0);
    cleanUp_FAffichage.setMetaObject(metaObj);
    return metaObj;
}

void* Application::qt_cast(const char* clname) {
    if(!qstrcmp(clname, "Application")) {
        return this;
    }
    return QDialog::qt_cast(clname);
}

bool Application::qt_invoke(int _id, QUObject* _o) {
    switch(_id - staticMetaObject()->slotOffset()) {
        case 0:
            refresh();
            break;
        case 1:
            drawLine();
            break;
        case 2:
            done();
            break;
        case 3:
            select();
            break;
        case 4:
            languageChange();
            break;
        default:
            return QDialog::qt_invoke(_id, _o);
    }
    return true;
}

bool Application::qt_emit(int _id, QUObject* _o) {
    return QDialog::qt_emit(_id, _o);
}

#ifndef QT_NO_PROPERTIES

bool Application::qt_property(int id, int f, QVariant* v) {
    return QDialog::qt_property(id, f, v);
}

bool Application::qt_static_property(QObject*, int, int, QVariant*) {
    return false;
}

#endif // QT_NO_PROPERTIES
