from flask import Flask, render_template, request, jsonify, session, make_response
from database import user_get, train_get, clean, ticket_operate, ticket_info, ticket_get, minit
from . import cus
import os


@cus.route("/")
def to_home():
    return home_page()

@cus.route('/home')
def home_page():
    u_uid = request.cookies.get("uid")
    p_uid = session.get("uid")
    if p_uid != None and p_uid != u_uid:
        session.pop("uid", None)
    tmp = user_get()
    try:
        tmp.find(int(session.get("uid")))
    except:
        tmp.find(1)
    return render_template('home.html', page="home", user_info=tmp)

@cus.route('/search', methods = ['get'])
def search_page():
    u_uid = request.cookies.get("uid")
    p_uid = session.get("uid")
    if p_uid != None and p_uid != u_uid:
        session.pop("uid", None)
    tmp = user_get()
    try:
        tmp.find(int(session.get("uid")))
    except:
        tmp.find(1)
    return render_template('search.html', page="search", user_info=tmp)

@cus.route('/login', methods = ['get'])
def user_page():
    u_uid = request.cookies.get("uid")
    p_uid = session.get("uid")
    if p_uid != None and p_uid != u_uid:
        session.pop("uid", None)
    tmp = user_get()
    try:
        tmp.find(int(session.get("uid")))
    except:
        tmp.find(1)
    return render_template('user.html', page="login", user_info=tmp)

@cus.route('/chp', methods = ['get'])
def chp_page():
    u_uid = request.cookies.get("uid")
    p_uid = session.get("uid")
    if p_uid != None and p_uid != u_uid:
        session.pop("uid", None)
    tmp = user_get()
    try:
        tmp.find(int(session.get("uid")))
    except:
        tmp.find(1)
    return render_template('chp.html', page="login", user_info=tmp)
    
@cus.route('/order', methods = ['get'])
def ord_page():
    u_uid = request.cookies.get("uid")
    p_uid = session.get("uid")
    if p_uid != None and p_uid != u_uid:
        session.pop("uid", None)
    tmp = user_get()
    try:
        tmp.find(int(session.get("uid")))
    except:
        tmp.find(1)
    return render_template('order.html', page="login", user_info=tmp)

@cus.route("/register", methods= ['post'])
def regis():
    u_uid = request.cookies.get("uid")
    p_uid = session.get("uid")
    if p_uid != None and p_uid != u_uid:
        session.pop("uid", None)
    tmp = user_get()
    try:
        tmp.find(int(session.get("uid")))
    except:
        tmp.find(1)
    tmp = user_get()
    if tmp.find_by_email(request.form['email']):
        return jsonify({'result': 0, 'message': '邮箱已注册'})
    tmp.email = request.form['email']
    tmp.name = request.form['name']
    tmp.password = request.form['password']
    tmp.phone = request.form['phone']
    tmp.add_user()
    tmp.find_by_email(request.form['email'])
    return jsonify({'result': 1, 'message': tmp.uid})

kind_tag_list = {'D': 'D-动车', 'G': 'G-高铁', 'C': 'C-城际高铁', 'O': 'O-普速', 'K': 'K-快速', 'T': 'T-特快', 'Z': 'Z-直达特快'}
seat_name_list = ['无座', '二等座', '一等座', '商务/特等', '动卧', '高级软卧', '软座', '硬座', '软卧', '硬卧'] 

