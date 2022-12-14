CC = g++
CFLAGS = -std=c++20
ODIR = obj
SDIR = src
OBJ = logger.o comparator.o socket.o exchange.o

_OBJS = server.o $(OBJ)
OBJS = $(patsubst %, $(ODIR)/%, $(_OBJS))

server: $(OBJS)
	$(CC) $(CFLAGS) -o target/$@ $(OBJS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(ODIR)/*.o target/server