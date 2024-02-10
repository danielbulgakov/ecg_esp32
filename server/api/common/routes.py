from flask import Blueprint
from auth.routes import auth_bp

# Create blueprint for routes
common_bp = Blueprint('common', __name__)

# Register blueprint for this blueprint
common_bp.register_blueprint(auth_bp, url_prefix='/auth')
