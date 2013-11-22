LDFLAGS := `pkg-config gtkmm-3.0 --libs` -lasound
CXXFLAGS := -std=c++11 `pkg-config gtkmm-3.0 --cflags`

%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c $<

simple: audioclass.o base.o examplewindow.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)


all: simple

clean:
	rm -rf *.o simple

