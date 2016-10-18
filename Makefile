CONSUMER_KEY = ""
CONSUMER_SECRET = ""
ACCESS_TOKEN = ""
ACCESS_SECRET = ""

all:
	g++ src/main.cpp  -o sloth_bot -lcurl -I.  -ltwitcurl -std=c++11
run:
	g++ src/main.cpp  -o sloth_bot -lcurl -I.  -ltwitcurl -std=c++11
	./sloth_bot $(CONSUMER_KEY) $(CONSUMER_SECRET) $(ACCESS_TOKEN) $(ACCESS_SECRET) 127