/****************************************************************************
** Meta object code from reading C++ file '_quickcode.h'
**
** Created: Sat May 2 07:55:08 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_quickcode.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_quickcode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__quickcode[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__quickcode[] = {
    "_quickcode\0"
};

const QMetaObject _quickcode::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata__quickcode,
      qt_meta_data__quickcode, 0 }
};

const QMetaObject *_quickcode::metaObject() const
{
    return &staticMetaObject;
}

void *_quickcode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__quickcode))
        return static_cast<void*>(const_cast< _quickcode*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int _quickcode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE