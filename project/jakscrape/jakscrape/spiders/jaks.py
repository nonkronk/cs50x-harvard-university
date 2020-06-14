import scrapy
from scrapy.spiders import CrawlSpider, Rule
from scrapy.linkextractors import LinkExtractor
from jakscrape.items import JakscrapeItem
from scrapy.loader import ItemLoader
from scrapy.loader.processors import MapCompose, TakeFirst
from scrapy.crawler import CrawlerProcess

class JaksSpider(CrawlSpider):
    name = 'jaks'
    allowed_domains = ['jakartanotebook.com']
    start_urls = ["https://www.jakartanotebook.com/jam-tangan-pria?show=100"]

    rules = [
        Rule(
            LinkExtractor(allow=(r'jam-tangan-pria\?show=100\&page=\d+',)),
            callback='parse_page', follow=True)
    ]

    def parse_page(self, response):
        for href in response.xpath('//*[@class="product-list__title"]/@href'):
            url = response.urljoin(href.extract())
            yield scrapy.Request(url, callback=self.parse_detail_page)


    def parse_detail_page(self,response):
        item = JakscrapeItem()
        l = ItemLoader(item, response=response)
        #l.add_value('title', 'Jam Tangan')
        l.add_xpath('title', '//span[@itemprop="name"]/h1/text()', MapCompose(lambda i: i.replace('Jam Tangan', '')))
        l.add_xpath('weight', '(//div[@class="detailInfo"]/dl/dd)[2]//text()', MapCompose(lambda i: i.replace(' kg', ''), float))
        l.add_xpath('sku', '(//div[@class="detailInfo"]/dl/dd)[1]//text()')
        l.add_xpath('color', '//div[@class="detailColor"]/ul/li/a/@title', TakeFirst())
        l.add_xpath('warranty', '(//div[@class="detailInfo"]/dl/dd)[3]//text()')
        l.add_xpath('price', '//span[@itemprop="price"]/text()', TakeFirst(), MapCompose(lambda i: i.replace('.', ''), int))
        l.add_xpath('false_price', '//span[@class="price-false"]/text()', TakeFirst(), MapCompose(lambda i: i.replace('Rp. ', '').replace('.', ''), int))
        l.add_xpath('image_urls', '//div[@class="detailGallery"]/a/@href')
        l.add_xpath('stock', '//div[@class="product-list__stock--branch"]//span/text()')
        l.add_xpath('rating_count', '//span[@itemprop = "reviewCount"]/text()', TakeFirst())
        l.add_value('body', "*** RUMAH JAM BANDUNG ***\nhttps://www.tokopedia.com/rjmb\nMember of RUMAH BANDUNG GROUP\nhttps://www.tokopedia.com/rbgroup\n\n*)")  # HEADER
        l.add_xpath('body', '//h2[contains(.,"Overview")]/text()', MapCompose(str.strip), MapCompose(lambda i: i.replace('Overview of ','INFORMASI PRODUK\n')))  # OVERVIEW
        l.add_value('body', '\nGARANSI')
        l.add_xpath('body', '(//div[@class="detailInfo"]/dl/dd)[4]//text()', MapCompose(str.upper), MapCompose(lambda i: i.replace('No Warranty', 'PM')))  # WARRANTY
        l.add_value('body', '-')
        l.add_xpath('body', '(//div[@class="detailInfo"]/dl/dd)[2]//text()')  # SKU
        l.add_value('body', '(KODE KLAIM)\n\n')
        l.add_xpath('body', '//div[@class="boxContent mce"]/p/text()')  # OVERVIEW BODY
        l.add_value('body', '\n\n*) KEUNGGULAN PRODUK\n-')
        l.add_xpath('body', '(//div[@class="h3"]//text())[1]')  # FEATURES SECTION 1
        l.add_value('body', '\n')
        l.add_xpath('body', '(//table[@class="stdTable noBorder"]//p/text())[1]')  # FEATURES BODY 1
        l.add_value('body', '\n\n-')
        l.add_xpath('body', '(//div[@class="h3"]//text())[2]')  # FEATURES SECTION 2
        l.add_value('body', '\n')
        l.add_xpath('body', '(//table[@class="stdTable noBorder"]//p/text())[2]')  # FEATURES BODY 2
        l.add_value('body', '\n\n-')
        l.add_xpath('body', '(//div[@class="h3"]//text())[3]')  # FEATURES SECTION 3
        l.add_value('body', '\n')
        l.add_xpath('body', '(//table[@class="stdTable noBorder"]//p/text())[3]')  # FEATURES BODY 3
        l.add_value('body', '\n\n-')
        l.add_xpath('body', '(//div[@class="h3"]//text())[4]')  # FEATURES SECTION 4
        l.add_value('body', '\n')
        l.add_xpath('body', '(//table[@class="stdTable noBorder"]//p/text())[4]')  # FEATURES BODY 4
        l.add_value('body', '\n\n*) Request Produk & Reseller Dropship a.n. Agan Sendiri :\nSMS / WA : 0823-1724-1783\nLINE : rbgroupindo\nBBM : 5f-753-d0f')  # CONTACT
        l.add_value('category1', 'Fashion & Aksesoris')
        l.add_value('category2', 'Jam Tangan')
        l.add_value('url', response.url)
        yield l.load_item()


if __name__ == "__main__":
    process = CrawlerProcess({
        'USER_AGENT': 'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)'
    })

    process.crawl(JaksSpider)
    process.start()
