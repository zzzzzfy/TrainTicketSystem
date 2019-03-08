import os
import database as mydb
mydb.minit()
from app import create_app
from app.models import User
from flask.ext.script import Manager, Shell
from flask.ext.migrate import Migrate, MigrateCommand


app = create_app(os.getenv('FLASK_CONFIG') or 'default')
manager = Manager(app)
migrate = Migrate(app)

def make_shell_context():
    return dict(app = app, User = User)

manager.add_command('shell', Shell(make_context = make_shell_context))

if __name__ == '__main__':
    manager.run()
    