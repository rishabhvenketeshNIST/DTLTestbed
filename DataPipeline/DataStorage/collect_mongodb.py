import pymongo
import xml.dom.minidom
import datetime
from collect import *

def getDevice(file):
        deviceStream = file.getElementsByTagName("DeviceStream")[0] #gets the header element of the XML
        device = deviceStream.getAttribute("name") #gets device name
        return device

class Uploader():
    def __init__(self, url = ""):
        #initialize dictionaries
        self.dict = {} #dictionary containing data values from xml
        client = pymongo.MongoClient("mongodb://localhost:27017/")
        #client = pymongo.MongoClient("mongodb+srv://michael:1234@cluster0.4jvidg2.mongodb.net/?retryWrites=true&w=majority")
        db = client["DTL"]
        self.ur = db["UR_data"] #connect to MongoDB collection
        print("Connected to MongoDB")
        self.url = url

    #recursive method to traverse XML file and retrieve pertinent data values
    #Uses xml.dom.minidom to traverse XML document as a node tree
    def output(self, node, num, deviceName = ""):
        children = node.childNodes #create list of children nodes of node
        if children.length == 0: #if node has no children
            return 1,node.nodeValue #return 1 and the value at the node to indicate node is a leaf node
        if node.nodeName == "DeviceStream":
            deviceName = node.getAttribute("name")
            if deviceName == "Agent": #ignore all data items under the "Agent" device stream
                return 0,0
        for child in children: #if node has children then traverse through all the children
            a, val = self.output(child, 0, deviceName) #recursive function to look at each child node
            if val == None: #if  the child node has no value then  skip it
                pass
            elif '\n  ' in str(val): #if the child nodes value is null then skip it
                pass
            elif a == 1: #if the child node is a leaf node then publish the node
                self.publish(node, str(val), deviceName)
            else: #any other conditions then skip it
                pass
        return 0,0 #return 0,0 to signifiy that node has already been traverse and because the node is not a leaf node and

    #method to update dictionary with value of specific leaf node
    def publish(self, node, val, deviceName):
        timestamp = node.getAttribute("timestamp") # retrieve timestamp
        if not timestamp:
            return
        dataItemId = node.getAttribute("dataItemId") # retrieve data tag
        val = val.replace(' ',',') # in cases such as coordinates where entry is two or more values separated by spaces, replace spaces with commas
        # the above is done to deal with issues writing dictionary to csv
        try: 
            val = float(val) 
            if val.is_integer():
                val = int(val)
            else:
                pass
        except ValueError: #if there is a value error, that means val is a string, so cast it to a string
            val = str(val) 

        timestamp = datetime.datetime.strptime(timestamp, "%Y-%m-%dT%H:%M:%S.%fZ")

        if deviceName not in self.dict.keys(): #if there is a new device, update dictionary with a new key "deviceName"
            entry = {deviceName: {timestamp: {dataItemId: val}}}
            self.dict.update(entry)
        elif timestamp not in self.dict[deviceName].keys(): # if a new timestamp is found, then create an entry with the key being the timestamp in dict
            entry = {timestamp: {dataItemId: val}}
            self.dict[deviceName].update(entry) # update entry
        else: # if it is an existing timestamp or data attribute then update dict
            if dataItemId not in self.dict[deviceName][timestamp].keys():
                entry = {dataItemId: val}
                self.dict[deviceName][timestamp].update(entry)
            else:
                pass

    def parse(self, file):
        doc = xml.dom.minidom.parseString(file) 
        a,b = self.output(doc, 0) #call recursive function on XML file, which will parse it and put contents in dictionary

        for deviceName in self.dict.keys(): #loop through entire dictionary
            timestamp_dict = self.dict[deviceName] 
            for timestamp in timestamp_dict.keys(): 
                dataItem_dict = timestamp_dict[timestamp]
                self.ur.update_one({"timestamp": timestamp, "device": deviceName}, {"$set": dataItem_dict}, upsert = True) #update the database with data items

        #for key in self.dict.keys():
            #temp_dict = self.dict[key]
            #self.ur.update_one({"timestamp": key}, {"$set": temp_dict}, upsert=True) 

    def run(self):
        x = input("Enter batch size: ") #asks user for batch size
        count = 1
        next = 1

        while True: #continues looping until desired number of batches are completed
            self.dict = {}
            #url = self.url
            #url = f"http://mtconnect.mazakcorp.com:5610/sample?from={next}&count={x}" #URL for sample GET request, starting from "next" sequence number and getting "x" data items
            url = f"http://localhost:5000/sample?from={next}&count={x}"
            file = getXML(url) #gets response XML
            print(count)
            print(url)

            empty = checkEmpty(file) #checks if the response XML has any new data items
            if empty: #if it has none, then break from the loop
                print("Empty response file, waiting 10 seconds")
                time.sleep(10)
                continue

            self.parse(file)
        
            next = nextSequence(file) #gets nextSequence, which will be the starting point for the next GET sample request
            count += 1

if __name__ == "__main__":
    uploader = Uploader()
    uploader.run()
