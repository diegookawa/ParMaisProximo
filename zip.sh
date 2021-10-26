sudo apt install -y zip
ra="./2127890_2127997"
rm -rf "$ra.zip" $ra
mkdir $ra
cp Makefile closest.c "$ra/"
zip "$ra.zip" -r $ra
rm -rf $ra