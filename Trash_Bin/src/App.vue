<script lang="ts">
import NavBar from './components/NavBar.vue'
import Login from './components/Login.vue'
import Search from './components/Search.vue'
import MyFiles from './components/MyFiles.vue'
//let asdf: String[] = ["Button 1", "Button 2"]
export default {
  components: {
    NavBar,
    Login,
    Search,
    MyFiles
  },
  data() {return {
    menus: ["Login", "My Files", "Search"],
    currentMenu: "Login"
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
    <NavBar :labels="menus" @click="changeMenu" />
    <Login v-if="currentMenu === 'Login'" />
    <Search v-if="currentMenu === 'Search'" />
    <MyFiles v-if="currentMenu === 'My Files'" />
  </main>
</template>

<style scoped>

</style>
