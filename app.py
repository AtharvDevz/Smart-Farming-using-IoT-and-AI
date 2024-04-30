# -*- coding: utf-8 -*-
import uvicorn
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from farm_sensor_data import farm_data
import json
from dotenv import load_dotenv

load_dotenv()  ## load all the environment variables

import os
import google.generativeai as genai

genai.configure(api_key=os.getenv("GOOGLE_API_KEY"))


def get_gemini_repsonse(input, prompt):
    model = genai.GenerativeModel('gemini-pro')
    response = model.generate_content([input, prompt])
    return response.text

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins    = ["*"],
    allow_credentials = True,
    allow_methods = ["*"],
    allow_headers = ["*"]
)
@app.get('/')
def index():
    return {'message': 'Hello, World'}

# @app.get('/{name}')
# def get_name(name: str):
#     return {'Welcome To Server' : f'{name}'}

@app.get('/data')
def get_data():
    print("Inside /data")
    import gspread
    gc = gspread.service_account(filename='farmmonitoring-5b63e966216f.json')
    wks = gc.open("Farm_Monitoring").sheet1
    all_values = wks.get_all_values()

    column_values = wks.row_values(1)
    print("Column Name : ", column_values)
    last_row = all_values[-1]
    dict1 = {}
    for i in range(0, len(last_row)):
        dict1[column_values[i]] = last_row[i]
    last_row = all_values[-1]

    print("Last row of data:", last_row)
    print("Execution Complete")
    return { "data": dict1}



@app.post('/analyze/{crop_name}')
def generate_response(crop_name: str, data:farm_data):
    print("data + ", data)
    data_dict = data.dict(by_alias=True)
    print("data_dict : ", data_dict)
    Date = data_dict["Date"]
    Time = data_dict["Time"]
    temp = data_dict["temp"]
    hum = data_dict["hum"]
    moisture = data_dict["moisture"]
    air_quality = data_dict["air_quality"]
    voc = data_dict["voc"]


    input_prompt = """
        As a Senior Farmer and Environmental Scientist, I have been provided with some data pertaining to the environment of a particular crop. The data includes information such as date, time, temperature, humidity, moisture, air quality (measured through MQ135 sensor), and volatile organic component (ppm). My task is to analyze this data and determine whether the environment is suitable for the particular crop, as well as provide tips on how to take care of the crop. If possible, I am also expected to suggest suitable fertilizers.

        To ensure clarity and ease of understanding, I will present my analysis in bullet points and in plain text

    """

    data = str([Date, Time , temp, hum, moisture, air_quality, voc])
    input = input_prompt + crop_name + data

    response = get_gemini_repsonse(input_prompt, input)
    print("Response is : ")
    print(response)

    return {
        'response': response
    }


if __name__ == '__main__':
    uvicorn.run(app, host='localhost', port=3002)
#uvicorn app:app --reload