@cus.route("/search", methods = ['post'])
def search():
    tmp = ticket_get()
    tmp.loc1 = request.form['loc1']
    tmp.loc2 = request.form['loc2']
    tmp.date = request.form['date']
    print(tmp.date)
    tmp.catalog = "LCDGKOTZ"
    tmp.query_ticket()
    rsp = []
    for ite in tmp.result:
        tmp_rsp = {}
        tmp_train = train_get()
        tmp_train.find(ite.train_id)
        tmp_rsp['kind'] = tmp_train.catalog
        tmp_rsp['train_id'] = tmp_train.train_id
        tmp_rsp['kind_tag'] = kind_tag_list[tmp_train.catalog]
        tmp_rsp['name'] = tmp_train.name.split('(')[0]
        tmp_rsp['date'] = ite.date1
        tmp_rsp['dep'] = ite.loc1
        tmp_rsp['des'] = ite.loc2
        tmp_rsp['dep_time'] = ite.time1
        tmp_rsp['des_time'] = ite.time2
        tmp_rsp['seat_name'] = []
        for t in seat_name_list:
            tmp_rsp['seat_name'].cusend(t)
        tmp_rsp['station'] = tmp_train.station_name
        tmp_rsp['arr_time'] = tmp_train.arriv_time
        tmp_rsp['arr_time'][0] = tmp_train.start_time[0]
        tmp_rsp['stan_time'] = []
        tmp_rsp['price'] = []
        tmp_rsp['remain'] = []
        for so_t in tmp_train.stopover_time:
            tmp_rsp['stan_time'].cusend(so_t.split(':')[1] + '分')
        tmp_rsp['stan_time'][0] = '发车'
        tmp_rsp['stan_time'][len(tmp_rsp['stan_time']) - 1] = '到达'
        for seat in seat_name_list:
            tmp_rsp['price'].cusend('--')
            tmp_rsp['remain'].cusend(-1)
        tmp_ind = 0
        for seat in ite.ticket_name:
            tmp_ind2 = -1
            for seat2 in seat_name_list:
                if seat == seat2:
                    tmp_ind2 = seat_name_list.index(seat2)
                    break
            if seat == '商务座' or seat == '特等座':
                tmp_ind2 = 3
                tmp_rsp['seat_name'][3] = seat
            tmp_rsp['price'][tmp_ind2] = int(ite.pri[tmp_ind])
            tmp_rsp['remain'][tmp_ind2] = ite.left[tmp_ind]
            tmp_ind += 1
        rsp.cusend(tmp_rsp)
    return jsonify(rsp)
    return jsonify([
        {'kind': 'D', 'name': 'D1234', 'kind_tag': 'D-动车', 
         'dep': '上海虹桥', 'dep_time': '08:00', 
         'des': '余姚北', 'des_time': '09:30', 
         'seat_name': ['无座', '二等座', '一等座', '商务/特等', '动卧', '软座', '硬座', '软卧', '硬卧'], 
         'price': [124, 124, 233, '--', '--', '--', '--', '--', '--'], 
         'remain': [2000, 3, 15, -1, -1, -1, -1, -1, -1], 
         'station': ['上海虹桥', '嘉善南', '嘉兴南', '桐乡', '杭州东', '绍兴北', '余姚北', '宁波', '临海', '深圳北'], 
         'arr_time': ['08:46', '09:14', '09:31', '09:45', '10:09', '10:33', '10:54', '11:18', '12:11', '00:39'], 
         'stan_time': ['发车', '9分', '3分', '9分', '5分', '2分', '2分', '7分', '2分', '到达'], 
         }, 
        {'kind': 'D', 'name': 'D1234', 'kind_tag': 'D-动车', 
         'dep': '上海虹桥', 'dep_time': '10:00', 
         'des': '余姚北', 'des_time': '11:40', 
         'seat_name': ['无座', '二等座', '一等座', '商务/特等', '动卧', '软座', '硬座', '软卧', '硬卧'], 
         'price': [124, 124, 233, '--', '--', '--', '--', '--', '--'], 
         'remain': [2000, 3, 15, -1, -1, -1, -1, -1, -1], 
         'station': ['上海虹桥', '嘉善南', '嘉兴南', '桐乡', '杭州东', '绍兴北', '余姚北', '宁波', '临海', '深圳北'], 
         'arr_time': ['08:46', '09:14', '09:31', '09:45', '10:09', '10:33', '10:54', '11:18', '12:11', '00:39'], 
         'stan_time': ['发车', '9分', '3分', '9分', '5分', '2分', '2分', '7分', '2分', '到达'], 
         }, 
        {'kind': 'G', 'name': 'G1234', 'kind_tag': 'G-高铁', 
         'dep': '上海虹桥', 'dep_time': '12:00', 
         'des': '余姚北', 'des_time': '13:14', 
         'seat_name': ['无座', '二等座', '一等座', '商务/特等', '动卧', '软座', '硬座', '软卧', '硬卧'], 
         'price': [224, 224, 233, '--', '--', '--', '--', '--', '--'], 
         'remain': [2000, 3, 15, -1, -1, -1, -1, -1, -1], 
         'station': ['上海虹桥', '嘉善南', '嘉兴南', '桐乡', '杭州东', '绍兴北', '余姚北', '宁波', '临海', '深圳北'], 
         'arr_time': ['08:46', '09:14', '09:31', '09:45', '10:09', '10:33', '10:54', '11:18', '12:11', '00:39'], 
         'stan_time': ['发车', '9分', '3分', '9分', '5分', '2分', '2分', '7分', '2分', '到达'], 
         } 
        ])

