from flask import Blueprint, request, jsonify

from database.models import User
from database.sql import db

common_auth_bp = Blueprint('auth', __name__)

@common_auth_bp.route('/login', methods=['POST'])
def login_post():
    data = request.get_json()

    username = data['username']
    password = data['password']

    if not username or not password:
        return jsonify({'error': 'Please provide username and password'}), 400

    user = User.query.filter_by(username=username).first()
    if not user or not user.check_password(password):
        return jsonify({'error': 'Invalid username or password'}), 401

    return jsonify({'message': 'Login successful'}), 200

@common_auth_bp.route('/register', methods=['POST'])
def register_post():


