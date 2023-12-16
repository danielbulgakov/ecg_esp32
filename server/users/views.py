from django.contrib.auth import authenticate
from rest_framework.authtoken.models import Token
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from .models import CustomUser
from .serializers import CustomUserSerializer
from django.contrib.auth.hashers import make_password


class RegisterAPIView(APIView):
    def post(self, request, *args, **kwargs):
        username = request.data.get('username')
        email = request.data.get('email')
        password = request.data.get('password')

        # Check if all fields were filled
        if not username or not email or not password:
            return Response({'error': 'Fill all the fields'}, status=status.HTTP_400_BAD_REQUEST)

        # Check if email is unique
        if CustomUser.objects.filter(email=email).exists():
            return Response({'error': 'Email already exists'}, status=status.HTTP_400_BAD_REQUEST)

        # Password hashing
        hashed_password = make_password(password)

        user = CustomUser(username=username, email=email, password=hashed_password)
        user.save()

        serializer = CustomUserSerializer(user)
        token, created = Token.objects.get_or_create(user=user)

        return Response({
            'token': token,
            'user': serializer
        }, status=status.HTTP_201_CREATED)


class LoginAPIView(APIView):
    def post(self, request, *args, **kwargs):
        username = request.data.get('username')
        password = request.data.get('password')

        # Data validation
        if not username or not password:
            return Response({'error': 'Fill all the fields'}, status=status.HTTP_400_BAD_REQUEST)

        # User auth
        user = authenticate(username=username, password=password)

        if user:
            # If user valid then get or create token
            token, created = Token.objects.get_or_create(user=user)
            return Response({'token': token.key}, status=status.HTTP_200_OK)
        else:
            return Response({'error': 'Wrong username or password'}, status=status.HTTP_401_UNAUTHORIZED)
