CFLAGS=-Wall -g -fPIC
CXXFLAGS=$(CFLAGS)
LDFLAGS=-fPIC -Wl,--no-undefined
is_dir = $(shell if [ -d $(1) ]; then echo 1 ; else echo 0 ; fi)
.PHONY: FORCE
MACHINE=$(shell uname -m)

all : TrioPC_Linux_Test_c TrioPC_Linux_Test_cpp

TrioPC_Linux_Test_c : TrioPC_Linux_Test_c.o libTrioPC-$(MACHINE).so
	g++ $(LDFLAGS) -o $@ $^

TrioPC_Linux_Test_cpp : TrioPC_Linux_Test_cpp.o libTrioPC-$(MACHINE).so
	g++ $(LDFLAGS) -o $@ $^

TrioPC_Linux_Test_c.o : TrioPC_Linux_Test_c.c TrioPC_Linux_Test.c TrioPC_Linux.h

TrioPC_Linux_Test_cpp.o : TrioPC_Linux_Test_cpp.cpp TrioPC_Linux_Test.c TrioPC_Linux.h

TrioPC_Linux_Test_c.c : TrioPC_Linux_Test.c
	ln -s $< $@

TrioPC_Linux_Test_cpp.cpp : TrioPC_Linux_Test.c
	ln -s $< $@

ifeq ($(call is_dir,../TrioPC_Linux),1)
libTrioPC-$(MACHINE).so : ../TrioPC_Linux/libTrioPC-$(MACHINE).so
	cp $< $@

../TrioPC_Linux/libTrioPC-$(MACHINE).so : FORCE
	$(MAKE) -C ../TrioPC_Linux all

TrioPC_Linux.h : ../TrioPC_Linux/TrioPC_Linux.h
	cp $< $@

release: TrioPC-${MACHINE}.tgz

TrioPC-${MACHINE}.tgz : libTrioPC-$(MACHINE).so TrioPC_Linux.h TrioPC_Linux_Test_c.c TrioPC_Linux_Test_cpp.cpp TrioPC_Linux_Test.c Makefile
	if [ -f $(basename $@) -o -d $(basename $@) ] ; then rm -rf $(basename $@) ; fi
	mkdir $(basename $@)
	cp $^ $(basename $@)/.
	tar -czf $@ $(basename $@)
	rm -rf $(basename $@)

test.c : FORCE
	LD_LIBRARY_PATH=. ./TrioPC_Linux_Test_c tcp 192.168.2.52

test.cpp : FORCE
	LD_LIBRARY_PATH=. ./TrioPC_Linux_Test_cpp tcp 192.168.2.52
endif

clean: FORCE
	rm -rf *.o TrioPC_Linux_Test_c TrioPC_Linux_Test_cpp TrioPC_Linux TrioPC.tgz TrioPC_Linux_Test_c.c TrioPC_Linux_Test_cpp.cpp
ifeq ($(call is_dir,../TrioPC_Linux),1)
	rm -f TrioPC_Linux.h libTrioPC*.so
	$(MAKE) -C ../TrioPC_Linux clean
endif
