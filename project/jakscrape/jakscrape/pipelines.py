import scrapy
from scrapy.pipelines.images import ImagesPipeline
from scrapy import signals
from scrapy.exporters import CsvItemExporter
from scrapy.exceptions import DropItem
from scrapy.http.request import Request
import math

class JakscrapePipeline(object):
    
    def process_item(self, item, spider):
        item['title'] = 'Jam Tangan ' + item['title']
        item['title'] = item['title'].replace('& ', '') \
            .replace('/ ', '') \
            .replace('Activated ', '') \
            .replace('American ', '') \
            .replace('Analog ', '') \
            .replace(' and ', '/') \
            .replace('Belt ', '') \
            .replace('Casual ', '') \
            .replace('Digital ', '') \
            .replace('Dual Time Zone ', '') \
            .replace('European ', '') \
            .replace('Fashionable ', '') \
            .replace('for ', '') \
            .replace('Hand-Wind Up ', '') \
            .replace('Luxury ', '') \
            .replace('Mechanical ', '') \
            .replace('Militer ', 'Military') \
            .replace('Models ', '') \
            .replace('Model ', '') \
            .replace('Outdoor ', '') \
            .replace('Pattern ', '') \
            .replace('Quartz ', '') \
            .replace('Round ', '') \
            .replace('Simple ', '') \
            .replace('Sport ', '') \
            .replace('Sports ', '') \
            .replace('Square ', '') \
            .replace('Steel ', '') \
            .replace('Strap ', '') \
            .replace('Style ', '') \
            .replace('Stylis ', '') \
            .replace('Stylish ', '') \
            .replace('Touch Screen ', '') \
            .replace('Trendy ', '') \
            .replace('Triple Time Zone ', '') \
            .replace('Watches ', '') \
            .replace('Watch ', '') \
            .replace('30M Water Resistance ', '') \
            .replace('Water Resistant 10m ', '') \
            .replace('Water Resistant 30m ', '') \
            .replace('Water Resistant 50m ', '') \
            .replace('Water Resistant ', '') \
            .replace('Waterproof ', '') \
            .replace('with ', '') \
            .replace('World Time ', '') \
            .replace('Wristband ', '')
        try:
            item['title'] = item['title'][:70]
        except IndexError:
            item['title'] = item['title']
        profit_factor = 1.2
        grosir_factor = 0.05
        admin = 5000
        gram = 1000
        round = 500
        roundweight = 50
        item['price'] = math.floor((int(item['price'] * profit_factor + admin)) / round) * round
        # item['weight'] = int(float(item['weight']) * float(gram))
        # item['weight'] = math.ceil(item['weight'] / roundweight) * roundweight
        item['grosir_price'] = math.floor(
            int(item['price'] - (grosir_factor * item['price'])) / round) * round
        body = item['body']
        # if 'Female' in body or \
        #                 'Girl' in body or \
        #                 'Girls' in body or \
        #                 'Ladies' in body or \
        #                 'Woman' in body or \
        #                 'Women' in body:
        #     item['etalase'] = "Women's Watches"
        # elif 'ESS' in body:
        #     item['etalase'] = '- ESS Watch'
        # elif 'IK' in body:
        #     item['etalase'] = '- IK Watch'
        # elif 'KINGSKY' in body:
        #     item['etalase'] = '- KINGSKY'
        # elif 'Ohsen' in body:
        #     item['etalase'] = '- Ohsen'
        # elif 'Oulm' in body:
        #     item['etalase'] = '- Oulm'
        # elif 'Ousion' in body:
        #     item['etalase'] = '- Ousion'
        # elif 'Ouyawei' in body:
        #     item['etalase'] = '- Ouyawei'
        # elif 'SKMEI' in body:
        #     item['etalase'] = '- SKMEI'
        # elif 'SKONE' in body:
        #     item['etalase'] = '- SKONE'
        # elif 'Spovan' in body:
        #     item['etalase'] = '- Spovan'
        # elif 'Umeishi' in body:
        #     item['etalase'] = '- Umeishi'
        # elif 'Weide' in body:
        #     item['etalase'] = '- Weide'
        # elif 'WEIQIN' in body:
        #     item['etalase'] = '- WEIQIN'
        # elif 'LED' in body:
        #     item['etalase'] = '- LED'
        # else:
        #     item['etalase'] = 'Other'
        item['etalase'] = "Jam Tangan"
        item['body_final'] = item['body']
        body_final = item['body_final']
        if 'LED' in body_final:
            item['category3'] = 'LED'
        elif 'Quartz' in body or \
                        'Fashion' in body or \
                        'Skeleton' in body or \
                        'Automatic' in body or \
                        'Mechanical' in body or \
                        'Simple' in body or \
                        'Casual' in body:
            item['category3'] = 'Analog'
        elif 'Sport' in body or \
                        'Fitness' in body or \
                        'Pedometer' in body or \
                        'Barometer' in body or \
                        'Outdoor' in body or \
                        'Thermometer' in body:
            item['category3'] = 'Digital'
        elif 'Digital' in body or 'digital' in body:
            item['category3'] = 'Digital'
        elif 'Analog' in body or 'analog' in body:
            item['category3'] = 'Analog'
        else:
            item['category3'] = 'Jam Tangan Lainnya'
        return item

