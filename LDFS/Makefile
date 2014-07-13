CC		:=	gcc
AR		:=	ar
SDIR	:=	source
IDIR	:=	include
CFLAGS	:=	-I$(IDIR)
LFLAGS	:=	-lmingw32 -mwindows -lwinmm -lws2_32 -lopengl32 -lglu32
ODIR	:=	build
CFILES	:=	$(wildcard $(SDIR)/*.c)
OBJS	:=	$(patsubst $(SDIR)/%.c, build/%.o, $(wildcard $(SDIR)/*.c))

.PHONY: all

all: ../libdynamicLDFS.a ../LDFS.dll ../libstaticLDFS.a

../libdynamicLDFS.a ../LDFS.dll: $(ODIR) $(OBJS)
	$(CC) -shared -o ../LDFS.dll $(OBJS) -Wl,--out-implib,../libdynamicLDFS.a $(LFLAGS)

../libstaticLDFS.a: $(ODIR) $(OBJS)
	$(AR) rcs ../libstaticLDFS.a $(OBJS)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(LFLAGS)

$(ODIR):
	@mkdir $@

.PHONY: clean

clean:
	rm -f ../libdynamicLDFS.a ../LDFS.dll ../libstaticLDFS.a $(ODIR)/*.o
	rmdir $(ODIR)
