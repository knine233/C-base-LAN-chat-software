/****************************************************************************
** Meta object code from reading C++ file 'fileprodialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../fileprodialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fileprodialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Fileprodialog_t {
    QByteArrayData data[14];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Fileprodialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Fileprodialog_t qt_meta_stringdata_Fileprodialog = {
    {
QT_MOC_LITERAL(0, 0, 13), // "Fileprodialog"
QT_MOC_LITERAL(1, 14, 21), // "snd_request_by_server"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 4), // "info"
QT_MOC_LITERAL(4, 42, 20), // "to_close_this_subwin"
QT_MOC_LITERAL(5, 63, 22), // "update_the_progressbar"
QT_MOC_LITERAL(6, 86, 8), // "progress"
QT_MOC_LITERAL(7, 95, 18), // "wakeup_tips_window"
QT_MOC_LITERAL(8, 114, 10), // "event_type"
QT_MOC_LITERAL(9, 125, 21), // "on_toolButton_clicked"
QT_MOC_LITERAL(10, 147, 25), // "on_pushButton_snd_clicked"
QT_MOC_LITERAL(11, 173, 22), // "s_to_close_this_subwin"
QT_MOC_LITERAL(12, 196, 24), // "s_update_the_progressbar"
QT_MOC_LITERAL(13, 221, 20) // "s_wakeup_tips_window"

    },
    "Fileprodialog\0snd_request_by_server\0"
    "\0info\0to_close_this_subwin\0"
    "update_the_progressbar\0progress\0"
    "wakeup_tips_window\0event_type\0"
    "on_toolButton_clicked\0on_pushButton_snd_clicked\0"
    "s_to_close_this_subwin\0s_update_the_progressbar\0"
    "s_wakeup_tips_window"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Fileprodialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    0,   62,    2, 0x06 /* Public */,
       5,    1,   63,    2, 0x06 /* Public */,
       7,    1,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   69,    2, 0x08 /* Private */,
      10,    0,   70,    2, 0x08 /* Private */,
      11,    0,   71,    2, 0x08 /* Private */,
      12,    1,   72,    2, 0x08 /* Private */,
      13,    1,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    6,
    QMetaType::Void, QMetaType::Int,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    6,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void Fileprodialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Fileprodialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->snd_request_by_server((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->to_close_this_subwin(); break;
        case 2: _t->update_the_progressbar((*reinterpret_cast< const qint64(*)>(_a[1]))); break;
        case 3: _t->wakeup_tips_window((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_toolButton_clicked(); break;
        case 5: _t->on_pushButton_snd_clicked(); break;
        case 6: _t->s_to_close_this_subwin(); break;
        case 7: _t->s_update_the_progressbar((*reinterpret_cast< const qint64(*)>(_a[1]))); break;
        case 8: _t->s_wakeup_tips_window((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Fileprodialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Fileprodialog::snd_request_by_server)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Fileprodialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Fileprodialog::to_close_this_subwin)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Fileprodialog::*)(const qint64 & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Fileprodialog::update_the_progressbar)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Fileprodialog::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Fileprodialog::wakeup_tips_window)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Fileprodialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Fileprodialog.data,
    qt_meta_data_Fileprodialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Fileprodialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Fileprodialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Fileprodialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Fileprodialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Fileprodialog::snd_request_by_server(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Fileprodialog::to_close_this_subwin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Fileprodialog::update_the_progressbar(const qint64 & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Fileprodialog::wakeup_tips_window(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
