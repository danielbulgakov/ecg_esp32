import hashlib
from datetime import datetime

from werkzeug.security import check_password_hash, generate_password_hash

from database.sql import db

class User(db.Model):
    id = db.Column(db.BigInteger, primary_key=True, autoincrement=True)
    username = db.Column(db.String(50), unique=False, nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)
    password_hash = db.Column(db.String(128), nullable=False)
    event_type = db.Column(db.String(50))
    timestamp = db.Column(db.DateTime, default=datetime.utcnow)
    ip_address = db.Column(db.String(50))
    user_agent = db.Column(db.String(200))
    status = db.Column(db.String(50))
    additional_info = db.Column(db.Text)

    # Password methods
    def set_password(self, password):
        self.password_hash = generate_password_hash(password)

    def check_password(self, password):
        return check_password_hash(self.password_hash, password)

    # Login methods

    @staticmethod
    def authenticate(email, password):
        user = User.query.filter_by(email=email).first()
        if user and user.check_password(password):
            user.timestamp = datetime.utcnow()  # Update timestamp mark
            db.session.commit()
            return user
        return None

    def __repr__(self):
        return '<User(id={}, username={}, email={})>'.format(self.id, self.username, self.email)
