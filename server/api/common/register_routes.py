from api.common.auth.routes import common_auth_bp

common_prefix='/api'
def register_common_blueprints(app):
    # Register auth blueprint
    app.register_blueprint(common_auth_bp, url_prefix=common_prefix)