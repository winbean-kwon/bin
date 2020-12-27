import feedparser
from pprint import pprint
from dateutil import parser
from time import sleep
import telegram

# 텔레그램 봇 제어용 코드
TOKEN ='1311142887:AAFDLY28KmfIettAERH6J9QpKlCGSQgoiBo'
CHAT_ID ='894380757'
bot = telegram.Bot(token=TOKEN)

disclosure_list_old = [] #공시 정보 기억용 변수

while True:   
    #RSS 공시정보를 받아온다
    rss_info = feedparser.parse("http://dart.fss.or.kr/api/todayRSS.xml")
    disclosure_list = rss_info['entries']

    #disclosure_list_old가 비었는지 체크한다.
    if len(disclosure_list_old)==0:

        #반복문을 통해 필요한 정보만 콘솔 창에 출력한다
        for disclosure in disclosure_list:
            company = disclosure['author']
            link = disclosure['link']
            published = parser.parse(disclosure['published'])
            year = published.year
            month = published.month
            day = published.day
            hour = published.hour + 9 
            minute = published.minute
            date_info = f'{year}년 {month}월 {day}일 {hour}시 {minute}분'
            title = disclosure['title']
            message = f'{title}\n{link}\n{date_info}'

            if '코스닥' in title:
                bot.send_message(chat_id=CHAT_ID, text=message)
                print(company, link, date_info, title)
                #print(company, link, date, info, title)

            print(company, link, date_info, title)
    else: #disclosure_list_old 가 비어있지 않다면
        for disclosure in disclosure_list:
            #이전에 보냈던 공시인지 체크하기
            if disclosure['title'] == disclosure_list_old[0]['title']:
                break
            #이전에 보냈던 공시가 아니라면
            company = disclosure['author']
            link = disclosure['link']
            published = parser.parse(disclosure['published'])
            year = published.year
            month = published.month
            day = published.day
            hour = published.hour + 9 
            minute = published.minute
            date_info = f'{year}년 {month}월 {day}일 {hour}시 {minute}분'
            title = disclosure['title']
            message = f'{title}\n{link}\n{date_info}'

            if '코스닥' in title:
                bot.send_message(chat_id=CHAT_ID, text=message)
                print(company, link, date_info, title)
                #print(company, link, date info, title)

            

    # 지금 보낸 공시 정보를 기억해 놓는다.
    disclosure_list_old = disclosure_list

    #3초간 프로그램 실행을 일시정지한다.
    sleep(3)