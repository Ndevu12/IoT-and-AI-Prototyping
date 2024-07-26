from fastapi import FastAPI
import uvicorn
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import torch
from chronos import ChronosPipeline

pipeline = ChronosPipeline.from_pretrained(
  "amazon/chronos-t5-small",
  device_map="cpu",
  torch_dtype=torch.bfloat16,
)

df = pd.read_csv("https://raw.githubusercontent.com/AileenNielsen/TimeSeriesAnalysisWithPython/master/data/AirPassengers.csv")

app = FastAPI()

@app.get('/forecast/{period}')
def forecast(period: int):
    context = torch.tensor(df["#Passengers"])
    prediction_length = period
    forecast = pipeline.predict(context, prediction_length)
    return {"forecast": f"{forecast[0].numpy()}"}

if __name__ == '__main__':
    uvicorn.run(app, host='0.0.0.0', port=80)