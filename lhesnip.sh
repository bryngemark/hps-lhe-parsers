#!/bin/sh
lheinfile=$1

lheinfiledir="$(echo -n $lheinfile | awk -F '/' '{print $2"/"$3"/"$4"/"$5}')"
echo "Working in directory: " $lheinfiledir
rootfile="$(echo -n $lheinfile | awk -F '/' '{print $3;}')"
rootfile="${rootfile}.root"
echo "Making root file: " $rootfile
lhefilesnip=./tmp.lhe
xsec=`grep 'Integrated weight (pb)' $lheinfile | awk '{print $NF;}'`

echo "Cross-section: " $xsec
events=10000

# #for lhefile in `ls ${lhepath}`; do
echo $lheinfile;
sed -n -e '/<\/init>/,$p' $lheinfile | grep -v '</init>'  |  sed 's/\(<event>\|<\/event>\)//g'| awk '{ if( !($1==8) ) { print $0}}' >> $lhefilesnip
echo $lhefilesnip
#done
./lhetree_SIMP.exe $lhefilesnip $rootfile $xsec $events                                                                                                                                      
ROOTFILESDIR=../rootfiles/
mkdir -p $ROOTFILESDIR
mv $rootfile $ROOTFILESDIR
rm $lhefilesnip           
