#include "ui/Application.hpp"

const unsigned int Application::WIDTH = 440;
const unsigned int Application::HEIGHT = 240;

/*
 *  Constructs a Application as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
Application::Application(StatisticalSerie2D& serie2D, Mutex& mutex)
        : QDialog(NULL, NULL, false, 0), serie2D(serie2D), mutex(mutex) {
    setName("Application");

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

    thePaintingFrame = new QFrame(this);
    thePaintingFrame->setGeometry(QRect(20, 20, WIDTH, HEIGHT));
    thePaintingFrame->setFrameShape(QFrame::StyledPanel);
    thePaintingFrame->setFrameShadow(QFrame::Raised);
    languageChange();
    resize(QSize(475, 327).expandedTo(minimumSizeHint()));
    clearWState(WState_Polished);

    // signals and slots connections
    connect(refreshButton, SIGNAL(clicked()), this, SLOT(refresh()));
    connect(doneButton, SIGNAL(clicked()), this, SLOT(done()));
    connect(drawButton, SIGNAL(clicked()), this, SLOT(drawLine()));
    connect(selectButton, SIGNAL(clicked()), this, SLOT(select()));

    this->minX = serie2D.getData().getMinX();
    this->minY = serie2D.getData().getMinY();
    this->maxX = serie2D.getData().getMaxX();
    this->maxY = serie2D.getData().getMaxY();
}

/*
 *  Destroys the object and frees any allocated resources
 */
Application::~Application() {
    // no need to delete child widgets, Qt does it all for us
    Log::log("Application", "~Application");
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
    QPainter paint(thePaintingFrame);
    paint.eraseRect(1, 1, WIDTH - 2, HEIGHT - 2); // let 1 pixel alone because the border is inset

    Data2DIterator it(this->serie2D.getData().getData());

    while(!it.end()) {
        paint.setPen(Qt::blue);
        paint.drawText(transformX(it.getX()) - 4, transformY(it.getY()) + 4, "x");
        ++it;
    }
}

void Application::drawLine() {
    Log::log("Application", "drawLine");

    this->refresh();

    float a = this->serie2D.getCoefficientA();
    float b = this->serie2D.getCoefficientB();

    QPainter paint(thePaintingFrame);

    paint.drawLine(
        transformX(this->minX),
        transformY(a * this->minX + b),
        transformX(this->maxX),
        transformY(a * this->maxX + b)
    );
}

void Application::done() {
    Log::log("Application", "done");
    close();
    QApplication::exit();
}

void Application::select() {
    Log::log("Application", "select");

    QPainter paint(thePaintingFrame);
    paint.setPen(Qt::black);

    if(startingPoint.x() < 0) {
        startingPoint.setX(0);
    }
    if(startingPoint.y() < 0) {
        startingPoint.setY(0);
    }
    if(endingPoint.x() < 0) {
        endingPoint.setX(0);
    }
    if(endingPoint.y() < 0) {
        endingPoint.setY(0);
    }

    unsigned int minX = min(startingPoint.x(), endingPoint.x());
    unsigned int maxX = max(startingPoint.x(), endingPoint.x());
    unsigned int minY = min(startingPoint.y(), endingPoint.y());
    unsigned int maxY = max(startingPoint.y(), endingPoint.y());

    mutex.lock();
    Data2DIterator it(this->serie2D.getData().getData());
    while(!it.end()) {
        if(this->transformX(it.getX()) > minX
                && this->transformX(it.getX()) < maxX
                && this->transformY(it.getY()) > minY
                && this->transformY(it.getY()) < maxY) {
            it.remove();
            this->serie2D.getData().resetTotalCount();
        } else {
            ++it;
        }
    }
    this->serie2D.computeCoefficients();
    mutex.unlock();

    this->refresh();
}

void Application::mouseMoveEvent(QMouseEvent* e) {
    if(isMouseButtonDown) {
        QPainter paint(thePaintingFrame);
        this->refresh();
        QPoint endingPoint = e->pos();
        endingPoint.setX(endingPoint.x() - 20);
        endingPoint.setY(endingPoint.y() - 20);

        drawRect(paint, startingPoint, endingPoint);
    }
}

void Application::mouseReleaseEvent(QMouseEvent* e) {
    QPainter paint(thePaintingFrame);
    if(isMouseButtonDown) {
        endingPoint = e->pos();
        endingPoint.setX(endingPoint.x() - 20);
        endingPoint.setY(endingPoint.y() - 20);
        isMouseButtonDown = false;
    }

    this->drawRect(paint, startingPoint, endingPoint);
}

void Application::mousePressEvent(QMouseEvent* e) {
    if(!isMouseButtonDown) {
        startingPoint = e->pos();
        startingPoint.setX(startingPoint.x() - 20);
        startingPoint.setY(startingPoint.y() - 20);
        isMouseButtonDown = true;
    }
}

unsigned Application::transformX(float pX) const {
    return (unsigned) round((pX - minX) / (maxX - minX) * (WIDTH - 40)) + 10;
}

unsigned Application::transformY(float pY) const {
    return HEIGHT - 20 - (unsigned) round((pY - minY) / (maxY - minY) * (HEIGHT - 40));
}

void Application::drawRect(QPainter& paint, const QPoint& p1, const QPoint& p2) {
    int minX = min(p1.x(), p2.x());
    int maxX = max(p1.x(), p2.x());
    int minY = min(p1.y(), p2.y());
    int maxY = max(p1.y(), p2.y());

    paint.drawRect(minX, minY, maxX - minX, maxY - minY);
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
