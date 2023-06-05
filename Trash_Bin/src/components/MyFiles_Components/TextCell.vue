<script lang="ts">
import { defineComponent } from 'vue';
import { oval_button } from '@/tailwindClasses';

    export default defineComponent ({
        data() {return {
            oval_button,
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
    <pre v-if="!editing" @click="editing = !editing">
        {{ currContent }}
    </pre>
    <span v-if="editing">
        <textarea v-model="currContent" />
        <div><button :class=oval_button @click="submit()">Submit</button></div>
    </span>
</template>

<style>

</style>