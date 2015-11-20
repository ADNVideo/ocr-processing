CC=g++
CFLAGS_OCR=  -W `pkg-config --cflags --libs opencv`  -Iinclude -lswscale -lavdevice -lavformat -lavcodec -lavutil -lswresample -lz -lconfig++ -ltesseract `xml2-config --cflags --libs` -w 

PROGS_tess:= tess-ocr-detector generate-mask tracking-tess-ocr-detector lia_liblex.o charset.o manage_capital.o ocr-filter
# run_lif_cleanocr

all:  $(PROGS_tess) 

tess-ocr-detector: src/tess-ocr-detector.cc 
	$(CC) src/tess-ocr-detector.cc -o  bin/$@  $(CFLAGS_OCR)
	src/make-bundle bin/$@  bin/$@.bundle

generate-mask: src/generate-mask.cc 
	$(CC) src/generate-mask.cc -o  bin/$@  $(CFLAGS_OCR)
	src/make-bundle bin/$@  bin/$@.bundle

tracking-tess-ocr-detector: src/tracking-tess-ocr-detector.cc 
	$(CC) src/tracking-tess-ocr-detector.cc -o  bin/$@  $(CFLAGS_OCR)
	src/make-bundle bin/$@  bin/$@.bundle

C=gcc
OPTION=-Iinclude



ocr-filter: src/ocr-filter.c charset.o lia_liblex.o manage_capital.o
	gcc -Iinclude -o bin/ocr-filter src/ocr-filter.c src/charset.o src/lia_liblex.o src/manage_capital.o
	src/make-bundle bin/ocr-filter  bin/ocr-filter.bundle

lia_liblex.o: src/lia_liblex.c 
	gcc  -Iinclude -c src/lia_liblex.c -o src/lia_liblex.o

charset.o: src/charset.c
	gcc  -Iinclude -c src/charset.c -o src/charset.o

manage_capital.o: src/manage_capital.c
	gcc  -Iinclude  -c src/manage_capital.c -o src/manage_capital.o	



clean:
	rm -rf  bin/*

mrproper: clean
	rm -rf  bin/*
