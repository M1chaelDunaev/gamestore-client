QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bankmessage.cpp \
    cart.cpp \
    community.cpp \
    cropperscene.cpp \
    desktopclient.cpp \
    downloader.cpp \
    editprofile.cpp \
    functions.cpp \
    gifts.cpp \
    imagecropper.cpp \
    informationalwindow.cpp \
    itemcuphead.cpp \
    itemdyinglight.cpp \
    itemeldenring.cpp \
    itemgodofwar.cpp \
    itemhorizon.cpp \
    itemlastofus.cpp \
    itemplaguetale.cpp \
    itemstray.cpp \
    itemwarhammer.cpp \
    library.cpp \
    loginwindow.cpp \
    main.cpp \
    mainapplication.cpp \
    mainwindow.cpp \
    payment.cpp \
    phonenumberlineedit.cpp \
    playwindow.cpp \
    promocodewindow.cpp \
    registrationwindow.cpp \
    registrationwindowfinal.cpp \
    restoreemail.cpp \
    restorepassword.cpp \
    restorephonenumber.cpp \
    restoresqanswer.cpp \
    searchlineedit.cpp \
    store.cpp \
    storeitem.cpp \
    storemessage.cpp \
    support.cpp \
    supportholder.cpp \
    useraccount.cpp \
    userprofile.cpp \
    wallet.cpp

HEADERS += \
    bankmessage.h \
    cart.h \
    community.h \
    cropperscene.h \
    desktopclient.h \
    downloader.h \
    editprofile.h \
    functions.h \
    gifts.h \
    imagecropper.h \
    informationalwindow.h \
    itemcuphead.h \
    itemdyinglight.h \
    itemeldenring.h \
    itemgodofwar.h \
    itemhorizon.h \
    itemlastofus.h \
    itemplaguetale.h \
    itemstray.h \
    itemwarhammer.h \
    library.h \
    loginwindow.h \
    mainapplication.h \
    mainwindow.h \
    payment.h \
    phonenumberlineedit.h \
    playwindow.h \
    promocodeslist.h \
    promocodewindow.h \
    registrationwindow.h \
    registrationwindowfinal.h \
    restoreemail.h \
    restorepassword.h \
    restorephonenumber.h \
    restoresqanswer.h \
    searchlineedit.h \
    store.h \
    storeitem.h \
    storemessage.h \
    support.h \
    supportholder.h \
    useraccount.h \
    userprofile.h \
    wallet.h

FORMS += \
    bankmessage.ui \
    cart.ui \
    community.ui \
    downloader.ui \
    editprofile.ui \
    gifts.ui \
    imagecropper.ui \
    informationalwindow.ui \
    library.ui \
    loginwindow.ui \
    mainwindow.ui \
    payment.ui \
    playwindow.ui \
    promocodewindow.ui \
    registrationwindow.ui \
    registrationwindowfinal.ui \
    restoreemail.ui \
    restorepassword.ui \
    restorephonenumber.ui \
    restoresqanswer.ui \
    store.ui \
    storeitem.ui \
    storemessage.ui \
    support.ui \
    supportholder.ui \
    userprofile.ui \
    wallet.ui

    RC_FILE += file.rc
    OTHER_FILES += file.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
