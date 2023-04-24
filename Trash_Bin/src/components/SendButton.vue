<script lang="ts">
var url = "http://localhost:18080/api/rest/v1/json/test";
export default {
  methods: {
    async handleClick() {
      console.log("test");
      const response = await fetch(url);
      // const text = await response.text();
      // console.log(text);
      const data = await response.json();
      console.log(data);
      // console.log("test")
    },
  },
};
</script>
<template>
  <div class="item">
    <!-- <button @click="handleClick" class="button">Click me!</button> -->
    <img
      alt="Vue logo"
      class="logo"
      src="../assets/logo.svg"
      width="125"
      height="125"
      @click="handleClick"
    />
  </div>
</template>
