<script lang="ts">
import { defineComponent } from 'vue';

    export default defineComponent ({
        data() {return {
            editing: false,
            currContent: this.content
        }},
        props: {
            content: String
        },
        methods: {
            submit() {
                this.editing = false
                this.$emit('submit', this.currContent)
            }
        },
        emits: ['submit']
    })
</script>

<template>
    <span v-if="!editing" @click="editing = !editing">
        {{ currContent }}
    </span>
    <span v-if="editing">
        <textarea v-model="currContent" />
        <button @click="submit()">Submit</button>
    </span>
</template>

<style>

</style>