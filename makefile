
# Run the following for the Client
Client11: PracticalSocket.o
        g++ -o Client11 Client11.cpp PracticalSocket.o
PracticalSocket.o: PracticalSocket.cpp PracticalSocket.h
        g++ -c PracticalSocket.cpp

clean:
        rm *.o

cpplint-Client: Client11
	cpplint bank.h PracticalSocket.cpp Client11.cpp

run-Client: Client11
        ./Client11

# Run the following for the Server
Server11: PracticalSocket.o
        g++ -o Server11 Server11.cpp PracticalSocket.o
PracticalSocket.o: PracticalSocket.cpp PracticalSocket.h
        g++ -c PracticalSocket.cpp

clean:
        rm *.o

cpplint-Server: Server11
	cpplint bank.h PracticalSocket.cpp Server11.cpp

run-Server: Server11
        ./Server11
