import serial
import csv

ser = serial.Serial('/dev/ttyACM0', 9600) # Open serial port at 9600 baud rate
with open('sensor_data.csv', 'w', newline='') as csvfile: # Open CSV file for writing
    writer = csv.writer(csvfile)
    while True:
        line = ser.readline().decode('utf-8').strip() # Read serial data and convert to string
        sensorValue = int(line) # Convert string to integer
        writer.writerow([sensorValue]) # Write sensor value to CSV file
