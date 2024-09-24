/****************************************************************************
** Meta object code from reading C++ file 'registrationwindowfinal.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DesktopClient_qt6/registrationwindowfinal.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'registrationwindowfinal.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSRegistrationWindowFinalENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSRegistrationWindowFinalENDCLASS = QtMocHelpers::stringData(
    "RegistrationWindowFinal",
    "on_Close_button_clicked",
    "",
    "on_GoBack_button_clicked",
    "setPhoneCode",
    "on_CompleteRegistration_button_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSRegistrationWindowFinalENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[24];
    char stringdata1[24];
    char stringdata2[1];
    char stringdata3[25];
    char stringdata4[13];
    char stringdata5[39];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSRegistrationWindowFinalENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSRegistrationWindowFinalENDCLASS_t qt_meta_stringdata_CLASSRegistrationWindowFinalENDCLASS = {
    {
        QT_MOC_LITERAL(0, 23),  // "RegistrationWindowFinal"
        QT_MOC_LITERAL(24, 23),  // "on_Close_button_clicked"
        QT_MOC_LITERAL(48, 0),  // ""
        QT_MOC_LITERAL(49, 24),  // "on_GoBack_button_clicked"
        QT_MOC_LITERAL(74, 12),  // "setPhoneCode"
        QT_MOC_LITERAL(87, 38)   // "on_CompleteRegistration_butto..."
    },
    "RegistrationWindowFinal",
    "on_Close_button_clicked",
    "",
    "on_GoBack_button_clicked",
    "setPhoneCode",
    "on_CompleteRegistration_button_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSRegistrationWindowFinalENDCLASS[] = {

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
       5,    0,   41,    2, 0x08,    4 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject RegistrationWindowFinal::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSRegistrationWindowFinalENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSRegistrationWindowFinalENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSRegistrationWindowFinalENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<RegistrationWindowFinal, std::true_type>,
        // method 'on_Close_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_GoBack_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setPhoneCode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_CompleteRegistration_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void RegistrationWindowFinal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RegistrationWindowFinal *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_Close_button_clicked(); break;
        case 1: _t->on_GoBack_button_clicked(); break;
        case 2: _t->setPhoneCode(); break;
        case 3: _t->on_CompleteRegistration_button_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *RegistrationWindowFinal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RegistrationWindowFinal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSRegistrationWindowFinalENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RegistrationWindowFinal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
