# -*- coding: utf-8 -*-

import os
import io
import json
import re,random,string
import base64

from flask import Flask, request, abort, render_template, send_file
from flask_cors import CORS

app = Flask(__name__)
CORS(app)


@app.route('/')
def index1():
    return send_file('./show.html')
@app.route('/semantic.min.css')
def index2():
    return send_file('./semantic.min.css')
@app.route('/semantic.min.js')
def index3():
    return send_file('./semantic.min.js')

@app.route('/getsvg/', methods=['POST'])
def getsvg():
    t = request.form.get('t', '')
    s = request.form.get('s', '')
    if t != 'sam':
        abort(403)
    s=s[:255]
    s=''.join(filter(str.isalpha,s))
    s=s.lower()
    print(t,s)
    file_name = 'tmp_'+''.join(random.sample(string.ascii_letters, 8))
    ret = ''
    try:
        with open(file_name+'.in','w') as f:
            f.write(s+'\n')
        os.system('./gen < %s.in > %s.dot '%(file_name,file_name))
        os.system('dot -Tsvg %s.dot -o %s.svg'%(file_name,file_name))
        with open(file_name+'.svg','r') as f:
            ret = f.read()
    except BaseException:
        abort(403)
    finally:
        os.remove('%s.in'%file_name)
        os.remove('%s.dot'%file_name)
        os.remove('%s.svg'%file_name)
    return base64.b64encode(ret.encode('utf-8')).decode('utf-8')


if __name__ == '__main__':
    app.run('127.0.0.1', 12233)
