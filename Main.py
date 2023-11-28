import serial
import time
import requests

stocks = ["TSLA", "AAPL", "GOOGL", "AMZN"]

rapidapi_key = "2c11aa8cbfmsh45d9f90ade82cf7p117a23jsn685c93c622e5"
rapidapi_host = "realstonks.p.rapidapi.com"

# Open the serial port (change 'COM3' to your Arduino's port)
ser = serial.Serial('/dev/cu.usbmodem14101', 9600, timeout=1)

# Wait for the Arduino to initialize
time.sleep(2)

for i in range (4):
    for stock_symbol in stocks:
        url = f"https://realstonks.p.rapidapi.com/{stock_symbol}"

        headers = {
            "X-RapidAPI-Key": rapidapi_key,
            "X-RapidAPI-Host": rapidapi_host
        }

        response = requests.get(url, headers=headers)

        if response.status_code == 200:
            data = response.json()
            price = data.get('price')
            change = data.get('change_percentage')
            message = stock_symbol + ":   CHANGE:,"+ str(price) + "   " + str(change) + "%"
            print(message)
            ser.write(message.encode())
            #print("Data:", data)
        else:
            print(f"Failed to fetch data for {stock_symbol}. Status code: {response.status_code}")
        time.sleep(2)

ser.close()
