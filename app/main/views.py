# -*- coding:utf-8 -*-  
from flask import render_template, redirect, url_for, abort, flash
from flask_login import login_required, current_user
from . import main
from .forms import ContactForm, EditProfileForm, EditProfileAdminForm, DeleteTrainForm, SaleTrainForm, ModifyTrainForm, BuildTrainForm
from .. import db
from flask_wtf import FlaskForm
from flask import request
from ..models import User
from ..decorators import admin_required
import json

# import sys
# sys.path.append("/home/zzzzffy/Desktop/net/flasky/app/db")
import database as mydb
# import sys
# reload(sys)
# sys.setdefaultencoding('utf8')


@main.route('/')
def index():
    return render_template('main/index.html')

def gz(a,b):
    a.id = b.uid
    a.email = b.email
    a.password = b.password
    a.confirmed = b.confirm
    a.privilege = b.privilege
    a.username = b.name

@main.route('/user/<useremail>')
def user(useremail):
    _user = mydb.user_get()
    _user.find_by_email(useremail)
    user = User()
    gz(user,_user)
    # user.email = _user.email
    # user.id = _user.uid
    # user.
    # user = User.query.filter_by(username=username).first_or_404()
    return render_template('main/user.html', user=user)


@main.route('/edit-profile', methods=['GET', 'POST'])
@login_required
def edit_profile():
    form = EditProfileForm()
    if form.validate_on_submit():
        _user = mydb.user_get()
        _user.find(current_user.id)
        _user.name = form.name.data
        _user.phone = form.phone.data
        _user.modify()
        # current_user.name = form.name.data
        # current_user.location = form.location.data
        # current_user.about_me = form.about_me.data
        # db.session.add(current_user._get_current_object())
        # db.session.commit()
        flash('Your profile has been updated.')
        return redirect(url_for('.user', useremail=current_user.email))
    form.name.data = current_user.username
    form.phone.data = current_user.phone
    # form.location.data = current_user.location
    # form.about_me.data = current_user.about_me
    return render_template('main/edit_profile.html', form=form)


@main.route('/edit-profile/<int:id>', methods=['GET', 'POST'])
@login_required
@admin_required
def edit_profile_admin(id):
    form = EditProfileAdminForm()
    _user = mydb.user_get()
    _user.find(id)
    user = User()
    gz(user,_user)
    print(form.privilege.data)
    # print(form.validate_on_submit())
    if request.method == "POST":
        print(form.email.data)
        print("!!!")
        _user.email = form.email.data
        _user.name = form.name.data
        _user.password = form.password.data
        if _user.privilege == 2 and int(form.privilege.data) == 2:
            flash("The guy is adminstrator!")
            return redirect(url_for('.edit_profile_admin', id = id))
        _user.privilege = int(form.privilege.data)
        _user.modify()
        flash('The profile has been updated.')
        return redirect(url_for('.edit_profile_admin', id = id))
    form.uid.data = user.id
    form.email.data = user.email
    form.privilege.data = user.privilege
    form.name.data = user.username
    return render_template('main/edit_profile.html', form=form)

@main.route('/delete-ticket', methods = ['GET', 'POST'])
@login_required
@admin_required
def delete_train():
    form = DeleteTrainForm()
    if form.validate_on_submit():
        # a = mydb.train_get()
        # if not a.find(form.train_id.data):
        #     flash("Train doesn't exisit!")
        #     return render_template('delete_ticket.html', form = form)
        flash("You delete a train successfuly!")
        return render_template('main/delete_ticket.html', form = form)
    return render_template('main/delete_ticket.html', form = form)

@main.route('/modify-train', methods = ['GET', 'POST'])
@login_required
@admin_required
def modify_train():
    form = BuildTrainForm()
    if request.method == "POST":
        # if request.form['inputlen']:
            # print(request.form['inputlen'])
            # return redirect(url_for('.index'))
        list_seat = request.form.getlist('pay')
        # print(list_seat)

        print(request.form)
        print(list_seat)
        print(type(list_seat))
        print(str(list_seat))
        num_seat = range(0, len(list_seat))
        print(num_seat)
        return render_template('main/modify_finish.html',
            train_id = request.form['train_id'], 
            name = request.form['name'], seat = list_seat, 
            seat2 = json.dumps(list_seat), num_se = num_seat, catalog = request.form['catalog'])

    return render_template('main/modify_ticket.html', form = form)