@cus.route("/buy_ticket", methods=['post'])
def buy_func():
    u_uid = request.cookies.get("uid")
    p_uid = session.get("uid")
    if p_uid != None and p_uid != u_uid:
        session.pop("uid", None)
    tmp = user_get()
    try:
        tmp.find(int(session.get("uid")))
    except:
        tmp.find(1)
    if not tmp.valid:
        return jsonify({'result': 0, 'message': '请先登录'})
    t = ticket_operate()
    t.uid = tmp.uid
    t.num = int(request.form['num'])
    t.loc1 = request.form['loc1']
    t.loc2 = request.form['loc2']
    t.date = request.form['date']
    t.train_id = request.form['train_id']
    t.ticket_name = request.form['ticket_kind']
    if t.buy_ticket():
        return jsonify({'result': 1, 'message': '购买成功'})
    else:
        return jsonify({'result': 0, 'message': '购买失败'})

@cus.route("/td_ticket", methods=['post'])
def td_func():
    u_uid = request.cookies.get("uid")
    p_uid = session.get("uid")
    if p_uid != None and p_uid != u_uid:
        session.pop("uid", None)
    tmp = user_get()
    try:
        tmp.find(int(session.get("uid")))
    except:
        tmp.find(1)
    if not tmp.valid:
        return jsonify({'result': 0, 'message': '请先登录'})
    t = ticket_operate()
    t.uid = tmp.uid
    t.num = int(request.form['num'])
    t.loc1 = request.form['loc1']
    t.loc2 = request.form['loc2']
    t.date = request.form['date']
    t.train_id = request.form['train_id']
    t.ticket_name = request.form['ticket_kind']
    if t.refund_ticket():
        return jsonify({'result': 1, 'message': '退票成功'})
    else:
        return jsonify({'result': 0, 'message': '退票失败'})

