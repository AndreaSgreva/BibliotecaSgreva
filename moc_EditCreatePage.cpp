/****************************************************************************
** Meta object code from reading C++ file 'EditCreatePage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "gui/EditCreatePage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EditCreatePage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_EditCreatePage_t {
    uint offsetsAndSizes[18];
    char stringdata0[15];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[8];
    char stringdata5[12];
    char stringdata6[12];
    char stringdata7[9];
    char stringdata8[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_EditCreatePage_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_EditCreatePage_t qt_meta_stringdata_EditCreatePage = {
    {
        QT_MOC_LITERAL(0, 14),  // "EditCreatePage"
        QT_MOC_LITERAL(15, 11),  // "itemCreated"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 11),  // "Biblioteca*"
        QT_MOC_LITERAL(40, 7),  // "newItem"
        QT_MOC_LITERAL(48, 11),  // "itemUpdated"
        QT_MOC_LITERAL(60, 11),  // "updatedItem"
        QT_MOC_LITERAL(72, 8),  // "saveItem"
        QT_MOC_LITERAL(81, 6)   // "goBack"
    },
    "EditCreatePage",
    "itemCreated",
    "",
    "Biblioteca*",
    "newItem",
    "itemUpdated",
    "updatedItem",
    "saveItem",
    "goBack"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_EditCreatePage[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,
       5,    1,   41,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   44,    2, 0x08,    5 /* Private */,
       8,    0,   45,    2, 0x08,    6 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject EditCreatePage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_EditCreatePage.offsetsAndSizes,
    qt_meta_data_EditCreatePage,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_EditCreatePage_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<EditCreatePage, std::true_type>,
        // method 'itemCreated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Biblioteca *, std::false_type>,
        // method 'itemUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Biblioteca *, std::false_type>,
        // method 'saveItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goBack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void EditCreatePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EditCreatePage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->itemCreated((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        case 1: _t->itemUpdated((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        case 2: _t->saveItem(); break;
        case 3: _t->goBack(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EditCreatePage::*)(Biblioteca * );
            if (_t _q_method = &EditCreatePage::itemCreated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EditCreatePage::*)(Biblioteca * );
            if (_t _q_method = &EditCreatePage::itemUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *EditCreatePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditCreatePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EditCreatePage.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Visitor"))
        return static_cast< Visitor*>(this);
    return QWidget::qt_metacast(_clname);
}

int EditCreatePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void EditCreatePage::itemCreated(Biblioteca * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EditCreatePage::itemUpdated(Biblioteca * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
