appname := server
srcfiles := main.cpp seg7_src.cpp server.cpp LED.cpp
objects := main.o seg7_src.o server.o LED.o

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

install: $(appname)
	install -m 0755 -d $(DISTDIR)/usr/bin
	install -m 0755 $(appname) $(DISTDIR)/usr/bin

clean: 
	$(RM) $(objects) $(appname)
