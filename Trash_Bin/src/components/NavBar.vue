<script lang="ts">
import { defineComponent } from 'vue';
    export default defineComponent ({
        props: {
            labels: Array<string>
        },
        methods: {
            onClick(label:string) {
                this.$emit("click", label);
            }
        },
        emits:["click"]
    })
</script>

<template>
    <h1>NavBar</h1>
    <button v-for="label in labels" @click="onClick(label)">{{ label }}</button>
</template>