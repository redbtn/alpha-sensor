#root@orangepizerolts:~/alpha-sensor# cat dash.py 
from flask import Flask, render_template
import json

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/data')
def get_data():
    # Load data from your JSON source
    with open('data.json') as file:
        data = json.load(file)
    return data

if __name__ == '__main__':
    app.run(debug=True)