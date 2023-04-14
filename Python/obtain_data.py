import requests
import json
import time
import requests

# Set the URL of the JSON file
micro_url = "http://192.168.106.124"
serv_url = 'http://127.0.0.1:8000/guardar_estado_boton/'

data = {
    'estado_boton': 'presionado'
}

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

def get_server_data(url):
    response = requests.get(url)
    print(response.text)  # imprime el contenido de la respuesta
    data = response.json()
    estado_boton = data['estado_boton']
    print(f'El estado actual del botón es: {estado_boton}')

# Main program
while (True):
    #data = get_json(micro_url)
    #serialize_data(data)

    get_server_data(serv_url)

    time.sleep(0.25)
