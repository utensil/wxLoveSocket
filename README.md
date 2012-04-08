wxLoveSocket
================

A wxWidgets based IM program, written just for fun.

Features
--------------

* text chat
* changing nickname and feeling
* changing face
* changing fonts for nickname and chat content
* save chat history to plain text file
* file transfer
* i18n, can choose English or Chinese UI, and automatically reboot to take effect

Development Status
--------------------

The code is really messy and buggy, because they were written years ago.

A refactor is planned.

Build
-----------------

For the time being, we only provides Makefile for MinGW under Windows, but it's easy to port it to other OS or compilers.

* Build wxWidgets
* Modify WX_SOURCE_ROOT in Makefile to where you place wxWidgets source
* Under MSYS, `make`

Build wxWidgets
-----------------

* Use subversion client to check out wxWidgets source to ${WX_SOURCE_ROOT}, eg. C:\wxWidgets
* See ${WX_SOURCE_ROOT}/BuildSVN.txt for building instructions
* Copy ${WX_SOURCE_ROOT}\include\wx\msw\setup0.h to ${WX_SOURCE_ROOT}\include\wx\msw\setup.h
* Under MSYS, `cd` into  the directory 'build/msw', and `make -f makefile.gcc SHARED=1 MONOLITHIC=1 BUILD=debug UNICODE=1`

Acknowledgments
-----------------

* wxWidgets authors

Licence
-----------------

MIT Licence, see LICENCE.
Copyright (c) 2011-2012 Utensil Song (https://github.com/utensil)