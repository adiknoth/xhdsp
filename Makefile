LDFLAGS := `pkg-config gtkmm-3.0 --libs` -lasound
DEBUG := -g
FOO := -D_THREAD_SAFE -D_REENTRANT
OBJS := audioclass.o base.o examplewindow.o fadercell.o multiface.o raydat.o
CXXFLAGS := $(DEBUG) -std=c++11 `pkg-config gtkmm-3.0 --cflags`

%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c $<

simple: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)


all: simple

clean:
	rm -rf *.o simple

