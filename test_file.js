// Online Javascript Editor for free
// Write, Edit and Run your Javascript code using JS Online Compiler

console.log("Try programiz.pro");

obj1 = {
    response:
    "**Environmental Data Analysis and Crop Care**\n\n**Crop:** Fenugreek\n\n**Data:**\n\n| Date | Time | Temperature (°C) | Humidity (%) | Moisture (%) | Air Quality (MQ135) | VOCs (ppm) |\n|---|---|---|---|---|---|---|\n| N/A | N/A | 35.0 | 30.0 | 88.0 | 0.0 | -100.0 |\n\n**Analysis:**\n\n* Temperature is within the optimal range for fenugreek growth (20-35°C).\n* Humidity is slightly low for optimal growth, but should not significantly affect the crop.\n* Soil moisture is adequate.\n* Air quality is good.\n* VOC levels are within acceptable limits.\n\n**Crop Care Tips:**\n\n* Water the crop regularly to maintain soil moisture.\n* Monitor temperature and humidity levels to ensure they stay within the optimal range.\n* Provide adequate sunlight.\n* Fertilize the crop with a balanced fertilizer formulated for fenugreek.\n* Inspect the crop regularly for pests and diseases.\n\n**Suitable Fertilizers:**\n\n* Organic fertilizers: Compost, manure\n* Chemical fertilizers: 10-10-10 NPK fertilizer\n\n**Overall, the environmental conditions are suitable for fenugreek growth. By following the above crop care tips, farmers can optimize their yield and ensure the health of their crop.**",
};

console.log(obj1["response"]);

string = obj1["response"];
string = string.trim("*");
console.log(obj1["response"]);
list1 = string.split("\n");

console.log(list1);

for (const key in list1) {
    console.log
}
console.log("Execution Complete");
