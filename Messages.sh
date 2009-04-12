#!/bin/sh
$EXTRACTRC `find . -name \*.rc` `find . -name \*.ui` `find . -name \*.kcfg` >> rc.cpp
$XGETTEXT `find . -name \*.cc -o -name \*.cpp -o -name \*.h` -o $podir/kdevjava.pot
rm -f rc.cpp
