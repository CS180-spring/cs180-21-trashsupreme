<script lang="ts">
import { defineComponent } from 'vue';
    export default defineComponent ({
        emits:['click']
    })
</script>

<template>
    <span @click="() => $emit('click')">➕</span>
</template>

<style>

</style>