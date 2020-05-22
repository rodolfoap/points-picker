BINARY=ppicker
execute(){
	./parsekml-geoportail.py placewilson/placewilson.kml > placewilson/placewilson.points
	./${BINARY} placewilson/placewilson.jpg placewilson/placewilson.points points-matrix.tpl
}
build(){
	mkdir -p build;
	pushd build &> /dev/null;
	[ -f Makefile ] || cmake .. -Wdev;
	make -j$(nproc); STATUS=$?
	popd &> /dev/null;
}
case "$1" in
	"")
		[ -f ${BINARY} ] || build;
		execute
	;;
	b)
		build
	;;
	e)
		vi -p main.cpp window.cpp window.h form.cpp form.h functions.cpp points-matrix.tpl CMakeLists.txt
		rm -f ${BINARY}
		build;
		execute;
	;;
esac
