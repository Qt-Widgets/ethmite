/****************************************************************************
** Meta object code from reading C++ file 'PlotForm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PlotForm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PlotForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PlotForm_t {
    QByteArrayData data[10];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlotForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlotForm_t qt_meta_stringdata_PlotForm = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PlotForm"
QT_MOC_LITERAL(1, 9, 15), // "setScaleEngineY"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "checked"
QT_MOC_LITERAL(4, 34, 12), // "setAutoScale"
QT_MOC_LITERAL(5, 47, 7), // "rescale"
QT_MOC_LITERAL(6, 55, 5), // "value"
QT_MOC_LITERAL(7, 61, 4), // "save"
QT_MOC_LITERAL(8, 66, 6), // "zoomIn"
QT_MOC_LITERAL(9, 73, 7) // "zoomOut"

    },
    "PlotForm\0setScaleEngineY\0\0checked\0"
    "setAutoScale\0rescale\0value\0save\0zoomIn\0"
    "zoomOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlotForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    1,   47,    2, 0x08 /* Private */,
       5,    1,   50,    2, 0x08 /* Private */,
       7,    0,   53,    2, 0x08 /* Private */,
       8,    0,   54,    2, 0x08 /* Private */,
       9,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PlotForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlotForm *_t = static_cast<PlotForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setScaleEngineY((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setAutoScale((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->rescale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->save(); break;
        case 4: _t->zoomIn(); break;
        case 5: _t->zoomOut(); break;
        default: ;
        }
    }
}

const QMetaObject PlotForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlotForm.data,
      qt_meta_data_PlotForm,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PlotForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlotForm::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PlotForm.stringdata0))
        return static_cast<void*>(const_cast< PlotForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int PlotForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
