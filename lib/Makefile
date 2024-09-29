CC=gcc
LN=ld

HEADERS=net.h methods/data_parsing.h logging.h setting_server.h methods/http_status.h methods/methods_get_put.h methods/methods.h methods/replace_placeholders.h methods/router.h methods/url_decoder.h methods/user_response.h db/data_processing_json.h db/cJSON-master/cJSON.h
SOURCES=net.c methods/data_parsing.c logging.c setting_server.c methods/http_status.c methods/methods_get_put.c methods/methods.c methods/replace_placeholders.c methods/router.c methods/url_decoder.c methods/user_response.c db/data_processing_json.c db/cJSON-master/cJSON.c
OBJECTS=net.o data_parsing.o logging.o setting_server.o http_status.o methods_get_put.o methods.o replace_placeholders.o router.o url_decoder.o user_response.o db/data_processing_json.o db/cJSON-master/cJSON.o

.PHONY: default
default: build link

build: $(HEADERS) $(SOURCES)
	$(CC) -c $(SOURCES)
link: $(OBJECTS)
	$(LN) -r $(OBJECTS) -o extclib.o
clean:
	rm -f *.o *.i *.s