@cus.route("/get_re", methods = ['post'])
def rem():
    u_uid = request.cookies.get("uid")
    p_uid = session.get("uid")
    if p_uid != None and p_uid != u_uid:
        session.pop("uid", None)
    tmp2 = user_get()
    try:
        tmp2.find(int(session.get("uid")))
    except:
        tmp2.find(1)
    if not tmp2.valid:
        return jsonify({'result': 0, 'message': '请先登录'})
    tmp = ticket_get()
    tmp.uid=tmp2.uid
    tmp.query_order()
    rsp = []
    for ite in tmp.result:
        tmp_rsp = {}
        tmp_train = train_get()
        tmp_train.find(ite.train_id)
        tmp_rsp['kind'] = tmp_train.catalog
        tmp_rsp['train_id'] = tmp_train.train_id
        tmp_rsp['kind_tag'] = kind_tag_list[tmp_train.catalog]
        tmp_rsp['name'] = tmp_train.name.split('(')[0]
        tmp_rsp['date'] = ite.date1
        tmp_rsp['dep'] = ite.loc1
        tmp_rsp['des'] = ite.loc2
        tmp_rsp['dep_time'] = ite.time1
        tmp_rsp['des_time'] = ite.time2
        tmp_rsp['seat_name'] = []
        for t in seat_name_list:
            tmp_rsp['seat_name'].cusend(t)
        tmp_rsp['station'] = tmp_train.station_name
        tmp_rsp['arr_time'] = tmp_train.arriv_time
        tmp_rsp['arr_time'][0] = tmp_train.start_time[0]
        tmp_rsp['stan_time'] = []
        tmp_rsp['price'] = []
        tmp_rsp['remain'] = []
        for so_t in tmp_train.stopover_time:
            tmp_rsp['stan_time'].cusend(so_t.split(':')[1] + '分')
        tmp_rsp['stan_time'][0] = '发车'
        tmp_rsp['stan_time'][len(tmp_rsp['stan_time']) - 1] = '到达'
        for seat in seat_name_list:
            tmp_rsp['price'].cusend('--')
            tmp_rsp['remain'].cusend(-1)
        tmp_ind = 0
        for seat in ite.ticket_name:
            tmp_ind2 = -1
            for seat2 in seat_name_list:
                if seat == seat2:
                    tmp_ind2 = seat_name_list.index(seat2)
                    break
            if seat == '商务座' or seat == '特等座':
                tmp_ind2 = 3
                tmp_rsp['seat_name'][3] = seat
            tmp_rsp['price'][tmp_ind2] = int(ite.pri[tmp_ind])
            tmp_rsp['remain'][tmp_ind2] = ite.left[tmp_ind]
            tmp_ind += 1
        rsp.cusend(tmp_rsp)
    return jsonify(rsp)

@cus.route("/logout", methods = ['get'])
def logout():
    session.pop("uid", None)
    rep = make_response(render_template('home.html', page="home"))
    rep.delete_cookie('uid')
    return rep

@cus.route("/modify_info", methods = ['post'])
def modify_info():
    u_uid = request.cookies.get("uid")
    p_uid = session.get("uid")
    if p_uid != None and p_uid != u_uid:
        session.pop("uid", None)
    if p_uid == None or p_uid != u_uid:
        return jsonify({'result': 0, 'message': '您未登录'})
    tmp = user_get()
    tmp.find(int(p_uid))
    tmp.name = request.form['name']
    tmp.phone = request.form['phone']
    tmp.modify()
    return jsonify({'result': 1, 'message': ''})

@cus.route("/modify_pwd", methods = ['post'])
def modify_pwd():
    u_uid = request.cookies.get("uid")
    p_uid = session.get("uid")
    if p_uid != None and p_uid != u_uid:
        session.pop("uid", None)
    if p_uid == None or p_uid != u_uid:
        return jsonify({'result': 0, 'message': '您未登录'})
    tmp = user_get()
    tmp.find(int(p_uid))
    if not tmp.password == request.form['pw1']:
        return jsonify({'result': 0, 'message': '密码错误'})
    tmp.password = request.form['pw2']
    tmp.modify()
    return jsonify({'result': 1, 'message': ''})


@cus.route('/login', methods = ['POST'])
def login():
    u_uid = request.cookies.get("uid")
    p_uid = session.get("uid")
    if p_uid and p_uid == u_uid:
        return jsonify({'result': 0, 'message': '您已登录'})
    tmp = user_get()
    if "@" in request.form['name']:
        tmp.find_by_email(request.form['name'])
    else:
        try:
            int(request.form['name'])
        except:
            return jsonify({'result': 0, 'message': '请输入UID或邮箱'})
        tmp.find(int(request.form['name']))
    if not tmp.valid or request.form['password'] != tmp.password:
        return jsonify({'result': 0, 'message': '用户不存在或密码错误'})
    rep = make_response(jsonify({'result': 1, 'message': tmp.name}))
    rep.set_cookie("uid", str(tmp.uid))
    session['uid'] = str(tmp.uid)
    return rep