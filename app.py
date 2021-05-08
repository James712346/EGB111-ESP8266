from flask import Flask

app = Flask(__name__)

Motor1 = 0
Motor2 = 0


@app.route("/get/motor/1/")
def MotorGet1():
    return str(Motor1)

@app.route("/get/motor/2/")
def MotorGet2():
    return str(Motor2)

@app.route("/set/motor/1/", methods = ['POST'])
def MotorSet1():
    Motor1 = request.get_data()

@app.route("/set/motor/2/", methods = ['POST'])
def MotorSet2():
    Motor2 = request.get_data()

if __name__ == '__main__':
    app.run(host='0.0.0.0')
