/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[350];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 26), // "snd_file_request_to_client"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 4), // "info"
QT_MOC_LITERAL(4, 44, 29), // "on_toolButton_filesnd_clicked"
QT_MOC_LITERAL(5, 74, 24), // "s_pre_connection_request"
QT_MOC_LITERAL(6, 99, 16), // "s_recv_group_msg"
QT_MOC_LITERAL(7, 116, 3), // "msg"
QT_MOC_LITERAL(8, 120, 23), // "s_upload_to_display_msg"
QT_MOC_LITERAL(9, 144, 26), // "on_pushButton_send_clicked"
QT_MOC_LITERAL(10, 171, 21), // "s_update_host_usrlist"
QT_MOC_LITERAL(11, 193, 9), // "is_append"
QT_MOC_LITERAL(12, 203, 30), // "on_toolButton_chatsavr_clicked"
QT_MOC_LITERAL(13, 234, 29), // "on_toolButton_p2pchat_clicked"
QT_MOC_LITERAL(14, 264, 19), // "s_recv_file_request"
QT_MOC_LITERAL(15, 284, 23), // "s_snd_request_by_server"
QT_MOC_LITERAL(16, 308, 18), // "s_recv_private_msg"
QT_MOC_LITERAL(17, 327, 7), // "raw_msg"
QT_MOC_LITERAL(18, 335, 14) // "s_host_offline"

    },
    "MainWindow\0snd_file_request_to_client\0"
    "\0info\0on_toolButton_filesnd_clicked\0"
    "s_pre_connection_request\0s_recv_group_msg\0"
    "msg\0s_upload_to_display_msg\0"
    "on_pushButton_send_clicked\0"
    "s_update_host_usrlist\0is_append\0"
    "on_toolButton_chatsavr_clicked\0"
    "on_toolButton_p2pchat_clicked\0"
    "s_recv_file_request\0s_snd_request_by_server\0"
    "s_recv_private_msg\0raw_msg\0s_host_offline"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   82,    2, 0x08 /* Private */,
       5,    0,   83,    2, 0x08 /* Private */,
       6,    1,   84,    2, 0x08 /* Private */,
       8,    1,   87,    2, 0x08 /* Private */,
       9,    0,   90,    2, 0x08 /* Private */,
      10,    2,   91,    2, 0x08 /* Private */,
      12,    0,   96,    2, 0x08 /* Private */,
      13,    0,   97,    2, 0x08 /* Private */,
      14,    1,   98,    2, 0x08 /* Private */,
      15,    1,  101,    2, 0x08 /* Private */,
      16,    1,  104,    2, 0x08 /* Private */,
      18,    0,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->snd_file_request_to_client((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_toolButton_filesnd_clicked(); break;
        case 2: _t->s_pre_connection_request(); break;
        case 3: _t->s_recv_group_msg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->s_upload_to_display_msg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_send_clicked(); break;
        case 6: _t->s_update_host_usrlist((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->on_toolButton_chatsavr_clicked(); break;
        case 8: _t->on_toolButton_p2pchat_clicked(); break;
        case 9: _t->s_recv_file_request((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->s_snd_request_by_server((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->s_recv_private_msg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->s_host_offline(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::snd_file_request_to_client)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::snd_file_request_to_client(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
