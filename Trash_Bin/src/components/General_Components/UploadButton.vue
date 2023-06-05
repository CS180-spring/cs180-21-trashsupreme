<script lang="ts">
import { defineComponent } from 'vue';
import { round_button } from '@/tailwindClasses'
    export default defineComponent ({
        data() {return {
            round_button
        }},
        emits:['click']
    })
</script>

<template>
    <button @click="() => $emit('click')" :class=round_button>^</button>
</template>

<style>

</style>