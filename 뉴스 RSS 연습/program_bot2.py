import feedparser
from pprint import pprint

rss_info = feedparser.parse("http://dart.fss.or.kr/api/todayRSS.xml")
pprint(rss_info['entries'])