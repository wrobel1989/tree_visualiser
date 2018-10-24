echo "Building and running tests.."
make -f Makefile_tests all
./runtests
sleep 1;
echo "Building and running GUI app.."
/usr/lib/x86_64-linux-gnu/qt5/bin/qmake -o Makefile vis.pro
make -f Makefile all
./vis
