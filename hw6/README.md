To compile search: 
qmake
make

After compiling search to generate object code, use this to compile crawler:
g++ -g -Wall webpage.o pageparsermarkdown.o util.o crawler.cpp -o crawler
