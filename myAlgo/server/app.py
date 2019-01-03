from flask import Flask
from flask import request
from flask_cors import CORS
from random import randint

app = Flask(__name__)
CORS(app)

# Tradier callback 
@app.route('/')
def get_auth_code():

    authcode = request.args.get('code', None)
    state = request.args.get('state', None)

    print(authcode)
    print(state)

    common_file = '../auth.txt'
    file = open(common_file, 'w+')

    json = '{\"auth_code\":'
    json = json+authcode+',\"state\":'+state+"}"

    print(json)

    file.write(json)

    return 'Thanks'

# this is necessary to listen on the public IP
#if __name__ == '__main__':
app.run(host='0.0.0.0')