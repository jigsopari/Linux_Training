BIN =  avgclient avgserver
GEN = avg_clnt.c avg_svc.c avg_xdr.c avg.h
RPCCOM = rpcgen

all: $(BIN)

avgclient: avgclient.o avg_clnt.o avg_xdr.o
	$(CC) -o $@ avgclient.o avg_clnt.o avg_xdr.o 

avgclient.o: avgclient.c avg.h
	$(CC) -g avgclient.c -c

avgserver: avgserver.o avg_svc.o avg_xdr.o
	$(CC) -o $@ avgserver.o avg_svc.o avg_xdr.o

avgserver.o: avgserver.c avg.h
	$(CC) -g avgserver.c -c

$(GEN): avg.x
	$(RPCCOM) avg.x

clean cleanup:
	rm -f $(GEN) *.o $(BIN)
