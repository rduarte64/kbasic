/****************************************************************************
** Meta object code from reading C++ file '_sourcecodeeditor_syntaxhighlighter.h'
**
** Created: Sat May 2 07:55:29 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_sourcecodeeditor_syntaxhighlighter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_sourcecodeeditor_syntaxhighlighter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__sourcecodeeditor_syntaxhighlighter[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__sourcecodeeditor_syntaxhighlighter[] = {
    "_sourcecodeeditor_syntaxhighlighter\0"
};

const QMetaObject _sourcecodeeditor_syntaxhighlighter::staticMetaObject = {
    { &QSyntaxHighlighter::staticMetaObject, qt_meta_stringdata__sourcecodeeditor_syntaxhighlighter,
      qt_meta_data__sourcecodeeditor_syntaxhighlighter, 0 }
};

const QMetaObject *_sourcecodeeditor_syntaxhighlighter::metaObject() const
{
    return &staticMetaObject;
}

void *_sourcecodeeditor_syntaxhighlighter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__sourcecodeeditor_syntaxhighlighter))
        return static_cast<void*>(const_cast< _sourcecodeeditor_syntaxhighlighter*>(this));
    return QSyntaxHighlighter::qt_metacast(_clname);
}

int _sourcecodeeditor_syntaxhighlighter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSyntaxHighlighter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
