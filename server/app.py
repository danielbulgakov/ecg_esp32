from flask import Flask

from api.common.routes import common_bp
from api.electron.routes import electron_bp
from api.web.routes import web_bp

app = Flask(__name__)

if __name__ == '__main__':

    # Register blueprints for my app
    app.register_blueprint(common_bp, url_prefix='/api')
    app.register_blueprint(electron_bp, url_prefix='/api/electron')
    app.register_blueprint(web_bp, url_prefix='/api/web')

    app.run()
