all:
	python config.py
	g++ ranking.cpp -std=gnu++11 -o ranking
	

clean: 
	rm ResultantRanks_A1.txt ResultantRanks_A2.txt UniqueDocuments.txt jaguar_google.txt jaguar_yahoo.txt ./ranking *.csv *.db