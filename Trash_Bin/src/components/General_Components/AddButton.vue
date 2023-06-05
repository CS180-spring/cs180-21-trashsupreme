<script lang="ts">
import { round_button } from '@/tailwindClasses';
import { defineComponent } from 'vue';
    export default defineComponent ({
        data() {return {
            round_button
        }},
        emits:['click']
    })
</script>

<template>
    <button @click="() => $emit('click')" :class=round_button>+</button>
</template>

<style>

</style>