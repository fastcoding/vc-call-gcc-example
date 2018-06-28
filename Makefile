CC=gcc
CXX=cl
M=X64

perl=$(shell perl -MConfig -e "print($$Config{{perlpath}})")
incdir=$(shell $(perl) -MConfig -e "print($$Config{{archlib}})")/CORE
code="print($$Config{{ccflags}})"
vers=$(shell $(perl) -MConfig -e "print $$Config{{api_revision}}.$$Config{{api_version}}")
libperl=$(shell $(perl) -MConfig -e "print $$Config{{libperl}}")
CFLAGS:=$(shell $(perl) -MConfig -e "$(code)" ) -I$(incdir) -DDLL
CXXFLAGS:=/MD /I. /Gd

LDFLAGS=$(shell $(perl) -MConfig -e "for $$i(ldflags,libs) {\
	print($$Config{{$$i}},' ')}" ) -lperl$(vers) -Wl,--output-def,test.def 
	
OBJS:=test.obj
	     
all: main.exe test.dll

distclean:
	-@del *~ >nul
	-@del *.obj *.exp *.lib *.def>nul
	-@del perl$(vers)*.* >nul
clean:distclean
	-@del main.exe test.dll >nul
	
testvc.exe:
	cl /MD /I$(incdir) test.c /link /nodefaultlib /out:$@ /libpath:./ perl524.lib


test.dll:test.obj
	@echo
	$(CC) -shared -dll -o$@ $^ $(LDFLAGS)

%.obj:%.c
	@echo ================ USING GCC ================
	$(CC) $(CFLAGS) -o $@ -c $^ 

test.def: test.dll

test.lib: test.def
	lib /machine:$(M) /def:$^ /out:$@

main.exe: main.cpp test.lib
	@echo 
	@echo ==================== USING MS Visual Studio ====================
	$(CXX) $(CXXFLAGS) main.cpp /link /machine:$(M) /out:$@ test.lib
