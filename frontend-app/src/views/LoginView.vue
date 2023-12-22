<script setup>
import { ref } from 'vue';
import { useRouter, useRoute } from 'vue-router';
import axios from 'axios';

const router = useRouter();

const userLogin = ref('');
const userPassword = ref('');

function handleSumbit(event) {
  console.log('Форма успешно отправлена');
  router.push({ name: 'about', replace: true });
}


</script>

<template>
  <div class="login-container">
    <div class="login-box">
      <div class="login-box__circle circle circle_brown">
        <img class="login-icon" src="@/assets/imgs/account_img.png" alt="Иконка авторизации">
      </div>
      <h1 class="login-box__header login-header">Авторизоваться</h1>
      <form
        @submit.prevent="handleSumbit"
        class="login-box__form"
      >
        <input
          v-model.trim="userLogin"
          class="login-box__input login-input"
          type="email"
          name="email"
          placeholder="Логин"
          required
        >
        <!-- TODO: Добавить валидацию пароля: количество символов, содержать разные виды символов -->
        <input
          v-model.trim="userPassword"
          class="login-box__input login-input"
          type="password"
          name="password"
          placeholder="Пароль"
          required
        >
        <button
          class="login-button"
          type="submit">
          Войти
        </button>
      </form>
    </div>  
  </div>
</template>

<style scoped>
.login-container {
  display: flex;
  justify-content: center;
  align-items: center;
  background: #F4F2EB;
  height: 100vh;
}

.login-box {
  display: flex;
  flex-direction: column;
  align-items: center;
  max-width: 500px;
  padding: 30px 70px 60px;
  border-radius: 20px;
  background: #FFF;
  box-shadow: -5px -5px 20px 0px rgba(0, 0, 0, 0.25), 5px 5px 20px 0px rgba(0, 0, 0, 0.25);
}

.circle {
  display: flex;
  justify-content: center;
  align-items: center;
  width: 64px;
  height: 64px;
  border-radius: 50%;
}

.circle_brown {
  background-color: #D8C3A5;
}

.login-box__circle {
  margin-bottom: 20px;
}

.login-icon {
  width: 32px;
}

.login-header {
  color: #000;
  font-size: 28px;
  font-style: normal;
  font-weight: 400;
  line-height: normal;
}

.login-box__header {
  margin-bottom: 35px;
}

.login-box__form {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.login-input {
  display: flex;
  width: 300px;
  height: 35px;
  padding: 24px 32px 23px 30px;
  font-size: 18px;
  align-items: center;
  flex-shrink: 0;
  background: #ECECEC;
}

.login-box__input {
  margin-bottom: 30px;
}

.login-box__input:last-child {
  margin-bottom: 40px;
}


.login-button {
  display: flex;
  width: 200px;
  padding: 17px 0px;
  font-size: 24px;
  justify-content: center;
  align-items: center;
  border-radius: 20px;
  background: #D8C3A5;
  box-shadow: 3px 3px 5px 0px rgba(0, 0, 0, 0.25), -3px -3px 5px 0px rgba(0, 0, 0, 0.25);
  transition: background-color 0.3s;
}

.login-button:hover {
  background: #dfcdb4;
  transition: background-color 0.3s;
}

.login-button:active {
  transform: scale(0.98) translateY(2px);
}
</style>