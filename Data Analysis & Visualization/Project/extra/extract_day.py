# This script extracts data by day and stores it into an excel file

# creating a list of all the coordinates
import pandas as pd
import requests
from datetime import datetime
from time import sleep


def make_coord():
    """
    This function returns a list of coordinates in the form of [index, [lat, lon]]
    """
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


def utc2time(ts):
    """
    This function converts a timestamp to an array of time
    """
    ts += 18000
    year = int(datetime.utcfromtimestamp(ts).strftime('%Y'))
    month = int(datetime.utcfromtimestamp(ts).strftime('%m'))
    day = int(datetime.utcfromtimestamp(ts).strftime('%d'))
    hour = int(datetime.utcfromtimestamp(ts).strftime('%H'))
    return [int(year), int(month), day, hour]


def params(data, hour, index):
    """
    This function returns the parameters for a given hour
    """
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

    return [temp[0], temp[1], temp[2], temp[3], index, aqi, co, no, no2, o3, so2, nh3, pm2_5, pm10]


def api_request(coord, time):
    """
    This function returns the data for a given coordinate for a whole day
    """

    sleep(1)  # for calling one request per second

    url = f"https://api.openweathermap.org/data/2.5/air_pollution/history?lat={coord[0]}&lon={coord[1]}&start={time}&end={time+82800}&appid=8d9efe95caf3922348a458d615abeb8c"
    r = requests.get(url=url)
    return r.json()


def extract_vals(temp, index):
    data = []
    for i in range(len(temp['list'])):
        data.append(params(temp, i, index))
    return data


def get_data_by_zone(hour, time):
    coord = make_coord()
    df = pd.DataFrame(extract_vals(api_request(coord[hour][1], time), coord[hour][0]), columns=[
                      'year', 'month', 'day', 'hour', 'index', 'aqi', 'co', 'no', 'no2', 'o3', 'so2', 'nh3', 'pm2_5', 'pm10'])
    return df


def get_day(time):
    temp = []
    for i in range(90):
        temp.append(get_data_by_zone(i, time))

    pd.concat(temp, axis=0).sort_index(kind='merge').to_csv(
        'data.csv', index=False, header=False, mode='a')


time_stamp = 1609441200  # for 1st jan 2021
for i in range(365):
    get_day(time_stamp)
    time_stamp += 86400
