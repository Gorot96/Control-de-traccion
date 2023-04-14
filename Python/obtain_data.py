import requests
import json
import time

# Set the URL of the JSON file
micro_url = "http://192.168.106.124"

# This function obtains a JSON from a error message 
# (because the wepbage is headerless, so it thinks that the header is actually the JSON from the webpage).
def get_json(url):
    try:
        response = requests.get(url).text
    except Exception as e:
        res = str(e)

    parts = res.split('###')

    jsonstring = str(parts[1][:-3]).strip()

    objectjson = json.loads(jsonstring)

    return objectjson    

# Uses a dictionary to treat the data
def serialize_data(json):
    for o in json.values():
        for p in o.values():
            print(p)

# Main program
while (True):
    data = get_json(micro_url)
    serialize_data(data)

    time.sleep(0.25)
