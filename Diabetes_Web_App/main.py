import numpy as np
from flask import Flask, request, render_template, url_for

import pickle

app = Flask(__name__)

model = pickle.load(open("modelSVM.pkl", "rb"))

@app.route("/")
def home():
    return render_template("home.html")

@app.route("/about")
def about():
    return render_template("about.html")

@app.route("/diabetes")
def diabetes():
    return render_template("Diabetes.html")

@app.route("/prediabetes")
def prediabetes():
    return render_template("Prediabetes.html")

@app.route('/predict',methods=['POST'])
def predict():
   if request.method == 'POST': 
    int_features = [int(x) for x in request.form.values()]
    final_features = [np.array(int_features)]
    prediction = model.predict(final_features)

    if prediction == 2:
        pred = "You have Diabetes, please consult a Doctor!"
    elif prediction == 1:
        pred = "You have a Pre-Dibaties!"
    elif prediction == 0:
        pred = "You don't have Diabetes!"
    
    output = pred
    
    return render_template('home.html', prediction_text=output)


if __name__ == "__main__":
    app.run(debug=True)
