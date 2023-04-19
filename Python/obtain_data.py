import requests
import json
import time
import requests
import csv
import _thread as thread
import keyboard

# Set the URL of the JSON file
micro_url = "http://192.168.88.124"

rows = []
csv_file = "non_distingued_data.csv"

# This function obtains a JSON from a error message 
# (because the wepbage is headerless, so it thinks that the header is actually the JSON from the webpage).

derrape = False

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
    
    l.append("DERRAPE") if derrape == True else l.append("NO_DERRAPE")
    write_to_csv(l)

def write_to_csv(line):
    with open(csv_file, "a", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(line)

def derrape(threadName):
    global derrape
    while(True):
        if keyboard.is_pressed('d'):
            derrape = True
        else:
            derrape = False

# Main programdd
thread.start_new_thread(derrape, tuple(["Segundo hilo"]))

while (True):
    data = get_json(micro_url)
    serialize_data(data)

    time.sleep(0.25)
