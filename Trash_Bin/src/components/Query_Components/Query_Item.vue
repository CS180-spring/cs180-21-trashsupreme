<script lang="ts">
import DeleteButton from '../General_Components/DeleteButton.vue'
import { badge } from '@/tailwindClasses'
import { defineComponent } from 'vue';
    export default defineComponent ({
        emits:['delete'],
        data() {return {
            badge
        }},
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
    <div>
        <span :class=badge>
            {{ name }}: {{ value }}  <DeleteButton @click="$emit('delete')" />
        </span>
    </div>
</template>

<style>

</style>