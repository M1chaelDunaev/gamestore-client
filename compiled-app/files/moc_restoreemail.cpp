/****************************************************************************
** Meta object code from reading C++ file 'restoreemail.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DesktopClient_qt6/restoreemail.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'restoreemail.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSRestoreEmailENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSRestoreEmailENDCLASS = QtMocHelpers::stringData(
    "RestoreEmail",
    "on_GetCode_button_clicked",
    "",
    "on_ChangeEmail_button_clicked",
    "on_Close_button_clicked",
    "setPhoneCode",
    "_text"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSRestoreEmailENDCLASS_t {
    uint offsetsAndSizes[14];
    char stringdata0[13];
    char stringdata1[26];
    char stringdata2[1];
    char stringdata3[30];
    char stringdata4[24];
    char stringdata5[13];
    char stringdata6[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSRestoreEmailENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSRestoreEmailENDCLASS_t qt_meta_stringdata_CLASSRestoreEmailENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "RestoreEmail"
        QT_MOC_LITERAL(13, 25),  // "on_GetCode_button_clicked"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 29),  // "on_ChangeEmail_button_clicked"
        QT_MOC_LITERAL(70, 23),  // "on_Close_button_clicked"
        QT_MOC_LITERAL(94, 12),  // "setPhoneCode"
        QT_MOC_LITERAL(107, 5)   // "_text"
    },
    "RestoreEmail",
    "on_GetCode_button_clicked",
    "",
    "on_ChangeEmail_button_clicked",
    "on_Close_button_clicked",
    "setPhoneCode",
    "_text"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSRestoreEmailENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x08,    1 /* Private */,
       3,    0,   39,    2, 0x08,    2 /* Private */,
       4,    0,   40,    2, 0x08,    3 /* Private */,
       5,    1,   41,    2, 0x08,    4 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

Q_CONSTINIT const QMetaObject RestoreEmail::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSRestoreEmailENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSRestoreEmailENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSRestoreEmailENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<RestoreEmail, std::true_type>,
        // method 'on_GetCode_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ChangeEmail_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Close_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setPhoneCode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void RestoreEmail::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RestoreEmail *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_GetCode_button_clicked(); break;
        case 1: _t->on_ChangeEmail_button_clicked(); break;
        case 2: _t->on_Close_button_clicked(); break;
        case 3: _t->setPhoneCode((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *RestoreEmail::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RestoreEmail::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSRestoreEmailENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int RestoreEmail::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
