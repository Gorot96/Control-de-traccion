import requests
import json
import time

# Set the URL of the JSON file
url = "http://192.168.106.124"

def get_data():
    try:
        response = requests.get(url).text
    except Exception as e:
        res = str(e)

    parts = res.split('###')

    jsonstring = str(parts[1][:-3]).strip()

    objectjson = json.loads(jsonstring)

    for o in objectjson.values():
        for p in o.values():
            print(p)

while (True):
    get_data()
    time.sleep(0.25)
