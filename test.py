### Disease Detection APP
from dotenv import load_dotenv

load_dotenv()  ## load all the environment variables

import os
import google.generativeai as genai

genai.configure(api_key=os.getenv("GOOGLE_API_KEY"))


def get_gemini_repsonse(input, prompt):
    model = genai.GenerativeModel('gemini-pro')
    response = model.generate_content([input, prompt])
    return response.text


##initialize our streamlit app

crop_name = input("Enter crop Name : ")

choice = int(input("Enter choice : "))
input_prompt = """
    As a Senior Farmer and Environmental Scientist, I have been provided with some data pertaining to the environment of a particular crop. The data includes information such as date, time, temperature, humidity, moisture, air quality (measured through MQ135 sensor), and volatile organic component (ppm). My task is to analyze this data and determine whether the environment is suitable for the particular crop, as well as provide tips on how to take care of the crop. If possible, I am also expected to suggest suitable fertilizers. To ensure clarity and ease of understanding, I will present my analysis in bullet points and tabular form, plain text

"""

data = str(['4/18/2024', '16:03:51', '35', '30', '88', '0', '-100'])
input = input_prompt + crop_name + data
## If submit button is clicked

if choice == 1:
    response = get_gemini_repsonse(input_prompt, input)
    print("Response is : ")
    print(response)

