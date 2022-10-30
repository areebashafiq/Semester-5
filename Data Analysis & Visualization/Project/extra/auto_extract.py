# function to convert utc to human readable time
from time import sleep
import pandas as pd
import requests


def utc2time(ts):
    import datetime
    return list(map(int, datetime.datetime.utcfromtimestamp(ts).strftime('%Y %m %d %H').split()))
# this function returns number of days in a month


def days_in_month(year, month):
    from calendar import monthrange
    return monthrange(year, month)[1]
# creating a list of all the coordinates


def make_coord():
    coord = []

    count = 1

    lat = 31.39
    for i in range(10):
        lon = 74.29
        for j in range(8):
            lon = round(lon, 2)
            lat = round(lat, 2)
            coord.append([count, [lat, lon]])
            count += 1
            # print(f"lat:{lat}, lon:{lon}")
            lon -= 0.02
        lat -= 0.02

    lat = 31.29
    for i in range(5):
        lon = 74.13
        for j in range(2):
            lon = round(lon, 2)
            lat = round(lat, 2)
            coord.append([count, [lat, lon]])
            count += 1
            # print(f"lat:{lat}, lon:{lon}")
            lon -= 0.02
        lat -= 0.02
    return coord


def params(data, hour, index, lon, lat):
    # a function that returns a list of parameters against a given json
    dt = data['list'][hour]['dt']
    aqi = data['list'][hour]['main']['aqi']
    co = data['list'][hour]['components']['co']
    no = data['list'][hour]['components']['no']
    no2 = data['list'][hour]['components']['no2']
    o3 = data['list'][hour]['components']['o3']
    so2 = data['list'][hour]['components']['so2']
    pm2_5 = data['list'][hour]['components']['pm2_5']
    pm10 = data['list'][hour]['components']['pm10']
    nh3 = data['list'][hour]['components']['nh3']

    temp = utc2time(dt)

    return [temp[0], temp[1], temp[2], temp[3], index, lon, lat, aqi, co, no, no2, o3, so2, nh3, pm2_5, pm10]

# function that returns dataframe of temperature coordinates for a day based on coordinates and timestamp


def temp_data(coord, ts):

    # getting number of days
    date = utc2time(ts)
    year = date[0]
    month = date[1]
    day = date[2]

    # ts is the timestamp
    # coord is the coordinates
    url = f"https://api.weatherbit.io/v2.0/history/hourly?lat={coord[0]}&lon={coord[1]}&start_date={year}-{month}-{day}%3A00&end_date={year}-{month}-{day}%3A24&key=5e76500a32524b8281b8b0ecd8822c19"
    r = requests.get(url=url)
    temp = r.json()
    arr = []
    for i in range(24):
        arr.append([temp['data'][i]['app_temp'], temp['data'][i]
                   ['dewpt'], temp['data'][i]['weather']['description']])
    return pd.DataFrame(arr, columns=['temp', 'dewpt', 'condition'])

# Function that returns a dataframe for pollution data for a day based on coordinates and timestamp


def poll_data(coord, ts, zone):

    # getting number of days
    date = utc2time(ts)
    year = date[0]
    month = date[1]
    day = date[2]

    # ts is the timestamp
    # coord is the coordinates
    url = f"https://api.openweathermap.org/data/2.5/air_pollution/history?lat={coord[0]}&lon={coord[1]}&start={ts}&end={ts+82800}&appid=8d9efe95caf3922348a458d615abeb8c"
    r = requests.get(url=url)
    data = r.json()
    arr = []
    for i in range(24):
        arr.append(params(data, i, zone, coord[0], coord[1]))
    return pd.DataFrame(arr, columns=['year', 'month', 'day', 'hour', 'zone', 'lon', 'lat', 'aqi', 'co', 'no', 'no2', 'o3', 'so2', 'nh3', 'pm2_5', 'pm10'])
# function that extracts data for a day and returns a dataframe


def get_data(coord, ts):
    sleep(1)  # to avoid rate limit
    temp = temp_data(coord[1], ts)
    poll = poll_data(coord[1], ts, coord[0])
    return pd.concat([poll, temp], axis=1)


'''
steps to do:
1. read timestamp from csv
2. get next day from timestamp
3. get number of days loop should be called
4. create coordinates
5. create a loop to get data for each coordinate
    - get pollution data for each day
    - get weather data for each day
    - combine both dataframes
6. combine dataframes in that specified order
7. append dataframe to csv
8. save updated timestamp to csv
'''


# reading timestamp from txt file into a variable
try:
    with open('timestamp.txt', 'r') as f:
        timestamp = int(f.read())
# writing timestamp to txt file if not found
except:
    timestamp = 1609459200  # for january 1, 2021
    with open('timestamp.txt', 'w') as f:
        f.write(str(timestamp))

# getting number of days loop should be called
days = days_in_month(utc2time(timestamp)[0], utc2time(timestamp)[1])
# creating coordinates
coord = make_coord()

# creating a loop to get data for each coordinate
for i in range(1):  # loop for days
    temp = []
    for j in range(1):  # loop for coordinates
        temp.append(get_data(coord[j], timestamp))

# adding headings to csv if not found
try:
    with open('data.csv', 'r') as f:
        pass
except:
    with open('data.csv', 'w') as f:
        f.write(
            'year,month,day,hour,zone,lon,lat,aqi,co,no,no2,o3,so2,nh3,pm2_5,pm10,temp,dewpt,condition')


# combining dataframes in that specified order
pd.concat(temp, axis=0).sort_index(kind='merge').to_csv(
    'data.csv', index=False, header=False, mode='a')

# writing updated timestamp to txt file
with open('timestamp.txt', 'w') as f:
    f.write(str(timestamp+86400))
