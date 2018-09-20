all: PA5

# Set CFLAGS to allow Debug and issue all warnings.
CFLAGS = -g -Wall

PA5: PA5.o
	g++ $(CFLAGS) PA5.o -o PA5

PA5.o: PA5.cpp
	g++ $(CFLAGS) -c PA5.cpp

clean:
	rm -f PA5.o PA5
	rm -f -r html latex

docs:
	doxygen
	# Following lines are only needed if we want to access doc pages
	#   using a Web server.
	#chmod go+r html/*
	#cp html/* ~/public_html/cs2303assig3