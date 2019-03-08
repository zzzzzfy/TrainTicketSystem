from flask import Blueprint

cus = Blueprint('cus', __name__)

from . import views
