<script setup>
import { ref } from 'vue';
import TheHeader from '@/components/TheHeader.vue';
import TheFooter from '@/components/TheFooter.vue';
import TheBody from '@/components/TheBody.vue'

</script>

<template>
  <div class="container">
    <TheHeader />
    <TheBody />
    <TheFooter />
  </div>
</template>

<style scoped>
.container {
  max-width: 1440px;
  min-height: 100vh;
  background-color: antiquewhite;
  margin: 0 auto;
  display: flex;
  flex-direction: column;
}
</style>