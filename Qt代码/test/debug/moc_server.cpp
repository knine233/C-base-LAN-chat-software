/****************************************************************************
** Meta object code from reading C++ file 'server.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_server_t {
    QByteArrayData data[10];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_server_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_server_t qt_meta_stringdata_server = {
    {
QT_MOC_LITERAL(0, 0, 6), // "server"
QT_MOC_LITERAL(1, 7, 22), // "pre_connection_request"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 21), // "upload_to_display_msg"
QT_MOC_LITERAL(4, 53, 3), // "msg"
QT_MOC_LITERAL(5, 57, 19), // "update_host_usrlist"
QT_MOC_LITERAL(6, 77, 4), // "info"
QT_MOC_LITERAL(7, 82, 9), // "is_append"
QT_MOC_LITERAL(8, 92, 24), // "recv_clinet_file_request"
QT_MOC_LITERAL(9, 117, 28) // "s_snd_file_request_to_client"

    },
    "server\0pre_connection_request\0\0"
    "upload_to_display_msg\0msg\0update_host_usrlist\0"
    "info\0is_append\0recv_clinet_file_request\0"
    "s_snd_file_request_to_client"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_server[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,
       5,    2,   43,    2, 0x06 /* Public */,
       8,    1,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    6,    7,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<server *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pre_connection_request(); break;
        case 1: _t->upload_to_display_msg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->update_host_usrlist((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->recv_clinet_file_request((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->s_snd_file_request_to_client((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (server::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&server::pre_connection_request)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (server::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&server::upload_to_display_msg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (server::*)(QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&server::update_host_usrlist)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (server::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&server::recv_clinet_file_request)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject server::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_server.data,
    qt_meta_data_server,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *server::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_server.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void server::pre_connection_request()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void server::upload_to_display_msg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void server::update_host_usrlist(QString _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void server::recv_clinet_file_request(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
