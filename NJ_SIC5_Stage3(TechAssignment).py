"""
UNTUK BAGIAN MEMULAI SERVER!!
buru" banh jd gbsa ngetik banyak bagian sini..
yang pasti kodenya harusnya dah bener,
cmn suka post -1 errornya krna sinyal atau make hotspot..

"""
# Necessary Library
from datetime import datetime
import pandas as pd
import pytz as pz
from flask import Flask, request, jsonify

# Variables to contains some values
serverSET = Flask(__name__)
Alldata = {"Timestamp":[],"Temperatures":{"Celcius":[], "Kelvin":[]}, "Humidity":[]} #to keep the data

def forTempCalc(vl):
    return {"Cel": vl, "Kel":vl+372.15}
@serverSET.route("/")
def RootRoute_lol():
    return pd.DataFrame.from_dict(Alldata).to_html(), 200
@serverSET.route("/gsubmit", methods=["GET"])
def frm_sensor():
    tst = datetime.now(tz=pytz.timezone("Asia/Jakarta")).strftime("%d%m%Y : %H%M") //ga yakin ada bogor...
    temp=forTempCalc(request.args["temperature"])
    hum=request.args["humidity"]
    Alldata["Timestamp"].append(tst)
    Alldata["Temperatures"]["Celcius"].append(temp["Cel"])
    Alldata["Temperatures"]["Kelvin"].append(temp["Kel"])
    Alldata["Humidity"].append(hum)
    return jsonify({
        "timestamp":tst,
        "temperatures":{"Celcius":temp["Cel"],"Kelvin":temp["Kel"]},
        "humidity":hum
    })
@serverSET.route("/post", methods=["POST"])
def to_srvr():
    tst = datetime.now(tz=pytz.timezone("Asia/Jakarta")).strftime("%d%m%Y : %H%M")
    getDt=request.get_json()
    temp=forTempCalc(float(getDt["temperature"]))
    hum=float(getDt["humidity"])
    Alldata["Timestamp"].append(tst)
    Alldata["Temperatures"]["Celcius"].append(temp["Cel"])
    Alldata["Temperatures"]["Kelvin"].append(temp["Kel"])
    Alldata["Humidity"].append(hum)
    return jsonify({
        "timestamp":tst,
        "temperatures":{"Celcius":temp["Cel"],"Kelvin":temp["Kel"]},
        "humidity":hum
    })

if (__name__ == "__main__"):
    serverSET.run(host='0.0.0.0', port=5000, debug=True)