@main.route('/modify_finish', methods=['POST', 'GET'])
def modify_finish():
    if request.method == 'POST':
        print(request.form)
        train_id = request.form['train_id']
        train_id = train_id[0:len(train_id) - 1]
        train_name = request.form['train_name']
        train_name = train_name[0:len(train_name)-1]
        list_seat = json.loads(request.form['seat_list'])
        station_num = int(request.form['inputlen'])
        num_price = len(list_seat)

        a = mydb.train_get()
        # a.train_id = train_id
        a.name = train_name
        a.catalog = request.form['catalog']
        # print(station_num, num_price)
        # print(type(station_num), type(num_price))
        a.generate_list(station_num, num_price)
        for i in range(0,num_price):
            a.ticket_name[i] = list_seat[i]

        for i in range(1,station_num+1):
            a.station_name[i-1] = request.form['loca'+str(i)]
            a.start_time[i-1] = request.form['begintime'+str(i)]
            a.arriv_time[i-1] = request.form['endtime'+str(i)]
            a.stopover_time[i-1] = request.form['overtime'+str(i)]
            for j in range(0, num_price):
                a.price[i-1][j] = request.form['seat'+str(i)+str(j)]
            # a.arriv_time[i] = re
            # a.
        print("num:",a.num_price,a.num_station)
        a.add_train()
        flash("You modify a train successfully")

    return redirect((url_for('.modify_train')))



@main.route('/sale-train', methods = ['GET', 'POST'])
@login_required
@admin_required
def sale_train():
    form = SaleTrainForm()
    if form.validate_on_submit():
        flash("You sale a train successfuly!")
        return render_template('main/sale_ticket.html', form = form)
    return render_template('main/sale_ticket.html', form = form)


@main.route('/build-ticket', methods = ['GET', 'POST'])
@login_required
@admin_required
def build_train():
    form = BuildTrainForm()
    if request.method == 'POST':
        # if request.form['inputlen']:
            # print(request.form['inputlen'])
            # return redirect(url_for('.index'))
        list_seat = request.form.getlist('pay')
        # print(list_seat)

        print(request.form)
        print(list_seat)
        print(type(list_seat))
        print(str(list_seat))
        num_seat = range(0, len(list_seat))
        print(num_seat)
        return render_template('main/build_finish.html',
            train_id = request.form['train_id'], 
            name = request.form['name'], seat = list_seat, 
            seat2 = json.dumps(list_seat), num_se = num_seat, catalog = request.form['catalog'])
    return render_template('main/build_ticket.html', form = form)
 
@main.route('/build_finish', methods=['POST', 'GET'])
def build_finish():
    if request.method == 'POST':
        print(request.form)
        train_id = request.form['train_id']
        train_id = train_id[0:len(train_id) - 1]
        train_name = request.form['train_name']
        train_name = train_name[0:len(train_name)-1]
        list_seat = json.loads(request.form['seat_list'])
        station_num = int(request.form['inputlen'])
        num_price = len(list_seat)

        a = mydb.train_get()
        a.train_id = train_id
        a.name = train_name
        a.catalog = request.form['catalog']
        # print(station_num, num_price)
        # print(type(station_num), type(num_price))
        a.generate_list(station_num, num_price)
        for i in range(0,num_price):
            a.ticket_name[i] = list_seat[i]

        for i in range(1,station_num+1):
            a.station_name[i-1] = request.form['loca'+str(i)]
            a.start_time[i-1] = request.form['begintime'+str(i)]
            a.arriv_time[i-1] = request.form['endtime'+str(i)]
            a.stopover_time[i-1] = request.form['overtime'+str(i)]
            for j in range(0, num_price):
                a.price[i-1][j] = request.form['seat'+str(i)+str(j)]
            # a.arriv_time[i] = re
            # a.
        print("num:",a.num_price,a.num_station)
        a.add_train()
        flash("You build a train successfully")

    return redirect((url_for('.build_train')))

