# -*- coding:utf-8 -*-  
from flask import flash
from flask_wtf import FlaskForm
from wtforms import StringField, TextAreaField, BooleanField, SelectField,\
    SubmitField, IntegerField, IntegerField, FieldList, FormField, SelectMultipleField, PasswordField
from wtforms.validators import DataRequired, Length, Email, Regexp, EqualTo
from wtforms import ValidationError
from ..models import User
from wtforms import RadioField
from wtforms import widgets

import database as mydb

class MultiCheckboxField(SelectMultipleField):
    widge = widgets.ListWidget(prefix_label = True)
    option_widget = widgets.CheckboxInput()

class NameForm(FlaskForm):
    name = StringField('What is your name?', validators=[DataRequired()])
    submit = SubmitField('Submit')


class EditProfileForm(FlaskForm):
    name = StringField('Real name', validators=[Length(0, 64)])
    phone = StringField('Phone', validators=[Length(0, 64)])
    # location = StringField('Location', validators=[Length(0, 64)])
    # about_me = TextAreaField('About me')
    submit = SubmitField('Submit')


class EditProfileAdminForm(FlaskForm):
    uid = IntegerField('Id',validators=[DataRequired()]) 
    email = StringField('Email', validators=[DataRequired(), Length(1, 64),
                                             Email()])
    name = StringField('Real name', validators=[Length(0, 64)])
    password = PasswordField('Password', validators=[
        DataRequired(), EqualTo('password2', message='Passwords must match.')])
    password2 = PasswordField('Confirm password', validators=[DataRequired()])
    # username = StringField('Username', validators=[
    #     DataRequired(), Length(1, 64),
    #     Regexp('^[A-Za-z][A-Za-z0-9_.]*$', 0,
    #            'Usernames must have only letters, numbers, dots or '
    #            'underscores')])
    # confirmed = BooleanField('Confirmed')
    privilege = RadioField('privilege', choices=[(1, 'customer'), (2, 'administrator')],
                             validators=[DataRequired()])
    submit = SubmitField('Submit')

    def validate_uid(self, field):
        a = mydb.user_get()
        if field.data <= 2018:
            raise ValidationError('Id is illegal')
        if not a.find(field.data):
        # if field.data != self.user.email and \
        #         User.query.filter_by(email=field.data).first():
            raise ValidationError("Id doesn't exisit.")

    # def validate_email(self, field):
    #     a = mydb.user_get()
    #     b = mydb.user_get()
        # if a.find_by_email(field.data) and a.email != b.email:
        # # if field.data != self.user.email and \
        # #         User.query.filter_by(email=field.data).first():
        #     raise ValidationError('Email already registered.')



class DeleteTrainForm(FlaskForm):
    train_id = StringField('Train id')
    submit = SubmitField('Submit')

    def validate_train_id(self, field):
        a = mydb.train_get()
        a.train_id = field.data
        if not a.find(field.data):
            raise ValidationError("Train doesn't exisit")
        if not a.delete_train():  
            raise ValidationError("Failed to delete train")

class ModifyTrainForm(FlaskForm):
    train_id = StringField('Train id')
    name = StringField('Name')
    catalog = RadioField('catalog',choices=[('C','C'),('D','D'),('G','G'),('Z','Z'),('T','T')
                ,('K','K'),('L','L'),('A','A'),('Y','Y')])
    pay = MultiCheckboxField('pay',choices = [('硬座','硬座'),('软座','软座'),('硬卧','硬卧'),('软卧','软卧'),('站票','站票'),
                ('二等座','二等座'),('一等座','一等座'),('商务座','商务座')],coerce=int,validators=[DataRequired(message='ngdsb')])
    
    # def validate_train_id(self, field):
    #     a = mydb.train_get()
    #     a.train_id = field.data
    #     # print("this:",a.train_id)
    #     # print(a.find(field.data))
    #     if not a.find(field.data):
    #         flash("Train dosen't exisits")
    # # submit = SubmitField('Build')
    #     pass

class SaleTrainForm(FlaskForm):
    train_id = StringField('Train id')
    submit = SubmitField('Submit')
    def validate_train_id(self, field):
        a = mydb.train_get()
        a.train_id = field.data
        if not a.find(field.data):
            raise ValidationError("Train doesn't exisit")
        if not a.sale_train():  
            raise ValidationError("Failed to sale train")

# class MultiCheckboxField(SelectMultipleField): 
    # widget = widgets.ListWidget(prefix_label=True) 
    # option_widget = widgets.CheckboxInput() 

class BuildTrainForm(FlaskForm):
    train_id = StringField('Train id')
    name = StringField('Name')
    catalog = RadioField('catalog',choices=[('C','C'),('D','D'),('G','G'),('Z','Z'),('T','T')
                ,('K','K'),('L','L'),('A','A'),('Y','Y')])
    pay = MultiCheckboxField('pay',choices = [('硬座','硬座'),('软座','软座'),('硬卧','硬卧'),('软卧','软卧'),('站票','站票'),
                ('二等座','二等座'),('一等座','一等座'),('商务座','商务座')],coerce=int,validators=[DataRequired(message='ngdsb')])
    
    def validate_train_id(self, field):
        a = mydb.train_get()
        a.train_id = field.data
        print("this:",a.train_id)
        # print(a.find(field.data))
        if a.find(field.data):
            flash("Train exisits")
    # submit = SubmitField('Build')
    pass

class TelephoneForm(FlaskForm):
    country_code = IntegerField('Country Code')
    area_code    = IntegerField('Area Code/Exchange')
    number       = TextAreaField('Number')

class ContactForm(FlaskForm):
    first_name   = TextAreaField()
    last_name    = TextAreaField()
    mobile_phone = FormField(TelephoneForm)
    office_phone = FormField(TelephoneForm)
    phones       = FieldList(FormField(TelephoneForm))