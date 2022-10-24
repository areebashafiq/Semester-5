# creating a list of all the coordinates
from csv import writer
from time import sleep
import requests
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


def get_curr(coord):
    url = f"https://api.openweathermap.org/data/2.5/air_pollution?lat={coord[0]}&lon={coord[1]}&appid=76f1fd8bb14ed19ba904204c58746675"
    r = requests.get(url=url)
    return r.json()


def params(data, index):
    # a function that returns a list of parameters against a given json
    dt = data['list'][0]['dt']
    aqi = data['list'][0]['main']['aqi']
    co = data['list'][0]['components']['co']
    no = data['list'][0]['components']['no']
    no2 = data['list'][0]['components']['no2']
    o3 = data['list'][0]['components']['o3']
    so2 = data['list'][0]['components']['so2']
    pm2_5 = data['list'][0]['components']['pm2_5']
    pm10 = data['list'][0]['components']['pm10']
    nh3 = data['list'][0]['components']['nh3']

    return [dt, index, aqi, co, no, no2, o3, so2, nh3, pm2_5, pm10]


for i in range(10):
    with open('data.csv', 'a') as f_object:
        writer_object = writer(f_object)
        for i in coord:
            writer_object.writerow(params(get_curr(i[1]), i[0]))
            sleep(1)
        f_object.close()
