import requests
import json
import csv
import re

# Set the URL of the JSON file
url = "http://192.168.106.124"

try:
    response = requests.get(url).text
except Exception as e:
    res = str(e)

# Define a regular expression pattern to match the JSON data
pattern = r"{{.+}}"

# Find all occurrences of the pattern in the string
match = re.findall(pattern, res)

# Print the JSON data, if available
if len(match) > 0:
    print(match[0][1:-1])
else:
    print("No JSON data found")
