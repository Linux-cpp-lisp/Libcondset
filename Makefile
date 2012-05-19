libcondset.so: conditionset.o
	g++ $(CLNKFLAGS) -shared -fPIC -o libcondset.so conditionset.o
conditionset.o: conditionset.cpp conditionset.h
	g++ $(CFLAGS) -c -fPIC -o conditionset.o conditionset.cpp
libcondset.a: conditionset.o
	g++ -c $(CFLAGS) -o conditionset.cpp
	ar cr libcondset.a conditionset.o
install_shared: libcondset.so conditionset.h
	cp libcondset.so $(INSTALL_PREFIX)/lib/libcondset.so
	cp conditionset.h $(INSTALL_PREFIX)/include/conditionset.h
install_static: libcondset.a conditionset.h
	cp libcondset.a $(INSTALL_PREFIX)/lib/libcondset.a
	cp conditionset.h $(INSTALL_PREFIX)/include/conditionset.h
install: install_shared
clean:
	rm -f *.o libcondset.*