/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue May 22 19:22:59 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      22,   11,   11,   11, 0x05,
      33,   11,   11,   11, 0x05,
      43,   11,   11,   11, 0x05,
      59,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      77,   11,   11,   11, 0x08,
      92,   11,   11,   11, 0x08,
     107,   11,   11,   11, 0x08,
     120,   11,   11,   11, 0x08,
     140,   11,   11,   11, 0x08,
     159,   11,   11,   11, 0x08,
     181,   11,   11,   11, 0x08,
     194,   11,   11,   11, 0x08,
     233,   11,   11,   11, 0x08,
     274,   11,   11,   11, 0x08,
     286,   11,   11,   11, 0x08,
     299,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0clicked()\0released()\0"
    "timeout()\0sliderPressed()\0valueChanged(int)\0"
    "openFileSlot()\0setParasSlot()\0"
    "panPicSlot()\0MagnifyActionSlot()\0"
    "NewROIActionSlot()\0DeleteROIActionSlot()\0"
    "timeUpdate()\0VerticalScrollBarValueChangedSlot(int)\0"
    "HorizontalScrollBarValueChangedSlot(int)\0"
    "isPressed()\0isReleased()\0mousePressEventSlot()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->released(); break;
        case 2: _t->timeout(); break;
        case 3: _t->sliderPressed(); break;
        case 4: _t->valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->openFileSlot(); break;
        case 6: _t->setParasSlot(); break;
        case 7: _t->panPicSlot(); break;
        case 8: _t->MagnifyActionSlot(); break;
        case 9: _t->NewROIActionSlot(); break;
        case 10: _t->DeleteROIActionSlot(); break;
        case 11: _t->timeUpdate(); break;
        case 12: _t->VerticalScrollBarValueChangedSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->HorizontalScrollBarValueChangedSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->isPressed(); break;
        case 15: _t->isReleased(); break;
        case 16: _t->mousePressEventSlot(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWindow::released()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainWindow::timeout()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MainWindow::sliderPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void MainWindow::valueChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