class JakImagesPipeline(ImagesPipeline):
    def file_path(self, request, response=None, info=None):
        #sku = response.meta['sku'][0] # Like this you can use all from item, not just url.
        image_guid = request.url.split('/')[-1].replace('-',' ')
        #image_guid = request.url.replace('/','')
        return '%s' % (image_guid)

    def get_media_requests(self, item, info):
        #yield Request(item['image_urls'][0])
        for image_url in item['image_urls']:
            yield scrapy.Request(image_url)

    def item_completed(self, results, item, info):
        image_paths = [x['path'] for ok, x in results if ok]
        if not image_paths:
            raise DropItem("Item contains no images")
        try:
            item['image_paths1'] = "/Users/nonkronk/github/cs50x-harvard-university/project/jakscrape/scraped_img/"+image_paths[0]
        except IndexError:
            item['image_paths1'] = ''
        try:
            item['image_paths2'] =  "/Users/nonkronk/github/cs50x-harvard-university/project/jakscrape/scraped_img/"+image_paths[1]
        except IndexError:
            item['image_paths2'] = ''
        try:
            item['image_paths3'] =  "/Users/nonkronk/github/cs50x-harvard-university/project/jakscrape/scraped_img/"+image_paths[2]
        except IndexError:
            item['image_paths3'] = ''
        try:
            item['image_paths4'] =  "/Users/nonkronk/github/cs50x-harvard-university/project/jakscrape/scraped_img/"+image_paths[3]
        except IndexError:
            item['image_paths4'] = ''
        try:
            item['image_paths5'] =  "/Users/nonkronk/github/cs50x-harvard-university/project/jakscrape/scraped_img/"+image_paths[4]
        except IndexError:
            item['image_paths5'] = ''
        return item

class JakCsvPipeline(object):
    def __init__(self):
        self.files = {}

    @classmethod
    def from_crawler(cls, crawler):
        pipeline = cls()
        crawler.signals.connect(pipeline.spider_opened, signals.spider_opened)
        crawler.signals.connect(pipeline.spider_closed, signals.spider_closed)
        return pipeline

    def spider_opened(self, spider):
        ofile = open('%s_items.csv' % spider.name, 'w+b')
        self.files[spider] = ofile
        self.exporter = CsvItemExporter(ofile,
            fields_to_export = ['image_paths1',
                'image_paths2',
                'image_paths3',
                'image_paths4',
                'image_paths5',
                'title',
                'sku',
                'color',
                'weight',
                'stock',
                'price',
                'false_price',
                'worst_rating',
                'best_rating',
                'rating_count',
                'weight',
                'warranty',
                'category1',
                'category2',
                'category3',
                'body_final',
                'etalase',
                'grosir_price',
                'url'])
        self.exporter.start_exporting()

    def spider_closed(self, spider):
        self.exporter.finish_exporting()
        ofile = self.files.pop(spider)
        ofile.close()

    def process_item(self, item, spider):
        self.exporter.export_item(item)
        return item
