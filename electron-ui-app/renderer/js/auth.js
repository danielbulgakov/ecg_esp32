// auth.js

document.addEventListener('DOMContentLoaded', function () {
  const loginForm = document.querySelector('.login-box__form');

  loginForm.addEventListener('submit', function (event) {
    event.preventDefault();

    console.log(event)
    // Скорее всего это можно сделать иначе, почитать как
    const email = event.srcElement[0].value;
    const password = event.srcElement[1].value;

    // Здесь вы можете отправить запрос на сервер для проверки учетных данных
    // и получения токена аутентификации.

    // Пример:
    // fetch('https://example.com/login', {
    //   method: 'POST',
    //   headers: {
    //     'Content-Type': 'application/json',
    //   },
    //   body: JSON.stringify({ email, password }),
    // })
    // .then(response => response.json())
    // .then(data => {
    //   if (data.token) {
    //     // Успешная аутентификация
    //     alert('Login successful!');
    //     // Переход на главную страницу
    //     window.location.href = 'home.html';
    //   } else {
    //     // Неправильные учетные данные
    //     alert('Invalid credentials. Please try again.');
    //   }
    // })
    // .catch(error => {
    //   console.error('Error:', error);
    // });

    // Для примера, просто переходим на главную страницу
    window.location.href = 'index.html';
  });
});
