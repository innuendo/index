all:	dbtest test

LDFLAGS += -lrt

test:	Timer.o Parser.o XMLStore.o TagIndex.o test.o
	$(CXX) $(LDFLAGS) $^ -o $@

dbtest:	Timer.o Parser.o XMLStore.o TagIndex.o dbtest.o
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	$(RM) *.o test dbtest

