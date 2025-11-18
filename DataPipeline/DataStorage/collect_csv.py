import requests
import time
import xml.dom.minidom
from xml_parse import XMLParser

def firstSequence(file): #gets the firstSequence from MTConnect Agent response XML
    doc = xml.dom.minidom.parseString(file) 
    header = doc.getElementsByTagName("Header")[0] #gets the header element of the XML
    firstSequence = header.getAttribute("firstSequence") #gets the firstSequence attribute of the header element
    return firstSequence

def nextSequence(file): #gets the nextSequence from MTConnect Agent response XML
    doc = xml.dom.minidom.parseString(file)
    header = doc.getElementsByTagName("Header")[0] #gets the header element of the XML
    nextSequence = header.getAttribute("nextSequence") #gets the nextSequence attribute
    return nextSequence

def lastSequence(file): #gets the nextSequence from MTConnect Agent response XML
    doc = xml.dom.minidom.parseString(file)
    header = doc.getElementsByTagName("Header")[0] #gets the header element of the XML
    lastSequence = header.getAttribute("lastSequence") #gets the nextSequence attribute
    return lastSequence

def checkEmpty(file): #checks if MTConnect Agent response XML has any new data
    doc = xml.dom.minidom.parseString(file)
    stream = doc.getElementsByTagName("Streams")[0] #gets Streams element of the XML
    children = stream.childNodes #gets children of the Streams element
    if children.length == 0: #checks if it has any children
        return True #return True for the Streams being empty
    else:
        return False #return False for the Streams not being empty

def getXML(url): #gets MTConnect response XML
    while True:
        try:
            response = requests.get(url)
            break
        except Exception as ex:
            print ("Exception:", ex)
            time.sleep(3)
            continue
    file = response.text #gets responseXML as a string
    '''
    file_path = f"doc{count}.txt"
    with open(file_path, 'w') as f:
        f.write(file)
    '''
    return file


class DataCollector:
    def __init__(self): #starts collecting data when run
        self.run()

    def run(self): #start collecting data and storing it in a csv file
        batch_size = input("Enter batch size: ") #asks user for batch size
        count = 0
        current = 1 #current sequence number to collect data from
        parser = XMLParser() #initialize XML parser, which parses MTConnect XML and stores data in data.csv

        while True: #continues looping until desired number of batches are completed
            prev_last = 0
            url = f"http://localhost:5000/sample?from={current}&count={batch_size}" #URL for sample GET request, starting from "current" sequence number and getting "batch_size" data items
            #url = f"http://mtconnect.mazakcorp.com:5610/sample?from={next}&count={x}"
            print(url)

            while True: #loops until there are x new data items to query
                temp_url = "http://localhost:5000/current" 
                #url = "http://mtconnect.mazakcorp.com:5610/current"
                file = requests.get(temp_url).text #makes current request to agent
                current_last = int(lastSequence(file)) #stores current "lastSequence", which is how many total data items there are in the Agent
                if current_last == prev_last: #if the current number of data items is equal to the number 10 seconds ago, then no data is being sent to the Agent
                    print("No data being sent to Agent")
                    leave = input("Do you want to exit this program? (y/n)")
                    if leave == "y":
                        exit()
                if (current_last - int(current)) >= int(batch_size): #checks if there new data items equal "batch_size"
                    break #if so, break from the loop
                print("Not enough data yet, waiting 10 seconds")
                time.sleep(10) #if there aren't x new data items, then sleep 10 seconds and check again
                prev_last = current_last 

            file = getXML(url) #gets response XML

            #empty = checkEmpty(file) #checks if the response XML has any new data items
            #if empty: #if it has none, then break from the loop
            #    print("Ended: no more data")
            #    break

            parser.parse(file) #parse the XML and add it to the CSV file
            from_seq = nextSequence(file) #gets nextSequence, which will be the starting point for the next sample request
            count += 1

if __name__ == "__main__":
    data_collector = DataCollector() #initializes data collector
