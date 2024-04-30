
console.log("Hello");
obj1 = {
    response:
        "**Environmental Analysis for Potato Crop**\n\n* **Temperature:** The ideal temperature range for potato crops is between 55-70°F (13-21°C). The provided data shows a temperature of 35°F, which is below the optimum range. This low temperature may hinder crop growth and development.\n\n* **Humidity:** Potatoes prefer moderate to high humidity levels (70-85%). The data indicates a humidity level of 30%, which is low and may lead to water stress and reduce crop yield.\n\n* **Moisture:** Potato crops require consistent moisture levels, especially during the tuber development stage. The data does not provide information on moisture levels, so it's difficult to assess this factor.\n\n* **Air Quality:** The MQ135 sensor reading of 0.0 indicates good air quality. This is favorable for potato crops, as poor air quality can harm plant health and reduce growth.\n\n* **Volatile Organic Compounds (VOCs):** The VOC reading of -100.0 ppm is below detectable levels. This is within the acceptable range for potato crops, as high VOC levels can indicate plant stress or disease.\n\n**Care Tips and Fertilizer Recommendations**\n\n* **Temperature:** Protect the crop from cold temperatures by providing frost protection such as row covers or mulching.\n* **Humidity:** Increase humidity levels by misting the foliage regularly or installing a humidifier in the growing area.\n* **Moisture:** Monitor soil moisture levels and water regularly, especially during hot and dry periods.\n* **Air Quality:** Maintain good air circulation by providing adequate ventilation or using fans.\n* **Fertilizers:** Potatoes benefit from a balanced fertilizer high in nitrogen, phosphorus, and potassium. Organic fertilizers such as compost or manure can also provide beneficial nutrients.",
};

document.getElementById("analyze-btn").addEventListener("click", () => {
    getResponse();
});

async function getResponse() {
    console.log("Inside Get-Analyze Function")
    let response = await fetch('http://127.0.0.1:8000/data');
    const farmData = await response.json()

    let a = Object.values(farmData["data"])
    const expectedStructureData = {
        Date: a[0],
        Time: a[1],
        temp: a[2],
        hum: a[3],
        moisture: a[4],
        air_quality: a[5],
        voc: a[6]
    };
    console.log("Atharv")
    console.log(expectedStructureData)
    const options = {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'  // Specify JSON content
        },
        body: JSON.stringify(expectedStructureData)  // Convert data to JSON string
    };
    let crop = document.getElementById("crop_name").value;
    try {
        const response = await fetch(`http://127.0.0.1:8000/analyze/${crop}`, options);
        if (!response.ok) {
            // throw new Error(`Error sending POST request: ${response.statusText}`);
        }
        var responseData = await response.json();
        console.log("Response:", responseData);
        console.log("analysis = ", responseData)
        string = responseData["response"];
        console.log(string)
        string = string.replaceAll("*", "");
        string = string.replaceAll("\n", "<br>");
        console.log(string);
        list1 = string.split("\n");
        console.log("Execution Complete");
        let responseBox = document.getElementById("response");
        responseBox.innerHTML = "Response is "
        responseBox.innerHTML = responseBox.innerHTML +
            `<h1>${crop}</h1><br>` + `${string}`;
    } catch (error) {
        console.error("Error sending POST request:", error);
        // return null; // Return null or an error object to indicate failure
    }
}

async function getData() {
    fetch('http://127.0.0.1:8000/data')
        .then(response => response.json())  // Parse JSON response
        .then(data => {
            var extractedData = data.data;  // Access data within the "data" key
            console.log(extractedData);  // Use extractedData here
            let sensorData = Object.entries(extractedData)
            console.log(sensorData)
            sensorName = [
                "Date",
                "Time",
                "Temperature",
                "Humidity",
                "Moisture",
                "Air Quality",
                "Voc(ppm)",
            ];
            sensorUnit = [
                "4/18/2024",
                "16:03:51",
                "°C",
                "g/m3",
                "%",
                "aqi",
                "ppm",
            ];

            let dashboard = document.querySelector(".dashboard ul");

            for (let i = 2; i < sensorName.length; i++) {
                dashboard.innerHTML =
                    dashboard.innerHTML +
                    `
          <li>
          <div class="widget">
                <div class="sensor-name">
                  ${sensorName[i]}
                </div>
                <div class="sensor-value">
                  ${sensorData[i][1]}
                </div>
                <div class="sensor-unit">
                  ${sensorUnit[i]}
                </div>
          </div>
          </li>
          `;
            }
        })
        .catch(error => console.error(error));

}

getData();