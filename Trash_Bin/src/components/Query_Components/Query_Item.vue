<script lang="ts">
import DeleteButton from '../General_Components/DeleteButton.vue'
import { defineComponent } from 'vue';
    export default defineComponent ({
        emits:['delete'],
        components: {
            DeleteButton
        },
        props: {
            name: String,
            value: String
        }
    })
</script>

<template>
    <div>{{ name }}: {{ value }}  <DeleteButton @click="$emit('delete')" /></div>
</template>

<style>

</style>