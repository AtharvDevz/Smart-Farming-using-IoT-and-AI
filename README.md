# Smart Farming using IoT and AI

This project is an innovative Internet of Things (IoT) and Artificial Intelligence (AI) system designed to optimize plant care by providing real-time environmental monitoring and AI-powered recommendations.

Key Features:

* Sensor Data Collection: Utilizes NodeMCU ESP32 to collect crucial environmental data, including:
    * Air Quality (MQ-135 sensor)
    * Soil Moisture (Soil Moisture Sensor)
    * Temperature & Humidity (DHT11 sensor)
* Data Transmission: Efficiently transmits sensor readings through HTTP requests.
* FastAPI Backend: Leverages the FastAPI framework for robust data processing, communication with the user interface, and future integration of an AI model.
* Database Storage: Using Google Sheets for easier Operations can use any other database
* User-Friendly Interface: Developed with HTML, CSS, and JavaScript, delivering real-time data visualization through charts and graphs. Additionally, it offers a user-friendly chat interface for interaction with the AI component.
* Current AI Integration: Provides a chat interface where users can interact with me (Gemini) for initial plant-specific care advice based on sensor data.
* Future AI Integration: The architecture is designed to seamlessly integrate a trained AI model in the backend for more sophisticated plant care recommendations based on sensor readings and plant type.

Benefits:

* Real-time Insights: Gain immediate understanding of your plant's environment.
* Data-Driven Decisions: Optimize plant care with actionable recommendations from the AI model (future).
* Improved Plant Health: Foster thriving plants through informed care practices.
* Scalable Architecture: The system is designed to grow with your needs, accommodating more sensors and users.

Getting Started

1. NodeMCU Connection and Code
   * Connection is Availible in the images Folder and the Board Code is in board_code Folder
2.  Prerequisites
    * FastAPI installed on your system. run Command (pip install fastapi and pip install uvicorn)
      Run Commands
      
      ```bash
      pip install uvicorn
      pip install fastapi

    * A basic understanding of Python, FastAPI, HTML, CSS, and JavaScript.
    * Download the Required JSON File of Credential and API Key from Your Google Cloud Account
    * Add Gemini API Key in .env File
4. Clone the Repository:

   ```bash
   git clone https://github.com/Atharv/Smart-Farming-using-IoT-and-AI.git
   ```
   
5. Set Up Database
   - Create Google sheet Script code to add the data in file through HTTP Get Request. (In the File GSScript.txt)
   - Configure your database connection details in the backend code.
   - Install gsspread module

     ```bash
     pip install gs-spread
        
5. Run the Server:
   
   ```bash
   uvicorn app:app --reload
   
6. Access the User Interface
   Open http://localhost:8000 (or your specified port) in a web browser.

Future Development:

* Implement a trained AI model in the backend for plant-specific care recommendations.
* Explore options for mobile app development for convenient remote monitoring.
* Integrate additional sensors to provide even more comprehensive environmental data.

Contributing

We welcome contributions to this project! Please feel free to fork the repository, make changes, and submit pull requests.
