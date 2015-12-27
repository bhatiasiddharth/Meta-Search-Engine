# -*- coding: utf-8 -*-
#https://github.com/NikolaiT/GoogleScraper

from GoogleScraper import scrape_with_config, GoogleSearchError

# See in the config.cfg file for possible values
keywordname='bits'

config = {
    'SCRAPING': {
        #'use_own_ip': 'True',
        'keyword': keywordname,
        'search_engines': 'google, yahoo',
        'num_pages_for_keyword': 3,
        'num_results_per_page': 10,
        'verbosity':0,
        'scrape_method': 'http',
    }
}

try:
    search = scrape_with_config(config)
except GoogleSearchError as e:
    print(e)

# let's inspect what we got

i=1
j=1
for serp in search.serps:
    if (serp.search_engine_name == "yahoo"):
        f = open(keywordname+'_yahoo.txt','a')

    else:
        f = open(keywordname+'_google.txt','a')        

    #print(serp.scrape_method)
    #print(serp.page_number)
    #print(serp.requested_at)
    #print(serp.num_results)
    # print(serp.num_results)
    # ... more attributes ...
    for link in serp.links:
        #write(link.title)
        if (serp.search_engine_name == "yahoo"):
        	if serp.page_number is not None:
	            f.write(str(serp.page_number*100+link.rank)+'\t'+str(i)+'\t'+link.title+'\t')
	            i=i+1

        else:
        	if serp.page_number is not None:
	            f.write(str(serp.page_number*100+link.rank)+'\t'+str(j)+'\t'+link.title+'\t')
	            j=j+1            


        if(link.snippet is None):
            f.write(' \n')

        else:
            f.write(str(link.snippet)+'\n')
