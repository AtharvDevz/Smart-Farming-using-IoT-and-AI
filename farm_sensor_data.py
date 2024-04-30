from pydantic import BaseModel

class farm_data(BaseModel):
    Date: str
    Time: str
    temp: float
    hum: float
    moisture: float
    air_quality: float
    voc: float


