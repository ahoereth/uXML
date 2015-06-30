CC := g++
CFLAGS := -g -Wall
SRCDIR := src
BUILDDIR := bin
SRCEXT := cpp
TARGETLIB := uXML

TARGET := $(BUILDDIR)/lib$(TARGETLIB).a
SRCS := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRCS:.$(SRCEXT)=.o))

all: $(OBJS)
	@mkdir -p $(BUILDDIR)
	ar rcs $(TARGET) $(OBJS)
	#cp $(SRCDIR)/*.hpp $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -r $(BUILDDIR)

# TODO: Simplify this for multiple test files.
tests: $(TESTOBJS)
	$(CC) $(CFLAGS) test/tests.cpp -I src -L bin -luXML -o bin/tests
	./bin/tests
