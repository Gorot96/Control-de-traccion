import requests
import json
import time
import requests
import csv

# Set the URL of the JSON file
micro_url = "http://192.168.88.124"

csv_file = "non_distingued_data.csv"

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
    l = []
    for o in json.values():
        l.append(o)
    
    write_to_csv(l)

def write_to_csv(line):
    with open(csv_file, "a", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(line)

# Main program
while (True):
    data = get_json(micro_url)
    serialize_data(data)

    time.sleep(0.25)
