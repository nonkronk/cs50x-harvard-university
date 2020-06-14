import scrapy
from scrapy.item import Item, Field
from scrapy.loader.processors import TakeFirst, Join

class JakscrapeItem(Item):
    title = Field(output_processor = TakeFirst())
    sku = Field(output_processor = TakeFirst())
    color = Field(output_processor=TakeFirst())
    warranty = Field(output_processor=TakeFirst())
    weight = Field(output_processor = TakeFirst())
    price = Field(output_processor = TakeFirst())
    false_price = Field(output_processor=TakeFirst())
    stock = Field(output_processor=TakeFirst())
    rating_count = Field(output_processor=TakeFirst())
    body = Field(output_processor=Join())
    body_final = Field(output_processor = TakeFirst())
    image_urls = Field()
    images = Field()
    image_paths1 = Field(output_processor = TakeFirst())
    image_paths2 = Field(output_processor = TakeFirst())
    image_paths3 = Field(output_processor = TakeFirst())
    image_paths4 = Field(output_processor = TakeFirst())
    image_paths5 = Field(output_processor = TakeFirst())
    category1 = Field(output_processor = TakeFirst())
    category2 = Field(output_processor=TakeFirst())
    category3 = Field(output_processor=TakeFirst())
    etalase = Field(output_processor=TakeFirst())
    grosir_price = Field(output_processor=TakeFirst())
    url = Field(output_processor=TakeFirst())
    pass
