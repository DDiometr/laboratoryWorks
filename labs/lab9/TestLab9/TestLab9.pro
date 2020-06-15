include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt
INCLUDEPATH+= D:\Downloads\Lab9_Project_for_tests
HEADERS += \
        ../../Downloads/Lab9_Project_for_tests/IKeypad.h \
        ../../Downloads/Lab9_Project_for_tests/ILatch.h \
        ../../Downloads/Lab9_Project_for_tests/lockcontroller.h \
        tst_testdivisionbyzero.h

SOURCES += \
        ../../Downloads/Lab9_Project_for_tests/lockcontroller.cpp \
        main.cpp
