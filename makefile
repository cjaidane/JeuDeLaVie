CC = gcc
CFLAGS = -g -Wall
CPPFLAGS += -I include -I/usr/include/cairo
CFLLAGS += -I include 
LDFLAGS += -lcairo -lm -lX11
LBATH= lib/
CPATH = src/
HPATH = include/
BPATH = bin/
OPATH = obj/
DOXGEN=doxygen Doxyfile
MODE=cairo_niveau4
LIBPATH = -L lib -ljeu

vpath %.h include/
vpath %.c src/


#COMPILER SANS CAIRO, EN MODE TEXTE 
ifeq ($(MODE), TEXTE)
main : lib/libjeu.a
	mkdir -p $(BPATH)
	$(CC)  $(CFLAGS) $(CFLLAGS) $(LIBPATH) -o $@ $^ 
	mv -f $@ $(BPATH)	


obj/%.o : %.c 
	mkdir -p $(OPATH)
	$(CC) $(CFLAGS)  $(CFLLAGS) -c -o $@ $< 

lib/libjeu.a: $(addprefix $(OPATH), grille.o jeu.o main.o io.o)
		ar -crv libjeu.a $^
		mkdir -p lib
		mv -f libjeu.a lib/
		


#COMPILER AVEC CAIRO 
else
main_cairo:lib/libjeu.a
		mkdir -p $(BPATH)
		$(CC)  $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBPATH)
		mv -f $@ $(BPATH)

obj/%.o: %.c 
		mkdir -p $(OPATH)
		$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLGAS) -c -o $@ $< 

lib/libjeu.a: $(addprefix $(OPATH), grille.o jeu.o main_cairo.o io.o mode_cairo.o )
		ar -crv libjeu.a $^
		mkdir -p lib
		mv -f libjeu.a lib/

endif


clean:
	rm -f -r $(OPATH)
	rm -f -r $(BPATH)
	rm -f -r $(LBATH)
	rm -f main
	rm -f doc

dist:
	tar -czvf JaidaneChaima-GoL-v5.tar.xz makefile Doxyfile src/*.c include/*.h

doc:
	$(DOXGEN)


