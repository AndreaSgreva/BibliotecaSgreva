/****************************************************************************
** Meta object code from reading C++ file 'AdminPage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "gui/AdminPage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AdminPage.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_AdminPage_t {
    uint offsetsAndSizes[36];
    char stringdata0[10];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[5];
    char stringdata5[12];
    char stringdata6[11];
    char stringdata7[11];
    char stringdata8[6];
    char stringdata9[7];
    char stringdata10[7];
    char stringdata11[7];
    char stringdata12[15];
    char stringdata13[4];
    char stringdata14[19];
    char stringdata15[7];
    char stringdata16[16];
    char stringdata17[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_AdminPage_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_AdminPage_t qt_meta_stringdata_AdminPage = {
    {
        QT_MOC_LITERAL(0, 9),  // "AdminPage"
        QT_MOC_LITERAL(10, 11),  // "itemUpdated"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 11),  // "Biblioteca*"
        QT_MOC_LITERAL(35, 4),  // "item"
        QT_MOC_LITERAL(40, 11),  // "itemRemoved"
        QT_MOC_LITERAL(52, 10),  // "createItem"
        QT_MOC_LITERAL(63, 10),  // "modifyItem"
        QT_MOC_LITERAL(74, 5),  // "close"
        QT_MOC_LITERAL(80, 6),  // "goBack"
        QT_MOC_LITERAL(87, 6),  // "search"
        QT_MOC_LITERAL(94, 6),  // "filter"
        QT_MOC_LITERAL(101, 14),  // "prenotaOggetto"
        QT_MOC_LITERAL(116, 3),  // "obj"
        QT_MOC_LITERAL(120, 18),  // "restituisciOggetto"
        QT_MOC_LITERAL(139, 6),  // "create"
        QT_MOC_LITERAL(146, 15),  // "modificaOggetto"
        QT_MOC_LITERAL(162, 14)   // "eliminaOggetto"
    },
    "AdminPage",
    "itemUpdated",
    "",
    "Biblioteca*",
    "item",
    "itemRemoved",
    "createItem",
    "modifyItem",
    "close",
    "goBack",
    "search",
    "filter",
    "prenotaOggetto",
    "obj",
    "restituisciOggetto",
    "create",
    "modificaOggetto",
    "eliminaOggetto"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_AdminPage[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   92,    2, 0x06,    1 /* Public */,
       5,    1,   95,    2, 0x06,    3 /* Public */,
       6,    0,   98,    2, 0x06,    5 /* Public */,
       7,    1,   99,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,  102,    2, 0x08,    8 /* Private */,
       9,    0,  103,    2, 0x08,    9 /* Private */,
      10,    0,  104,    2, 0x08,   10 /* Private */,
      11,    0,  105,    2, 0x08,   11 /* Private */,
      12,    1,  106,    2, 0x08,   12 /* Private */,
      14,    1,  109,    2, 0x08,   14 /* Private */,
      15,    0,  112,    2, 0x08,   16 /* Private */,
      16,    1,  113,    2, 0x08,   17 /* Private */,
      17,    1,  116,    2, 0x08,   19 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,   13,
    QMetaType::Void, 0x80000000 | 3,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,   13,
    QMetaType::Void, 0x80000000 | 3,   13,

       0        // eod
};

Q_CONSTINIT const QMetaObject AdminPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_AdminPage.offsetsAndSizes,
    qt_meta_data_AdminPage,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_AdminPage_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<AdminPage, std::true_type>,
        // method 'itemUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Biblioteca *, std::false_type>,
        // method 'itemRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Biblioteca *, std::false_type>,
        // method 'createItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'modifyItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Biblioteca *, std::false_type>,
        // method 'close'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goBack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'search'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'filter'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'prenotaOggetto'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Biblioteca *, std::false_type>,
        // method 'restituisciOggetto'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Biblioteca *, std::false_type>,
        // method 'create'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'modificaOggetto'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Biblioteca *, std::false_type>,
        // method 'eliminaOggetto'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Biblioteca *, std::false_type>
    >,
    nullptr
} };

void AdminPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AdminPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->itemUpdated((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        case 1: _t->itemRemoved((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        case 2: _t->createItem(); break;
        case 3: _t->modifyItem((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        case 4: _t->close(); break;
        case 5: _t->goBack(); break;
        case 6: _t->search(); break;
        case 7: _t->filter(); break;
        case 8: _t->prenotaOggetto((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        case 9: _t->restituisciOggetto((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        case 10: _t->create(); break;
        case 11: _t->modificaOggetto((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        case 12: _t->eliminaOggetto((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AdminPage::*)(Biblioteca * );
            if (_t _q_method = &AdminPage::itemUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AdminPage::*)(Biblioteca * );
            if (_t _q_method = &AdminPage::itemRemoved; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AdminPage::*)();
            if (_t _q_method = &AdminPage::createItem; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AdminPage::*)(Biblioteca * );
            if (_t _q_method = &AdminPage::modifyItem; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *AdminPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AdminPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AdminPage.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "JsonObserver"))
        return static_cast< JsonObserver*>(this);
    return QWidget::qt_metacast(_clname);
}

int AdminPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void AdminPage::itemUpdated(Biblioteca * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AdminPage::itemRemoved(Biblioteca * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AdminPage::createItem()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AdminPage::modifyItem(Biblioteca * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
