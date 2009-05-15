#!/bin/sh
# This script creates the eps files

INDIR=$1;
IMGDIR=$2;
CURDIR=$(pwd);

echo ">>> Starting";

cd $INDIR;

for i in $(ls); do
    echo ">>> Creating $i.plot";
    echo "set terminal postscript" > $i.plot;
    echo "set output \"$i.eps\"" >> $i.plot;
    echo "set key on inside bottom" >> $i.plot;
    echo "plot \"$i\" u 1:2 t \"lower bound\" w lines, \"$i\" u 1:3 t \"upper bound\" w lines" >> $i.plot;
    echo ">>> Creating $i.eps";
    gnuplot $i.plot;
    convert -rotate 90 $i.eps $i.eps
    rm $i.plot;
done;

cd $CURDIR;

echo ">>> Moving the files";

mv $INDIR/*.eps $IMGDIR;

echo ">>> Ending";

# EOF

