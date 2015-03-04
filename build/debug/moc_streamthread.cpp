/****************************************************************************
** Meta object code from reading C++ file 'streamthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../includes/Qts/streamthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'streamthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StreamThread_t {
    QByteArrayData data[27];
    char stringdata[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StreamThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StreamThread_t qt_meta_stringdata_StreamThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "StreamThread"
QT_MOC_LITERAL(1, 13, 10), // "aFrameDone"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 5), // "debug"
QT_MOC_LITERAL(4, 31, 11), // "const char*"
QT_MOC_LITERAL(5, 43, 3), // "msg"
QT_MOC_LITERAL(6, 47, 7), // "initSig"
QT_MOC_LITERAL(7, 55, 6), // "refadd"
QT_MOC_LITERAL(8, 62, 1), // "x"
QT_MOC_LITERAL(9, 64, 1), // "y"
QT_MOC_LITERAL(10, 66, 11), // "stepReached"
QT_MOC_LITERAL(11, 78, 11), // "startreplay"
QT_MOC_LITERAL(12, 90, 11), // "updateItems"
QT_MOC_LITERAL(13, 102, 11), // "streamStart"
QT_MOC_LITERAL(14, 114, 12), // "std::string&"
QT_MOC_LITERAL(15, 127, 8), // "filename"
QT_MOC_LITERAL(16, 136, 4), // "init"
QT_MOC_LITERAL(17, 141, 14), // "updateRefscene"
QT_MOC_LITERAL(18, 156, 11), // "saveBBTrack"
QT_MOC_LITERAL(19, 168, 3), // "dir"
QT_MOC_LITERAL(20, 172, 10), // "parsefname"
QT_MOC_LITERAL(21, 183, 7), // "parsegt"
QT_MOC_LITERAL(22, 191, 6), // "setPos"
QT_MOC_LITERAL(23, 198, 7), // "stepPos"
QT_MOC_LITERAL(24, 206, 6), // "getroi"
QT_MOC_LITERAL(25, 213, 8), // "checkroi"
QT_MOC_LITERAL(26, 222, 7) // "abandon"

    },
    "StreamThread\0aFrameDone\0\0debug\0"
    "const char*\0msg\0initSig\0refadd\0x\0y\0"
    "stepReached\0startreplay\0updateItems\0"
    "streamStart\0std::string&\0filename\0"
    "init\0updateRefscene\0saveBBTrack\0dir\0"
    "parsefname\0parsegt\0setPos\0stepPos\0"
    "getroi\0checkroi\0abandon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StreamThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    1,  100,    2, 0x06 /* Public */,
       6,    0,  103,    2, 0x06 /* Public */,
       7,    2,  104,    2, 0x06 /* Public */,
      10,    0,  109,    2, 0x06 /* Public */,
      11,    0,  110,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,  111,    2, 0x0a /* Public */,
      13,    1,  112,    2, 0x0a /* Public */,
      16,    0,  115,    2, 0x0a /* Public */,
      17,    0,  116,    2, 0x0a /* Public */,
      18,    1,  117,    2, 0x0a /* Public */,
      20,    0,  120,    2, 0x0a /* Public */,
      21,    0,  121,    2, 0x0a /* Public */,
      22,    1,  122,    2, 0x0a /* Public */,
      24,    0,  125,    2, 0x0a /* Public */,
      25,    2,  126,    2, 0x0a /* Public */,
      26,    0,  131,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void,
    QMetaType::Double, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void,

       0        // eod
};

void StreamThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StreamThread *_t = static_cast<StreamThread *>(_o);
        switch (_id) {
        case 0: _t->aFrameDone(); break;
        case 1: _t->debug((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 2: _t->initSig(); break;
        case 3: _t->refadd((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->stepReached(); break;
        case 5: _t->startreplay(); break;
        case 6: _t->updateItems(); break;
        case 7: _t->streamStart((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 8: { bool _r = _t->init();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: _t->updateRefscene(); break;
        case 10: _t->saveBBTrack((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 11: _t->parsefname(); break;
        case 12: _t->parsegt(); break;
        case 13: _t->setPos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->getroi(); break;
        case 15: { double _r = _t->checkroi((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 16: _t->abandon(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StreamThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StreamThread::aFrameDone)) {
                *result = 0;
            }
        }
        {
            typedef void (StreamThread::*_t)(const char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StreamThread::debug)) {
                *result = 1;
            }
        }
        {
            typedef void (StreamThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StreamThread::initSig)) {
                *result = 2;
            }
        }
        {
            typedef void (StreamThread::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StreamThread::refadd)) {
                *result = 3;
            }
        }
        {
            typedef void (StreamThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StreamThread::stepReached)) {
                *result = 4;
            }
        }
        {
            typedef void (StreamThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StreamThread::startreplay)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject StreamThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_StreamThread.data,
      qt_meta_data_StreamThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StreamThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StreamThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StreamThread.stringdata))
        return static_cast<void*>(const_cast< StreamThread*>(this));
    return QThread::qt_metacast(_clname);
}

int StreamThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void StreamThread::aFrameDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void StreamThread::debug(const char * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void StreamThread::initSig()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void StreamThread::refadd(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void StreamThread::stepReached()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void StreamThread::startreplay()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
