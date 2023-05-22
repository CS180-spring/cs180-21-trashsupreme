
<script lang="ts">
import NavBar from './components/NavBar.vue'
import Login from './components/Login.vue'
import Search from './components/Search.vue'
import MyFiles from './components/MyFiles.vue'
import SendButton from './components/SendButton.vue'
//let asdf: String[] = ["Button 1", "Button 2"]
export default {
  components: {
    NavBar,
    Login,
    Search,
    MyFiles,
    SendButton
  },
  data() {return {
    menus: ["Login", "My Files", "Search"],
    currentMenu: "Search"
  }},
  methods: {
    changeMenu(currentLabel: string) {
      this.currentMenu = currentLabel
    }
  }
}
</script>

<template>
  <header>
  
  </header>

  <main>
    <h1>App</h1>
    <Search v-if="currentMenu === 'Search'" />
    <!--
    <NavBar :labels="menus" @click="changeMenu" />
    <Login v-if="currentMenu === 'Login'" />
    <MyFiles v-if="currentMenu === 'My Files'" />
    -->
    
  </main>
  <!--
  <div id="test">
      <SendButton />
      <img alt="Vue logo" class="logo" src="./assets/logo.svg" width="125" height="125" />
  </div>
  -->
</template>

<style scoped>

</style>
