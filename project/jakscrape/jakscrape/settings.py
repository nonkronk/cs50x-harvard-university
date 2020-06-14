

BOT_NAME = 'jakscrape'
SPIDER_MODULES = ['jakscrape.spiders']
NEWSPIDER_MODULE = 'jakscrape.spiders'
ITEM_PIPELINES = {
    'jakscrape.pipelines.JakscrapePipeline': 1,
    'jakscrape.pipelines.JakCsvPipeline': 1000000,
    'jakscrape.pipelines.JakImagesPipeline': 1,
    }
# IMAGES_STORE = 'D:\j'
IMAGES_STORE = '/Users/nonkronk/github/cs50x-harvard-university/project/jakscrape/scraped_img'
ROBOTSTXT_OBEY = False
USER_AGENT = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.106 Safari/537.36'
COOKIES_ENABLED = False
#CONCURRENT_REQUEST_PER_DOMAIN = 1
#DOWNLOAD_DELAY = 5

