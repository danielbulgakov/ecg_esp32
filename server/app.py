from flask import Flask

from api.common.register_routes import register_common_blueprints
from database.sql import init_db

app = Flask(__name__)

# CONFIG
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:////home/dbulgakov/Work/ecg_esp32/server/data/clients.db'

# Register blueprints
def register_blueprints(app):
    register_common_blueprints(app)

# Init dependency modules
init_db(app)
register_blueprints(app)

if __name__ == '__main__':
    app.run()
