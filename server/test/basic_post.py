import requests

url = 'http://127.0.0.1:5000/api/add_user'

data = {
    'username': 'vlad',
    'password': 'bogdan'
}

response = requests.post(url, json=data)

if response.status_code ==  200:
    print('POST request was successful.')
    print('Content\n')
    print(response.json())
else:
    print(f'POST request failed with status code {response.status_code}.')

print(response.text)