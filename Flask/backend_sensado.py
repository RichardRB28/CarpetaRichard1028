from flask import Flask, request
from flask_restful import Resource, Api
from db_action import get_all_data, save_data
app = Flask(__name__)
api = Api(app)

@app.route('/data') #encuentra en esa ruta y el decorador
def get_data():
    response= get_all_data()
    return({'data': response})

@app.route('/save',methods=['POST'])
def put_data(): 
    resp=save_data(request.json)
    return({'data':'ok'})



if __name__ == '__main__':
    app.run(debug=True)