from flask import Flask, request, render_template
from flask_cors import CORS
app = Flask(__name__)
CORS(app)

Motor1 = 0
Motor2 = 0
Motor3 = 0


@app.route("/")
def main():
    return render_template('index.html')


@app.route("/get/motor/1/")
def MotorGet1():
    return str(Motor1)


@app.route("/get/motor/2/")
def MotorGet2():
    return str(Motor2)

@app.route("/get/motor/3/")
def MotorGet2():
    return str(Motor3)


@app.route("/set/motor/1/", methods=['POST'])
def MotorSet1():
    global Motor1
    print(request.get_data())
    Motor1 = int(request.get_data())
    return str(Motor1)


@app.route("/set/motor/2/", methods=['POST'])
def MotorSet2():
    global Motor2
    print(request.get_data())
    Motor2 = int(request.get_data())
    return str(Motor2)

@app.route("/set/motor/3/", methods=['POST'])
def MotorSet3():
    global Motor3
    print(request.get_data())
    Motor3 = int(request.get_data())
    return str(Motor3)


if __name__ == '__main__':
    app.run(host='0.0.0.0')
